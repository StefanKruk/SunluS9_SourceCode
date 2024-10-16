#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/screens/spinner_dialog_box.cpp"
/**************************
 * spinner_dialog_box.cpp *
 **************************/

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

#include "../config.h"
#include "screens.h"
#include "screen_data.h"

#ifdef FTDI_SPINNER_DIALOG_BOX

using namespace FTDI;
using namespace ExtUI;

constexpr static SpinnerDialogBoxData &mydata = screen_data.SpinnerDialogBox;

void SpinnerDialogBox::onRedraw(draw_mode_t) {
}

void SpinnerDialogBox::show(const progmem_str message) {
  drawMessage(message);
  drawSpinner();
  storeBackground();
  mydata.auto_hide = false;
}

void SpinnerDialogBox::hide() {
  CommandProcessor cmd;
  cmd.stop().execute();
}

void SpinnerDialogBox::enqueueAndWait_P(const progmem_str commands) {
  enqueueAndWait_P(GET_TEXT_F(MSG_PLEASE_WAIT), commands);
}

void SpinnerDialogBox::enqueueAndWait_P(const progmem_str message, const progmem_str commands) {
  show(message);
  GOTO_SCREEN(SpinnerDialogBox);
  ExtUI::injectCommands_P((const char*)commands);
  mydata.auto_hide = true;
}

void SpinnerDialogBox::onIdle() {
  reset_menu_timeout();
  if (mydata.auto_hide && !commandsInQueue()) {
    mydata.auto_hide = false;
    hide();
    GOTO_PREVIOUS();
  }
}

#endif // FTDI_SPINNER_DIALOG_BOX
