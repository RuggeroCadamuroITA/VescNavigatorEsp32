#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

// Include centrale che a sua volta include tutti i dir_*.h
#include "directions.h"

// =============================
// CONFIG (uguali ad Android)
// =============================
static const char* DEVICE_NAME = "MotoNav_ESP32";
static BLEUUID SERVICE_UUID("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
static BLEUUID CHAR_UUID  ("beb5483e-36e1-4688-b7f5-ea07361b26a8");

// =============================
// Stato
// =============================
static bool deviceConnected = false;

// Anti-spam (stampa solo se cambia)
static int lastCode   = -999;
static int lastMeters = -999;
static int lastExit   = -999;

// =============================
// Parsing: formato Android = "code;meters;exit"
// Esempio: "7;120;2"
// =============================
bool parseMessage(const String& msg, int &outCode, int &outMeters, int &outExit) {
  int p1 = msg.indexOf(';');
  if (p1 < 0) return false;

  int p2 = msg.indexOf(';', p1 + 1);
  if (p2 < 0) return false;

  String sCode   = msg.substring(0, p1);
  String sMeters = msg.substring(p1 + 1, p2);
  String sExit   = msg.substring(p2 + 1);

  sCode.trim();
  sMeters.trim();
  sExit.trim();

  if (sCode.isEmpty() || sMeters.isEmpty() || sExit.isEmpty()) return false;

  outCode   = sCode.toInt();
  outMeters = sMeters.toInt();
  outExit   = sExit.toInt();

  if (outMeters < 0) outMeters = 0;
  if (outExit < 0) outExit = 0;

  return true;
}

// =============================
// Callback Server
// =============================
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override {
    deviceConnected = true;
    Serial.println("\n✅ BLE CONNECTED");
  }

  void onDisconnect(BLEServer* pServer) override {
    deviceConnected = false;
    Serial.println("\n❌ BLE DISCONNECTED");

    BLEDevice::startAdvertising();
    Serial.println("📡 Advertising restarted");
  }
};

// =============================
// Callback Characteristic (onWrite)
// =============================
class MyCharCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) override {
    std::string rx = pCharacteristic->getValue();
    if (rx.empty()) return;

    // Converti a String Arduino
    String msg;
    msg.reserve(rx.size());
    for (size_t i = 0; i < rx.size(); i++) msg += (char)rx[i];

    int code = 0;
    int meters = 0;
    int exitNum = 0;

    if (!parseMessage(msg, code, meters, exitNum)) {
      Serial.println("\n==============================");
      Serial.println("📥 RX BLE WRITE (PARSE FAIL)");
      Serial.print("Raw: ");
      Serial.println(msg);
      Serial.println("⚠️ Format atteso: code;meters;exit");
      Serial.println("==============================");
      return;
    }

    // Anti-spam
    if (code == lastCode && meters == lastMeters && exitNum == lastExit) {
      return;
    }
    lastCode = code;
    lastMeters = meters;
    lastExit = exitNum;

    // Usa i tuoi .h tramite directions.h
    const char* dirName = navdir::name_from_code(code);
    const char* dirIcon = navdir::icon_from_code(code);

    Serial.println("\n==============================");
    Serial.println("📥 RX BLE NAV");
    Serial.print("Raw: ");
    Serial.println(msg);

    Serial.print("Code: ");
    Serial.println(code);

    Serial.print("DirName: ");
    Serial.println(dirName);

    Serial.print("DirIcon: ");
    Serial.println(dirIcon);

    Serial.print("Meters: ");
    Serial.println(meters);

    // Rotonda: exitNum se presente
    if (code == navdir::CODE_ROUNDABOUT) {
      Serial.print("Roundabout exit: ");
      if (exitNum > 0) Serial.println(exitNum);
      else Serial.println("(not provided)");
    }

    Serial.println("==============================");
  }
};

static BLECharacteristic* gChar = nullptr;

void setup() {
  Serial.begin(115200);
  delay(300);

  Serial.println("\n=== ESP32 BLE NAV RECEIVER (code;meters;exit) ===");

  BLEDevice::init(DEVICE_NAME);

  // Payload super corto, MTU non è fondamentale, ma non dà fastidio
  BLEDevice::setMTU(185);

  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new MyServerCallbacks());

  BLEService* service = server->createService(SERVICE_UUID);

  gChar = service->createCharacteristic(
    CHAR_UUID,
    BLECharacteristic::PROPERTY_WRITE |
    BLECharacteristic::PROPERTY_WRITE_NR
  );

  gChar->setCallbacks(new MyCharCallbacks());
  gChar->addDescriptor(new BLE2902());

  service->start();

  BLEAdvertising* adv = BLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->setScanResponse(true);
  adv->setMinPreferred(0x06);
  adv->setMinPreferred(0x12);

  BLEDevice::startAdvertising();

  Serial.println("📡 Advertising started");
  Serial.print("Device Name: "); Serial.println(DEVICE_NAME);
  Serial.print("Service UUID: "); Serial.println(SERVICE_UUID.toString().c_str());
  Serial.print("Char UUID: "); Serial.println(CHAR_UUID.toString().c_str());
  Serial.println("Apri l'app Android e premi CONNETTI ESP32.");
}

void loop() {
  delay(250);
}
