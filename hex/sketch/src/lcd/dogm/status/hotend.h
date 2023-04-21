#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/dogm/status/hotend.h"
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

//
// lcd/dogm/status/hotend.h - Status Screen Hotends bitmaps
//

#if HAS_MMU
  #define STATUS_HOTEND_BITMAPS EXTRUDERS
  #define MAX_HOTEND_BITMAPS 8
#else
  #define STATUS_HOTEND_BITMAPS HOTENDS
  #define MAX_HOTEND_BITMAPS 5
#endif
#if STATUS_HOTEND_BITMAPS > MAX_HOTEND_BITMAPS
  #undef STATUS_HOTEND_BITMAPS
  #define STATUS_HOTEND_BITMAPS MAX_HOTEND_BITMAPS
#endif

#define STATUS_HOTEND1_WIDTH  16

#if STATUS_HOTEND_BITMAPS == 1 || ENABLED(STATUS_HOTEND_NUMBERLESS)

  const unsigned char status_hotend_a_bmp[] PROGMEM = {
    B00011111,B11100000,
    B00111111,B11110000,
    B00111111,B11110000,
    B00111111,B11110000,
    B00011111,B11100000,
    B00011111,B11100000,
    B00111111,B11110000,
    B00111111,B11110000,
    B00111111,B11110000,
    B00001111,B11000000,
    B00000111,B10000000,
    B00000011,B00000000
  };

  #ifdef STATUS_HOTEND_ANIM

    const unsigned char status_hotend_b_bmp[] PROGMEM = {
      B00011111,B11100000,
      B00100000,B00010000,
      B00100000,B00010000,
      B00100000,B00010000,
      B00010000,B00100000,
      B00010000,B00100000,
      B00100000,B00010000,
      B00100000,B00010000,
      B00110000,B00110000,
      B00001000,B01000000,
      B00000100,B10000000,
      B00000011,B00000000
    };

  #endif

#elif STATUS_HOTEND_BITMAPS > 1

  #ifdef STATUS_HOTEND_ANIM

    const unsigned char status_hotend1_a_bmp[] PROGMEM = {
      B00011111,B11100000,
      B00111111,B11110000,
      #if LCD_FIRST_TOOL == 0
        B00111100,B11110000,
        B00111011,B01110000,
        B00111011,B01110000,
        B00011011,B01100000,
        B00011011,B01100000,
        B00111011,B01110000,
        B00111100,B11110000,
      #else
        B00111110,B11110000,
        B00111100,B11110000,
        B00011010,B11100000,
        B00011110,B11100000,
        B00111110,B11110000,
        B00111110,B11110000,
        B00111110,B11110000,
      #endif
      B00001111,B11000000,
      B00000111,B10000000,
      B00000011,B00000000
    };

    const unsigned char status_hotend1_b_bmp[] PROGMEM = {
      B00011111,B11100000,
      B00100000,B00010000,
      #if LCD_FIRST_TOOL == 0
        B00100011,B00010000,
        B00100100,B10010000,
        B00010100,B10100000,
        B00010100,B10100000,
        B00100100,B10010000,
        B00100100,B10010000,
        B00110011,B00110000,
      #else
        B00100001,B00010000,
        B00100011,B00010000,
        B00010101,B00100000,
        B00010001,B00100000,
        B00100001,B00010000,
        B00100001,B00010000,
        B00110001,B00110000,
      #endif
      B00001000,B01000000,
      B00000100,B10000000,
      B00000011,B00000000
    };

    const unsigned char status_hotend2_a_bmp[] PROGMEM = {
      B00011111,B11100000,
      B00111111,B11110000,
      #if LCD_FIRST_TOOL == 0
        B00111110,B11110000,
        B00111100,B11110000,
        B00011010,B11100000,
        B00011110,B11100000,
        B00111110,B11110000,
        B00111110,B11110000,
        B00111110,B11110000,
      #else
        B00111100,B11110000,
        B00111011,B01110000,
        B00011111,B01100000,
        B00011110,B11100000,
        B00111101,B11110000,
        B00111011,B11110000,
        B00111000,B01110000,
      #endif
      B00001111,B11000000,
      B00000111,B10000000,
      B00000011,B00000000
    };

    const unsigned char status_hotend2_b_bmp[] PROGMEM = {
      B00011111,B11100000,
      B00100000,B00010000,
      #if LCD_FIRST_TOOL == 0
        B00100001,B00010000,
        B00100011,B00010000,
        B00010101,B00100000,
        B00010001,B00100000,
        B00100001,B00010000,
        B00100001,B00010000,
        B00110001,B00110000,
      #else
        B00100011,B00010000,
        B00100100,B10010000,
        B00010000,B10100000,
        B00010001,B00100000,
        B00100010,B00010000,
        B00100100,B00010000,
        B00110111,B10110000,
      #endif
      B00001000,B01000000,
      B00000100,B10000000,
      B00000011,B00000000
    };

  #else

    const unsigned char status_hotend1_a_bmp[] PROGMEM = {
      B00011111,B11100000,
      #if LCD_FIRST_TOOL == 0
        B00111100,B11110000,
        B00111011,B01110000,
        B00111011,B01110000,
        B00011011,B01100000,
        B00011011,B01100000,
        B00111011,B01110000,
        B00111100,B11110000,
      #else
        B00111110,B11110000,
        B00111100,B11110000,
        B00111010,B11110000,
        B00011110,B11100000,
        B00011110,B11100000,
        B00111110,B11110000,
        B00111110,B11110000,
      #endif
      B00111111,B11110000,
      B00001111,B11000000,
      B00000111,B10000000,
      B00000011,B00000000
    };

    const unsigned char status_hotend2_a_bmp[] PROGMEM = {
      B00011111,B11100000,
      #if LCD_FIRST_TOOL == 0
        B00111110,B11110000,
        B00111100,B11110000,
        B00111010,B11110000,
        B00011110,B11100000,
        B00011110,B11100000,
        B00111110,B11110000,
        B00111110,B11110000,
      #else
        B00111100,B11110000,
        B00111011,B01110000,
        B00111111,B01110000,
        B00011110,B11100000,
        B00011101,B11100000,
        B00111011,B11110000,
        B00111000,B01110000,
      #endif
      B00111111,B11110000,
      B00001111,B11000000,
      B00000111,B10000000,
      B00000011,B00000000
    };

  #endif

  #if STATUS_HOTEND_BITMAPS >= 3

    #ifdef STATUS_HOTEND_ANIM

      const unsigned char status_hotend3_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00111111,B11110000,
        #if LCD_FIRST_TOOL == 0
          B00111100,B11110000,
          B00111011,B01110000,
          B00011111,B01100000,
          B00011110,B11100000,
          B00111101,B11110000,
          B00111011,B11110000,
          B00111000,B01110000,
        #else
          B00111100,B11110000,
          B00111011,B01110000,
          B00011111,B01100000,
          B00011100,B11100000,
          B00111111,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

      const unsigned char status_hotend3_b_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00100000,B00010000,
        #if LCD_FIRST_TOOL == 0
          B00100011,B00010000,
          B00100100,B10010000,
          B00010000,B10100000,
          B00010001,B00100000,
          B00100010,B00010000,
          B00100100,B00010000,
          B00110111,B10110000,
        #else
          B00100011,B00010000,
          B00100100,B10010000,
          B00010000,B10100000,
          B00010011,B00100000,
          B00100000,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #endif
        B00001000,B01000000,
        B00000100,B10000000,
        B00000011,B00000000
      };

    #else

      const unsigned char status_hotend3_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        #if LCD_FIRST_TOOL == 0
          B00111100,B11110000,
          B00111011,B01110000,
          B00111111,B01110000,
          B00011110,B11100000,
          B00011101,B11100000,
          B00111011,B11110000,
          B00111000,B01110000,
        #else
          B00111100,B11110000,
          B00111011,B01110000,
          B00111111,B01110000,
          B00011100,B11100000,
          B00011111,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00111111,B11110000,
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

    #endif

  #endif

  #if STATUS_HOTEND_BITMAPS >= 4

    #ifdef STATUS_HOTEND_ANIM

      const unsigned char status_hotend4_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00111111,B11110000,
        #if LCD_FIRST_TOOL == 0
          B00111100,B11110000,
          B00111011,B01110000,
          B00011111,B01100000,
          B00011100,B11100000,
          B00111111,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #else
          B00111011,B01110000,
          B00111011,B01110000,
          B00011011,B01100000,
          B00011011,B01100000,
          B00111000,B00110000,
          B00111111,B01110000,
          B00111111,B01110000,
        #endif
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

      const unsigned char status_hotend4_b_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00100000,B00010000,
        #if LCD_FIRST_TOOL == 0
          B00100011,B00010000,
          B00100100,B10010000,
          B00010000,B10100000,
          B00010011,B00100000,
          B00100000,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #else
          B00100100,B10010000,
          B00100100,B10010000,
          B00010100,B10100000,
          B00010100,B10100000,
          B00100111,B11010000,
          B00100000,B10010000,
          B00110000,B10110000,
        #endif
        B00001000,B01000000,
        B00000100,B10000000,
        B00000011,B00000000
      };

    #else

      const unsigned char status_hotend4_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        #if LCD_FIRST_TOOL == 0
          B00111100,B11110000,
          B00111011,B01110000,
          B00111111,B01110000,
          B00011100,B11100000,
          B00011111,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #else
          B00111011,B01110000,
          B00111011,B01110000,
          B00111011,B01110000,
          B00011011,B01100000,
          B00011000,B00100000,
          B00111111,B01110000,
          B00111111,B01110000,
        #endif
        B00111111,B11110000,
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

    #endif

  #endif

  #if STATUS_HOTEND_BITMAPS >= 5

    #ifdef STATUS_HOTEND_ANIM

      const unsigned char status_hotend5_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00111111,B11110000,
        #if LCD_FIRST_TOOL == 0
          B00111011,B01110000,
          B00111011,B01110000,
          B00011011,B01100000,
          B00011011,B01100000,
          B00111000,B00110000,
          B00111111,B01110000,
          B00111111,B01110000,
        #else
          B00111000,B01110000,
          B00111011,B11110000,
          B00011000,B11100000,
          B00011111,B01100000,
          B00111111,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

      const unsigned char status_hotend5_b_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00100000,B00010000,
        #if LCD_FIRST_TOOL == 0
          B00100100,B10010000,
          B00100100,B10010000,
          B00010100,B10100000,
          B00010100,B10100000,
          B00100111,B11010000,
          B00100000,B10010000,
          B00110000,B10110000,
        #else
          B00100111,B10010000,
          B00100100,B00010000,
          B00010111,B00100000,
          B00010000,B10100000,
          B00100000,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #endif
        B00001000,B01000000,
        B00000100,B10000000,
        B00000011,B00000000
      };

    #else

      const unsigned char status_hotend5_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        #if LCD_FIRST_TOOL == 0
          B00111011,B01110000,
          B00111011,B01110000,
          B00111011,B01110000,
          B00011011,B01100000,
          B00011000,B00100000,
          B00111111,B01110000,
          B00111111,B01110000,
        #else
          B00111000,B01110000,
          B00111011,B11110000,
          B00111000,B11110000,
          B00011111,B01100000,
          B00011111,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00111111,B11110000,
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

    #endif

  #endif

  #if STATUS_HOTEND_BITMAPS >= 6

    #ifdef STATUS_HOTEND_ANIM

      const unsigned char status_hotend6_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00111111,B11110000,
        #if LCD_FIRST_TOOL == 0
          B00111000,B01110000,
          B00111011,B11110000,
          B00011000,B11100000,
          B00011111,B01100000,
          B00111111,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #else
          B00111100,B01110000,
          B00111011,B11110000,
          B00011011,B11100000,
          B00011000,B11100000,
          B00111011,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

      const unsigned char status_hotend6_b_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00100000,B00010000,
        #if LCD_FIRST_TOOL == 0
          B00100111,B10010000,
          B00100100,B00010000,
          B00010111,B00100000,
          B00010000,B10100000,
          B00100000,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #else
          B00100011,B10010000,
          B00100100,B00010000,
          B00010100,B00100000,
          B00010111,B00100000,
          B00100100,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #endif
        B00001000,B01000000,
        B00000100,B10000000,
        B00000011,B00000000
      };

    #else

      const unsigned char status_hotend6_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        #if LCD_FIRST_TOOL == 0
          B00111000,B01110000,
          B00111011,B11110000,
          B00111000,B11110000,
          B00011111,B01100000,
          B00011111,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #else
          B00111100,B01110000,
          B00111011,B11110000,
          B00111011,B11110000,
          B00011000,B11100000,
          B00011011,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00111111,B11110000,
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

    #endif

  #endif

  #if STATUS_HOTEND_BITMAPS >= 7

    #ifdef STATUS_HOTEND_ANIM

      const unsigned char status_hotend7_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00111111,B11110000,
        #if LCD_FIRST_TOOL == 0
          B00111100,B01110000,
          B00111011,B11110000,
          B00011011,B11100000,
          B00011000,B11100000,
          B00111011,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #else
          B00111000,B01110000,
          B00111011,B01110000,
          B00011111,B01100000,
          B00011110,B11100000,
          B00111110,B11110000,
          B00111101,B11110000,
          B00111101,B11110000,
        #endif
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

      const unsigned char status_hotend7_b_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00100000,B00010000,
        #if LCD_FIRST_TOOL == 0
          B00100011,B10010000,
          B00100100,B00010000,
          B00010100,B00100000,
          B00010111,B00100000,
          B00100100,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #else
          B00100111,B10010000,
          B00100100,B10010000,
          B00010000,B10100000,
          B00010001,B00100000,
          B00100001,B00010000,
          B00100010,B00010000,
          B00110010,B00110000,
        #endif
        B00001000,B01000000,
        B00000100,B10000000,
        B00000011,B00000000
      };

    #else

      const unsigned char status_hotend7_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        #if LCD_FIRST_TOOL == 0
          B00111100,B01110000,
          B00111011,B11110000,
          B00111011,B11110000,
          B00011000,B11100000,
          B00011011,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #else
          B00111000,B01110000,
          B00111011,B01110000,
          B00111111,B01110000,
          B00011110,B11100000,
          B00011110,B11100000,
          B00111101,B11110000,
          B00111101,B11110000,
        #endif
        B00111111,B11110000,
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

    #endif

  #endif

  #if STATUS_HOTEND_BITMAPS >= 8

    #ifdef STATUS_HOTEND_ANIM

      const unsigned char status_hotend8_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00111111,B11110000,
        #if LCD_FIRST_TOOL == 0
          B00111000,B01110000,
          B00111011,B01110000,
          B00011111,B01100000,
          B00011110,B11100000,
          B00111110,B11110000,
          B00111101,B11110000,
          B00111101,B11110000,
        #else
          B00111100,B11110000,
          B00111011,B01110000,
          B00011011,B01100000,
          B00011100,B11100000,
          B00111011,B01110000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

      const unsigned char status_hotend8_b_bmp[] PROGMEM = {
        B00011111,B11100000,
        B00100000,B00010000,
        #if LCD_FIRST_TOOL == 0
          B00100111,B10010000,
          B00100100,B10010000,
          B00010000,B10100000,
          B00010001,B00100000,
          B00100001,B00010000,
          B00100010,B00010000,
          B00110010,B00110000,
        #else
          B00100011,B00010000,
          B00100100,B10010000,
          B00010100,B10100000,
          B00010011,B00100000,
          B00100100,B10010000,
          B00100100,B10010000,
          B00110011,B00110000,
        #endif
        B00001000,B01000000,
        B00000100,B10000000,
        B00000011,B00000000
      };

    #else

      const unsigned char status_hotend8_a_bmp[] PROGMEM = {
        B00011111,B11100000,
        #if LCD_FIRST_TOOL == 0
          B00111000,B01110000,
          B00111011,B01110000,
          B00111111,B01110000,
          B00011110,B11100000,
          B00011110,B11100000,
          B00111101,B11110000,
          B00111101,B11110000,
        #else
          B00111100,B11110000,
          B00111011,B01110000,
          B00111011,B01110000,
          B00011100,B11100000,
          B00011011,B01100000,
          B00111011,B01110000,
          B00111100,B11110000,
        #endif
        B00111111,B11110000,
        B00001111,B11000000,
        B00000111,B10000000,
        B00000011,B00000000
      };

    #endif

  #endif

#endif
