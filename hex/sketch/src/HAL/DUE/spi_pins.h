#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/DUE/spi_pins.h"
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
 * Define SPI Pins: SCK, MISO, MOSI, SS
 *
 * Available chip select pins for HW SPI are 4 10 52 77
 */
#if SDSS == 4 || SDSS == 10 || SDSS == 52 || SDSS == 77 || SDSS == 87
  #if SDSS == 4
    #define SPI_PIN         87
    #define SPI_CHAN         1
  #elif SDSS == 10
    #define SPI_PIN         77
    #define SPI_CHAN         0
  #elif SDSS == 52
    #define SPI_PIN         86
    #define SPI_CHAN         2
  #elif SDSS == 77
    #define SPI_PIN         77
    #define SPI_CHAN         0
  #else
    #define SPI_PIN         87
    #define SPI_CHAN         1
  #endif
  #define SD_SCK_PIN        76
  #define SD_MISO_PIN       74
  #define SD_MOSI_PIN       75
#else
  // defaults
  #define DUE_SOFTWARE_SPI
  #ifndef SD_SCK_PIN
    #define SD_SCK_PIN      52
  #endif
  #ifndef SD_MISO_PIN
    #define SD_MISO_PIN     50
  #endif
  #ifndef SD_MOSI_PIN
    #define SD_MOSI_PIN     51
  #endif
#endif

/* A.28, A.29, B.21, C.26, C.29 */
#define SD_SS_PIN         SDSS
