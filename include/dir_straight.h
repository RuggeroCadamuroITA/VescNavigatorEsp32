#pragma once
#include <stdint.h>

namespace navdir {
  static constexpr int CODE_STRAIGHT = 6;

  inline const char* name_straight() { return "STRAIGHT / MERGE / DEFAULT"; }
  inline const char* icon_straight() { return "ARROW_STRAIGHT"; }
}
