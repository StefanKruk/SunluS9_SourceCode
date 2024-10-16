#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/pins/sanguino/pins_MELZI_MALYAN.h"
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
 * Melzi (Malyan M150) pin assignments
 */

#define BOARD_INFO_NAME "Melzi (Malyan)"

// Alter timing for graphical display
#if HAS_MARLINUI_U8GLIB
  #ifndef BOARD_ST7920_DELAY_1
    #define BOARD_ST7920_DELAY_1 DELAY_NS(125)
  #endif
  #ifndef BOARD_ST7920_DELAY_2
    #define BOARD_ST7920_DELAY_2 DELAY_NS(125)
  #endif
  #ifndef BOARD_ST7920_DELAY_3
    #define BOARD_ST7920_DELAY_3 DELAY_NS(125)
  #endif
#endif

#include "pins_MELZI.h"

#undef LCD_SDSS
#undef LCD_PINS_RS
#undef LCD_PINS_ENABLE
#undef LCD_PINS_D4
#undef BTN_EN1
#undef BTN_EN2
#undef BTN_ENC

#define LCD_PINS_RS                           17  // ST9720 CS
#define LCD_PINS_ENABLE                       16  // ST9720 DAT
#define LCD_PINS_D4                           11  // ST9720 CLK
#define BTN_EN1                               30
#define BTN_EN2                               29
#define BTN_ENC                               28
