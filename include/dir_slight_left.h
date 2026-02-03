#pragma once
#include <stdint.h>

namespace navdir {
  static constexpr int CODE_SLIGHT_LEFT = 4;

  inline const char* name_slight_left() { return "TURN_SLIGHT_LEFT"; }
  inline const char* icon_slight_left() { return "ARROW_LEFT_SLIGHT"; }
}
