#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/TEENSY35_36/spi_pins.h"
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
 * HAL SPI Pins for Teensy 3.5 (MK64FX512) and Teensy 3.6 (MK66FX1M0)
 */

#define SD_SCK_PIN   13
#define SD_MISO_PIN  12
#define SD_MOSI_PIN  11
#define SD_SS_PIN 20 // SDSS // A.28, A.29, B.21, C.26, C.29
