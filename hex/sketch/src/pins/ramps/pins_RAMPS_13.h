#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/pins/ramps/pins_RAMPS_13.h"
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
 * Arduino Mega with RAMPS v1.3 pin assignments
 *
 * Applies to the following boards:
 *
 *  RAMPS_13_EFB (Extruder, Fan, Bed)
 *  RAMPS_13_EEB (Extruder, Extruder, Bed)
 *  RAMPS_13_EFF (Extruder, Fan, Fan)
 *  RAMPS_13_EEF (Extruder, Extruder, Fan)
 *  RAMPS_13_SF  (Spindle, Controller Fan)
 */

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME "RAMPS 1.3"
#endif

#define IS_RAMPS_13

#include "pins_RAMPS.h"
