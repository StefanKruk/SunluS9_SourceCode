#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/STM32F1/inc/Conditionals_adv.h"
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

#ifdef USE_USB_COMPOSITE
  //#warning "SD_CHECK_AND_RETRY isn't needed with USE_USB_COMPOSITE."
  #undef SD_CHECK_AND_RETRY
  #if DISABLED(NO_SD_HOST_DRIVE)
    #define HAS_SD_HOST_DRIVE 1
  #endif
#endif
