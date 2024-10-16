#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/gcode/stats/M75-M78.cpp"
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

#include "../gcode.h"
#include "../../module/printcounter.h"
#include "../../lcd/marlinui.h"

#include "../../MarlinCore.h" // for startOrResumeJob

/**
 * M75: Start print timer
 */
void GcodeSuite::M75() {
  startOrResumeJob();
}

/**
 * M76: Pause print timer
 */
void GcodeSuite::M76() {
  print_job_timer.pause();
}

/**
 * M77: Stop print timer
 */
void GcodeSuite::M77() {
  print_job_timer.stop();
}

#if ENABLED(PRINTCOUNTER)

/**
 * M78: Show print statistics
 */
void GcodeSuite::M78() {
  if (parser.intval('S') == 78) {  // "M78 S78" will reset the statistics
    print_job_timer.initStats();
    ui.reset_status();
    return;
  }

  #if HAS_SERVICE_INTERVALS
    if (parser.seenval('R')) {
      print_job_timer.resetServiceInterval(parser.value_int());
      ui.reset_status();
      return;
    }
  #endif

  print_job_timer.showStats();
}

#endif // PRINTCOUNTER
