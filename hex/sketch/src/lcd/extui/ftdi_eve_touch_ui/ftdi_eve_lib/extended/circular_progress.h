#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/ftdi_eve_lib/extended/circular_progress.h"
/***********************
 * circular_progress.h *
 ***********************/

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

namespace FTDI {
  void draw_circular_progress(CommandProcessor& cmd, int x, int y, int w, int h, float percent, char *text, uint32_t bgcolor, uint32_t fgcolor);
  void draw_circular_progress(CommandProcessor& cmd, int x, int y, int w, int h, float percent,             uint32_t bgcolor, uint32_t fgcolor);
}
