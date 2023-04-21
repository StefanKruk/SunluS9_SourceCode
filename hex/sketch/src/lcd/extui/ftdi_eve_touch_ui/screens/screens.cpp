#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/ftdi_eve_touch_ui/screens/screens.cpp"
/***************
 * screens.cpp *
 ***************/

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

#if ENABLED(TOUCH_UI_FTDI_EVE)
#include "screens.h"
tiny_timer_t refresh_timer;


/**
 * DECL_SCREEN_IF_INCLUDED allows for a concise
 * definition of SCREEN_TABLE:
 *
 * SCREEN_TABLE {
 *   DECL_SCREEN_IF_INCLUDED(MY_HEADER)
 * }
 *
 * Is a shorthand for:
 *
 * SCREEN_TABLE {
 *   #ifdef MY_HEADER
 *     DECL_SCREEN(MY_HEADER),
 *   #endif
 * }
 *
 */
#define   COMMA ,
#define __DECL_SCREEN_IF_INCLUDED(O,C)   THIRD(O, DECL_SCREEN(C) COMMA,)
#define  _DECL_SCREEN_IF_INCLUDED(O,C) __DECL_SCREEN_IF_INCLUDED(O ## COMMA, C)
#define   DECL_SCREEN_IF_INCLUDED(H)    _DECL_SCREEN_IF_INCLUDED(H, H ## _CLASS)

SCREEN_TABLE {
  DECL_SCREEN_IF_INCLUDED(FTDI_BOOT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_LANGUAGE_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_TOUCH_CALIBRATION_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_STATUS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_MAIN_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_TUNE_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_ADVANCED_SETTINGS_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_ALERT_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_CONFIRM_USER_REQUEST_ALERT_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_RESTORE_FAILSAFE_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_SAVE_SETTINGS_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_CONFIRM_START_PRINT_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_CONFIRM_ABORT_PRINT_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_CONFIRM_AUTO_CALIBRATION_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_CUSTOM_USER_MENUS)
  DECL_SCREEN_IF_INCLUDED(FTDI_SPINNER_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_ABOUT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_STATISTICS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_NUDGE_NOZZLE_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_MOVE_AXIS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_STEPS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_STEPPER_CURRENT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_STEPPER_BUMP_SENSITIVITY_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_LEVELING_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_Z_OFFSET_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_BED_MESH_VIEW_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_BED_MESH_EDIT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_NOZZLE_OFFSETS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_BACKLASH_COMP_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_FEEDRATE_PERCENT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_FLOW_PERCENT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_MAX_VELOCITY_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_MAX_ACCELERATION_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_DEFAULT_ACCELERATION_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_JUNCTION_DEVIATION_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_JERK_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_CASE_LIGHT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_FILAMENT_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_FILAMENT_RUNOUT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_LINEAR_ADVANCE_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_TEMPERATURE_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_CHANGE_FILAMENT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_INTERFACE_SETTINGS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_INTERFACE_SOUNDS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_LOCK_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_FILES_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_ENDSTOP_STATE_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_BIO_PRINTING_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_BIO_CONFIRMOME_XYZ)
  DECL_SCREEN_IF_INCLUDED(FTDI_BIO_CONFIRMOME_E)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_STATUS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_MAIN_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_ADVANCED_SETTINGS_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_PREHEAT_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_PREHEAT_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_UNLOAD_CARTRIDGE_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_LOAD_CHOCOLATE_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_MOVE_XYZ_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_COCOA_MOVE_E_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_DEVELOPER_MENU)
  DECL_SCREEN_IF_INCLUDED(FTDI_CONFIRM_ERASE_FLASH_DIALOG_BOX)
  DECL_SCREEN_IF_INCLUDED(FTDI_WIDGET_DEMO_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_TOUCH_REGISTERS_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_STRESS_TEST_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_MEDIA_PLAYER_SCREEN)
  DECL_SCREEN_IF_INCLUDED(FTDI_DISPLAY_TUNING_SCREEN)
};

SCREEN_TABLE_POST

#include "screen_data.h"
screen_data_t screen_data;

#endif // TOUCH_UI_FTDI_EVE
