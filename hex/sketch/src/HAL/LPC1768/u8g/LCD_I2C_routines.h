#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/LPC1768/u8g/LCD_I2C_routines.h"
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

void u8g_i2c_init(const uint8_t clock_options);
//uint8_t u8g_i2c_wait(uint8_t mask, uint8_t pos);
uint8_t u8g_i2c_start(uint8_t sla);
uint8_t u8g_i2c_send_byte(uint8_t data);
void u8g_i2c_stop();
