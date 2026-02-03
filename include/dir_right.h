#pragma once
#include <stdint.h>

namespace navdir {
  static constexpr int CODE_RIGHT = 1;

  inline const char* name_right() { return "TURN_RIGHT / RAMP_RIGHT"; }
  inline const char* icon_right() { return "ARROW_RIGHT_90"; }
}
