#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/ESP32/watchdog.cpp"
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
#ifdef ARDUINO_ARCH_ESP32

#include "../../inc/MarlinConfig.h"

#if ENABLED(USE_WATCHDOG)

#define WDT_TIMEOUT_US TERN(WATCHDOG_DURATION_8S, 8000000, 4000000) // 4 or 8 second timeout

#include "watchdog.h"

void watchdogSetup() {
  // do whatever. don't remove this function.
}

void watchdog_init() {
  // TODO
}

#endif // USE_WATCHDOG

#endif // ARDUINO_ARCH_ESP32
