#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/pins/ramps/pins_TRIGORILLA_13.h"
/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Arduino Mega with RAMPS v1.3 for Anycubic
 */

#define BOARD_INFO_NAME "Anycubic RAMPS 1.3"

#define IS_RAMPS_EFB
#define RAMPS_D9_PIN                         44
#define FAN2_PIN                              9

#ifndef E0_AUTO_FAN_PIN
  #define E0_AUTO_FAN_PIN                     9
#endif

#include "pins_RAMPS_13.h"

#undef E1_STEP_PIN
#undef E1_DIR_PIN
#undef E1_ENABLE_PIN
#undef E1_CS_PIN
