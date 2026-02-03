#pragma once
#include <stdint.h>

namespace navdir {
  static constexpr int CODE_LEFT = 0;

  inline const char* name_left() { return "TURN_LEFT / RAMP_LEFT"; }
  inline const char* icon_left() { return "ARROW_LEFT_90"; }   // hint testuale
}
