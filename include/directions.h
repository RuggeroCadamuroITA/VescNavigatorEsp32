#pragma once

#include "dir_left.h"
#include "dir_right.h"
#include "dir_sharp_left.h"
#include "dir_sharp_right.h"
#include "dir_slight_left.h"
#include "dir_slight_right.h"
#include "dir_straight.h"
#include "dir_roundabout.h"
#include "dir_uturn.h"

namespace navdir {

  inline const char* name_from_code(int code) {
    switch (code) {
      case CODE_LEFT:         return name_left();
      case CODE_RIGHT:        return name_right();
      case CODE_SHARP_LEFT:   return name_sharp_left();
      case CODE_SHARP_RIGHT:  return name_sharp_right();
      case CODE_SLIGHT_LEFT:  return name_slight_left();
      case CODE_SLIGHT_RIGHT: return name_slight_right();
      case CODE_STRAIGHT:     return name_straight();
      case CODE_ROUNDABOUT:   return name_roundabout();
      case CODE_UTURN:        return name_uturn();
      default:                return "UNKNOWN";
    }
  }

  inline const char* icon_from_code(int code) {
    switch (code) {
      case CODE_LEFT:         return icon_left();
      case CODE_RIGHT:        return icon_right();
      case CODE_SHARP_LEFT:   return icon_sharp_left();
      case CODE_SHARP_RIGHT:  return icon_sharp_right();
      case CODE_SLIGHT_LEFT:  return icon_slight_left();
      case CODE_SLIGHT_RIGHT: return icon_slight_right();
      case CODE_STRAIGHT:     return icon_straight();
      case CODE_ROUNDABOUT:   return icon_roundabout();
      case CODE_UTURN:        return icon_uturn();
      default:                return "ARROW_STRAIGHT";
    }
  }

} // namespace navdir
