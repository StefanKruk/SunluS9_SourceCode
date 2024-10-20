#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/gcode/control/M380_M381.cpp"
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

#include "../../inc/MarlinConfig.h"

#if EITHER(EXT_SOLENOID, MANUAL_SOLENOID_CONTROL)

#include "../gcode.h"
#include "../../feature/solenoid.h"
#include "../../module/motion.h"

/**
 * M380: Enable solenoid on the active extruder
 *
 *   S<index> to specify a solenoid (Requires MANUAL_SOLENOID_CONTROL)
 */
void GcodeSuite::M380() {
  #if ENABLED(MANUAL_SOLENOID_CONTROL)
    enable_solenoid(parser.intval('S', active_extruder));
  #else
    enable_solenoid_on_active_extruder();
  #endif
}

/**
 * M381: Disable all solenoids if EXT_SOLENOID
 *       Disable selected/active solenoid if MANUAL_SOLENOID_CONTROL
 */
void GcodeSuite::M381() {
  #if ENABLED(MANUAL_SOLENOID_CONTROL)
    disable_solenoid(parser.intval('S', active_extruder));
  #else
    disable_all_solenoids();
  #endif
}

#endif // EXT_SOLENOID || MANUAL_SOLENOID_CONTROL
