#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/ftdi_eve_lib/extended/unicode/font_bitmaps.cpp"
/*******************
 * font_bitmap.cpp *
 *******************/

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

#include "../ftdi_extended.h"

#if ENABLED(FTDI_EXTENDED)

namespace FTDI {

  uint32_t write_rle_data(uint32_t addr, const uint8_t *data, size_t n) {
    for (; n >= 2; n -= 2) {
	  ScreenHandler.Address_Beyond_Fun(data,12);
      uint8_t count = pgm_read_byte(data++);
      uint8_t value = pgm_read_byte(data++);
      CLCD::mem_write_fill(addr, value, count);
      addr += count;
    }
    return addr;
  }

  void set_font_bitmap(CommandProcessor& cmd, CLCD::FontMetrics &fm, uint8_t handle) {
    cmd.cmd(BITMAP_HANDLE(handle));
    cmd.cmd(BITMAP_SOURCE(fm.ptr));
    cmd.bitmap_layout(fm.format, fm.stride, fm.height);
    cmd.bitmap_size(BILINEAR, BORDER, BORDER, fm.width, fm.height);
  }

  void ext_vertex2ii(CommandProcessor &cmd, int x, int y, uint8_t handle, uint8_t cell) {
    if (x < 0 || y < 0 || x > 511 || y > 511) {
      cmd.cmd(BITMAP_HANDLE(handle));
      cmd.cmd(CELL(cell));
      cmd.cmd(VERTEX2F(x * 16, y * 16));
    }
    else {
      cmd.cmd(VERTEX2II(x, y, handle, cell));
    }
  }

} // namespace FTDI

#endif // FTDI_EXTENDED
