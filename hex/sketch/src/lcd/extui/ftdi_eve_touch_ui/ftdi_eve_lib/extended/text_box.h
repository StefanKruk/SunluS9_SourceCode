#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/ftdi_eve_lib/extended/text_box.h"
/**************
 * text_box.h *
 **************/

/****************************************************************************
 *   Written By Marcio Teixeira 2019 - Aleph Objects, Inc.                  *
 *                                                                          *
 *   This program is free software: you can redistribute it and/or modify   *
 *   it under the terms of the GNU General Public License as published by   *
 *   the Free Software Foundation, either version 3 of the License, or      *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   This program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU General Public License for more details.                           *
 *                                                                          *
 *   To view a copy of the GNU General Public License, go to the following  *
 *   location: <https://www.gnu.org/licenses/>.                             *
 ****************************************************************************/

#pragma once

/**
 * This function draws text inside a bounding box, doing word wrapping and using the largest font that will fit.
 */
namespace FTDI {
  void draw_text_box(class CommandProcessor& cmd, int x, int y, int w, int h, progmem_str str, uint16_t options = 0, uint8_t font = 31);
  void draw_text_box(class CommandProcessor& cmd, int x, int y, int w, int h, const char *str, uint16_t options = 0, uint8_t font = 31);
}
