#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/screens/alert_dialog_box.h"
/**********************
 * alert_dialog_box.h *
 **********************/

/****************************************************************************
 *   Written By Mark Pelletier  2017 - Aleph Objects, Inc.                  *
 *   Written By Marcio Teixeira 2018 - Aleph Objects, Inc.                  *
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

#define FTDI_ALERT_DIALOG_BOX
#define FTDI_ALERT_DIALOG_BOX_CLASS AlertDialogBox

struct AlertDialogBoxData {
  bool isError;
};

class AlertDialogBox : public DialogBoxBaseClass, public CachedScreen<ALERT_BOX_CACHE,ALERT_BOX_DL_SIZE> {
  public:
    static void onEntry();
    static void onRedraw(draw_mode_t);
    template<typename T> static void show(T);
    template<typename T> static void showError(T);
    static void hide();
};
