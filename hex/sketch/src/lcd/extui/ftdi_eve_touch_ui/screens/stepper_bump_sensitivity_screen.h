#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/screens/stepper_bump_sensitivity_screen.h"
/*************************************
 * stepper_bump_sensitivity_screen.h *
 *************************************/

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

#define FTDI_STEPPER_BUMP_SENSITIVITY_SCREEN
#define FTDI_STEPPER_BUMP_SENSITIVITY_SCREEN_CLASS StepperBumpSensitivityScreen

class StepperBumpSensitivityScreen : public BaseNumericAdjustmentScreen, public CachedScreen<STEPPER_BUMP_SENSITIVITY_SCREEN_CACHE> {
  public:
    static void onRedraw(draw_mode_t);
    static bool onTouchHeld(uint8_t tag);
};
