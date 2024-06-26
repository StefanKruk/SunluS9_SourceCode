#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/screens/lock_screen.cpp"
/*******************
 * lock_screen.cpp *
 *******************/

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

#ifdef FTDI_LOCK_SCREEN

using namespace FTDI;
using namespace Theme;

uint16_t LockScreen::passcode = 0;
constexpr static LockScreenData &mydata = screen_data.LockScreen;

void LockScreen::onEntry() {
  const uint8_t siz = sizeof(mydata.passcode);
  memset(mydata.passcode, '_', siz-1);
  mydata.passcode[siz-1] = '\0';
  BaseScreen::onEntry();
}

void LockScreen::onRedraw(draw_mode_t what) {
  CommandProcessor cmd;

  if (what & BACKGROUND) {
    cmd.cmd(CLEAR_COLOR_RGB(bg_color))
       .cmd(CLEAR(true,true,true))
       .cmd(COLOR_RGB(bg_text_enabled))
       .tag(0);
  }

  if (what & FOREGROUND) {
    #if ENABLED(TOUCH_UI_PORTRAIT)
      #define GRID_COLS 1
      #define GRID_ROWS 10
    #else
      #define GRID_COLS 1
      #define GRID_ROWS 7
    #endif

    #undef MARGIN_T
    #undef MARGIN_B
    #define MARGIN_T 3
    #define MARGIN_B 3

    progmem_str message;
    switch (message_style()) {
      case 'w':
        message = GET_TEXT_F(MSG_PASSCODE_REJECTED);
        break;
      case 'g':
        message = GET_TEXT_F(MSG_PASSCODE_ACCEPTED);
        break;
      default:
        message = passcode ? GET_TEXT_F(MSG_PASSCODE_REQUEST) : GET_TEXT_F(MSG_PASSCODE_SELECT);
    }
    message_style() = '\0'; // Terminate the string.

    constexpr uint8_t l = TERN(TOUCH_UI_PORTRAIT, 6, 3);

    const uint8_t pressed = EventLoop::get_pressed_tag();

    cmd.font(font_large)
    #if ENABLED(TOUCH_UI_PORTRAIT)
       .text(BTN_POS(1,2), BTN_SIZE(1,1), message)
       .font(font_xlarge)
       .text(BTN_POS(1,4), BTN_SIZE(1,1), mydata.passcode)
    #else
       .text(BTN_POS(1,1), BTN_SIZE(1,1), message)
       .font(font_xlarge)
       .text(BTN_POS(1,2), BTN_SIZE(1,1), mydata.passcode)
    #endif
       .font(font_large)
       .colors(normal_btn)
    #ifdef TOUCH_UI_PASSCODE
       .keys(BTN_POS(1,l+1), BTN_SIZE(1,1), F("123"),        pressed)
       .keys(BTN_POS(1,l+2), BTN_SIZE(1,1), F("456"),        pressed)
       .keys(BTN_POS(1,l+3), BTN_SIZE(1,1), F("789"),        pressed)
       .keys(BTN_POS(1,l+4), BTN_SIZE(1,1), F("0.<"),        pressed);
    #else
       .keys(BTN_POS(1,l+1), BTN_SIZE(1,1), F("1234567890"), pressed)
       .keys(BTN_POS(1,l+2), BTN_SIZE(1,1), F("qwertyuiop"), pressed)
       .keys(BTN_POS(1,l+3), BTN_SIZE(1,1), F("asdfghjkl "), pressed)
       .keys(BTN_POS(1,l+4), BTN_SIZE(1,1), F("zxcvbnm!?<"), pressed);
    #endif

    #undef MARGIN_T
    #undef MARGIN_B
    #define MARGIN_T MARGIN_DEFAULT
    #define MARGIN_B MARGIN_DEFAULT

    #undef GRID_COLS
    #undef GRID_ROWS
  }
}

char &LockScreen::message_style() {
  // We use the last byte of the passcode string as a flag to indicate,
  // which message to show.
  constexpr uint8_t last_char = sizeof(mydata.passcode)-1;
  return mydata.passcode[last_char];
}

void LockScreen::onPasscodeEntered() {
  if (passcode == 0) {                        // We are defining a passcode
    message_style() = 0;
    onRefresh();
    sound.play(twinkle, PLAY_SYNCHRONOUS);
    passcode = compute_checksum();
    GOTO_PREVIOUS();
  }
  else if (passcode == compute_checksum()) {  // We are verifying a passcode
    message_style() = 'g';
    onRefresh();
    sound.play(twinkle, PLAY_SYNCHRONOUS);
    GOTO_PREVIOUS();
  }
  else {
    message_style() = 'w';
    onRefresh();
    sound.play(sad_trombone, PLAY_SYNCHRONOUS);
    current_screen.forget(); // Discard the screen the user was trying to go to.
    GOTO_PREVIOUS();
  }
}

bool LockScreen::onTouchEnd(uint8_t tag) {
  char *c = strchr(mydata.passcode,'_');
  if (c) {
    if (tag == '<') {
      if (c != mydata.passcode) {
        // Backspace deletes previous entered characters.
        *--c = '_';
      }
    }
    else {
      // Append character to passcode
      *c++ = tag;
      if (*c == '\0') {
        // If at last character, then process the code.
        onPasscodeEntered();
      }
    }
  }
  return true;
}

uint16_t LockScreen::compute_checksum() {
  uint16_t checksum = 0;
  const char* c = mydata.passcode;
  while (*c) {
    checksum = (checksum << 2) ^ *c++;
  }
  if (checksum == 0) checksum = 0xFFFF; // Prevent a zero checksum
  return checksum;
}

// This function should be called *after* calling GOTO_SCREEN
// to move to new screen. If a passcode is enabled, it will
// immediately jump to the keypad screen, pushing the previous
// screen onto the stack. If the code is entered correctly,
// the stack will be popped, allowing the user to proceed to
// the new screen. Otherwise it will be popped twice, taking
// the user back to where they were before.
void LockScreen::check_passcode() {
  if (passcode == 0) return;
  message_style() = 0;
  GOTO_SCREEN(LockScreen);
}

bool LockScreen::is_enabled() {
  return passcode != 0;
}

void LockScreen::disable() {
  passcode = 0;
}

void LockScreen::enable() {
  message_style() = 0;
  passcode = 0;
  GOTO_SCREEN(LockScreen);
}

#endif // FTDI_LOCK_SCREEN
