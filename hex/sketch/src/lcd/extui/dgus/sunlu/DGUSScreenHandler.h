#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/dgus/sunlu/DGUSScreenHandler.h"
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

#include "../DGUSDisplay.h"
#include "../DGUSVPVariable.h"
#include "../DGUSDisplayDef.h"

#include "../../../../inc/MarlinConfig.h"

enum DGUSLCD_Screens : uint8_t;

#define Filament_Check_Process
class DGUSScreenHandler {
public:
  DGUSScreenHandler() = default;

  static uint16_t Filament_Len;
  static uint16_t VP_Value;
  static int16_t z_compensate_adust;
  static float back_e;
  static bool save_par;
  static bool smile_adjustZ;
  static float temp_current_position_x,temp_current_position_y,temp_current_position_z,temp_current_position_e;
  static uint8_t temp_runout_enable;
  static uint8_t System_Config_0X80_D1[4];
  static volatile uint8_t power_loss_resume;
  static volatile uint8_t power_loss_cnt;
  static volatile uint8_t power_loss_state;
  static volatile uint8_t Filament_Runout_AutoRecovery_State;
  static volatile uint8_t Filament_Runout_AutoRecovery_Cnt;
  static volatile uint8_t back_Fliament_State;  //  click  start print   no filament
  static volatile uint8_t Filament_Runout_screen_state;
  static volatile uint8_t Filament_Runout_Check_Flag;

  static bool loop();
  static void resume_printUI();
  void onHomingStart();
  void onHomingComplete(bool t);
  void onStartMove();
  void onEndMove();
  void Temp_Calibration_Timer();
	

  // Send all 4 strings that are displayed on the infoscreen, confirmation screen and kill screen
  // The bools specifing whether the strings are in RAM or FLASH.
  static void sendinfoscreen(const char *line1, const char *line2, const char *line3, const char *line4, bool l1inflash, bool l2inflash, bool l3inflash, bool liinflash);
  static void sendkillscreen(uint32_t tmpaddress,uint32_t dataN0);
  static void Display_Para_screen(uint32_t dataN0,uint32_t dataN1);
	
  static void Address_Beyond_Fun(uint32_t tmpaddress,uint32_t dataN0);
  static void sendsoftwareversionscreen(const char *line1);
  static void sendprintinfoscreen(const char *line1);

  static void HandleUserConfirmationPopUp(uint16_t ConfirmVP, const char *line1, const char *line2, const char *line3, const char *line4, bool l1inflash, bool l2inflash, bool l3inflash, bool liinflash);

  // "M117" Message -- msg is a RAM ptr.
  static void setstatusmessage(const char *msg);
  // The same for messages from Flash
  static void setstatusmessagePGM(PGM_P const msg);
  // Callback for VP "Display wants to change screen on idle printer"
  static void ScreenChangeHookIfIdle(DGUS_VP_Variable &var, void *val_ptr);
  // Callback for VP "Screen has been changed"
  static void ScreenChangeHook(DGUS_VP_Variable &var, void *val_ptr);

  static void IntoSleep();//close LCD light
  static void OutoSleep();//open LCD light
  static void WaitMove();
  // Callback for VP "All Heaters Off"
  static void HandleAllHeatersOff(DGUS_VP_Variable &var, void *val_ptr);
  // Hook for "Change this temperature"
  static void HandleTemperatureChanged(DGUS_VP_Variable &var, void *val_ptr);
  static void HandlekeyboardChanged(DGUS_VP_Variable &var, void *val_ptr);//zb
  
  // Hook for "Change Flowrate"
  static void HandleFlowRateChanged(DGUS_VP_Variable &var, void *val_ptr);
  #if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
    // Hook for manual move option
    static void HandleManualMoveOption(DGUS_VP_Variable &var, void *val_ptr);
  #endif

  // Hook for manual move.
  static void HandleManualMove(DGUS_VP_Variable &var, void *val_ptr);
  // Hook for manual extrude.
  static void HandleManualExtrude(DGUS_VP_Variable &var, void *val_ptr);
  // Hook for motor lock and unlook
  static void HandleMotorLockUnlock(DGUS_VP_Variable &var, void *val_ptr);
  #if ENABLED(POWER_LOSS_RECOVERY)
    // Hook for power loss recovery.
    static void HandlePowerLossRecovery(DGUS_VP_Variable &var, void *val_ptr);
  #endif
  // Hook for settings
  static void HandleSettings(DGUS_VP_Variable &var, void *val_ptr);
  static void HandleStepPerMMChanged(DGUS_VP_Variable &var, void *val_ptr);
  static void HandleStepPerMMExtruderChanged(DGUS_VP_Variable &var, void *val_ptr);

  #if HAS_PID_HEATING
    // Hook for "Change this temperature PID para"
    static void HandleTemperaturePIDChanged(DGUS_VP_Variable &var, void *val_ptr);
    // Hook for PID autotune
    static void HandlePIDAutotune(DGUS_VP_Variable &var, void *val_ptr);
  #endif
  #if HAS_BED_PROBE
    // Hook for "Change probe offset z"
    static void HandleProbeOffsetZChanged(DGUS_VP_Variable &var, void *val_ptr);
  #endif
  #if ENABLED(BABYSTEPPING)
    // Hook for live z adjust action
    static void HandleLiveAdjustZ(DGUS_VP_Variable &var, void *val_ptr);
  #endif
  #if HAS_FAN
    // Hook for fan control
    static void HandleFanControl(DGUS_VP_Variable &var, void *val_ptr);
  #endif
  // Hook for heater control
  static void HandleHeaterControl(DGUS_VP_Variable &var, void *val_ptr);
  #if ENABLED(DGUS_PREHEAT_UI)
    // Hook for preheat
    static void HandlePreheat(DGUS_VP_Variable &var, void *val_ptr);
  #endif
  #if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
    // Hook for filament load and unload filament option
    static void HandleFilamentOption(DGUS_VP_Variable &var, void *val_ptr);
    // Hook for filament load and unload
    static void HandleFilamentLoadUnload(DGUS_VP_Variable &var);
  #endif

  #if ENABLED(SDSUPPORT)
    // Callback for VP "Display wants to change screen when there is a SD card"
    static void ScreenChangeHookIfSD(DGUS_VP_Variable &var, void *val_ptr);
    // Scroll buttons on the file listing screen.
    static void DGUSLCD_SD_ScrollFilelist(DGUS_VP_Variable &var, void *val_ptr);
    // File touched.
    static void DGUSLCD_SD_FileSelected(DGUS_VP_Variable &var, void *val_ptr);
    // start print after confirmation received.
    static void DGUSLCD_SD_StartPrint(DGUS_VP_Variable &var, void *val_ptr);
    // User hit the pause, resume or abort button.
    static void DGUSLCD_SD_ResumePauseAbort(DGUS_VP_Variable &var, void *val_ptr);
    static void DGUSLCD_SD_Enterdrybox(DGUS_VP_Variable &var, void *val_ptr);
	
    static void DGUSLCD_SD_FilamentResumePauseAbort(DGUS_VP_Variable &var, void *val_ptr);
	
    static void Filament_AutoHoming_Resume_Z();
    static void Filament_Runout_AutoRecovery();
    static void Set_Filament_Length(float input_AxisPosition_mm);
    static void Set_Filament_State();
    static void Reset_e_Position(float input_AxisPosition_mm);
	
    static bool GetFilamentState_Check();
    static void InitLevelData();

	
    // User confirmed the abort action
    static void DGUSLCD_SD_ReallyAbort(DGUS_VP_Variable &var, void *val_ptr);
    // User hit the tune button
    static void DGUSLCD_SD_PrintTune(DGUS_VP_Variable &var, void *val_ptr);
    // Send a single filename to the display.
    static void DGUSLCD_SD_SendFilename(DGUS_VP_Variable &var);
    // Marlin informed us that a new SD has been inserted.
    static void SDCardInserted();
    // Marlin informed us that the SD Card has been removed().
    static void SDCardRemoved();
    // Marlin informed us about a bad SD Card.
    static void SDCardError();
  #endif

  // OK Button the Confirm screen.
  static void ScreenConfirmedOK(DGUS_VP_Variable &var, void *val_ptr);

  // Update data after went to new screen (by display or by GotoScreen)
  // remember: store the last-displayed screen, so it can get returned to.
  // (e.g for pop up messages)
  static void UpdateNewScreen(DGUSLCD_Screens newscreen, bool popup=false);

  // Recall the remembered screen.
  static void PopToOldScreen();

  // Make the display show the screen and update all VPs in it.
  static void GotoScreen(DGUSLCD_Screens screen, bool ispopup = false);

  static void UpdateScreenVPData();

  // Helpers to convert and transfer data to the display.
  static void DGUSLCD_SendWordValueToDisplay(DGUS_VP_Variable &var);
  static void DGUSLCD_SendStringToDisplay(DGUS_VP_Variable &var);
  static void DGUSLCD_SendStringToDisplayPGM(DGUS_VP_Variable &var);
  static void DGUSLCD_SendTemperaturePID(DGUS_VP_Variable &var);
  static void DGUSLCD_SendPercentageToDisplay(DGUS_VP_Variable &var);
  static void DGUSLCD_SendPrintProgressToDisplay(DGUS_VP_Variable &var);
  static void DGUSLCD_SendPrintTimeToDisplay(DGUS_VP_Variable &var);

  #if ENABLED(PRINTCOUNTER)
    static void DGUSLCD_SendPrintAccTimeToDisplay(DGUS_VP_Variable &var);
    static void DGUSLCD_SendPrintsTotalToDisplay(DGUS_VP_Variable &var);
  #endif
  #if HAS_FAN
    static void DGUSLCD_SendFanStatusToDisplay(DGUS_VP_Variable &var);
  #endif
  static void DGUSLCD_SendHeaterStatusToDisplay(DGUS_VP_Variable &var);
  #if ENABLED(DGUS_UI_WAITING)
    static void DGUSLCD_SendWaitingStatusToDisplay(DGUS_VP_Variable &var);
  #endif

  // Send a value from 0..100 to a variable with a range from 0..255
  static void DGUSLCD_PercentageToUint8(DGUS_VP_Variable &var, void *val_ptr);

  template<typename T>
  static void DGUSLCD_SetValueDirectly(DGUS_VP_Variable &var, void *val_ptr) {
    if (!var.memadr) return;
    union { unsigned char tmp[sizeof(T)]; T t; } x;
    unsigned char *ptr = (unsigned char*)val_ptr;
    LOOP_L_N(i, sizeof(T)) x.tmp[i] = ptr[sizeof(T) - i - 1];
    *(T*)var.memadr = x.t;
  }

  // Send a float value to the display.
  // Display will get a 4-byte integer scaled to the number of digits:
  // Tell the display the number of digits and it cheats by displaying a dot between...
  template<unsigned int decimals>
  static void DGUSLCD_SendFloatAsLongValueToDisplay(DGUS_VP_Variable &var) {
    if (var.memadr) {
      float f = *(float *)var.memadr;
      f *= cpow(10, decimals);
      dgusdisplay.WriteVariable(var.VP, (long)f);
    }
  }

  // Send a float value to the display.
  // Display will get a 2-byte integer scaled to the number of digits:
  // Tell the display the number of digits and it cheats by displaying a dot between...
  template<unsigned int decimals>
  static void DGUSLCD_SendFloatAsIntValueToDisplay(DGUS_VP_Variable &var) {
    if (var.memadr) {
      float f = *(float *)var.memadr;
      //DEBUG_ECHOLNPAIR_F(" >> ", f, 6);
      f *= cpow(10, decimals);
      dgusdisplay.WriteVariable(var.VP, (uint16_t)f);
    }
  }

  // Force an update of all VP on the current screen.
  static inline void ForceCompleteUpdate() { update_ptr = 0; ScreenComplete = false; }
  // Has all VPs sent to the screen
  static inline bool IsScreenComplete() { return ScreenComplete; }

  static inline DGUSLCD_Screens getCurrentScreen() { return current_screen; }
  bool getFilament_Check_Flag() 			 		      { return Filament_Runout_Check_Flag; }
  void setFilament_Check_Flag(const bool value) { Filament_Runout_Check_Flag = value; }
  bool getFilament_Screen_State() 			 		      { return Filament_Runout_screen_state; }
  void setFilament_Screen_State(const bool value) { Filament_Runout_screen_state = value; }


  
  void printtest();

  static inline void SetupConfirmAction( void (*f)()) { confirm_action_cb = f; }

//DGUSLCD_UTILITIES_Deal
#if 0
  static void DGUSLCD_DEAL_EVENT(DGUS_VP_Variable &var);
#endif
  static void DGUSLCD_UTILITIES_Deal(DGUS_VP_Variable &var,void *val_ptr);
  static void DGUSLCD_UTILITIES_Leveling(DGUS_VP_Variable &var,void *val_ptr);
  static void DisplayLevelingZ(const_float_t zval,int8_t index);
  
  static void DGUSLCD_SYS_config(DGUS_VP_Variable &var,void *val_ptr);
  static void Periodic_task();
  static uint16_t	Get_drybox_targe_temp(void);
  static uint16_t	Fresh_Ui_Icon_Fun(void);


  static uint16_t filament_temp_u;
  static uint16_t filament_display_data;
  
  static uint16_t drybox_targe_temp;
//Back deal
  static void DisplayResumeFileName();
  static void SDPrintingFinished();
  static void DGUSLCD_BACK_Deal(DGUS_VP_Variable &var,void *val_ptr);
private:
  static constexpr uint8_t NUM_PAST_SCREENS = 4;
  static uint8_t update_ptr;		//< Last sent entry in the VPList for the actual screen.
  static uint8_t measure_index;
  static DGUSLCD_Screens current_screen;  //< currently on screen
  static DGUSLCD_Screens past_screens[NUM_PAST_SCREENS]; //< LIFO with past screens for the "back" button.
  static bool ScreenComplete;     //< All VPs sent to screen?
  static bool has_sdcar;
  static bool No_Refresh;
  static uint16_t motor_stper;
  static uint16_t ConfirmVP;      //< context for confirm screen (VP that will be emulated-sent on "OK").
  static uint16_t skipVP;         //< When updating the screen data, skip this one, because the user is interacting with it.

  #if ENABLED(SDSUPPORT)
    static int16_t top_file;      //< file on top of file chooser
    static int16_t file_to_print; //< touched file to be confirmed
    static int16_t gcode_file_offset; //
  #endif

  static void (*confirm_action_cb)();
};

#if ENABLED(POWER_LOSS_RECOVERY)//david need if 0
  #define PLR_SCREEN_RECOVER DGUSLCD_SCREEN_SDPRINTMANIPULATION
  #define PLR_SCREEN_CANCEL 100//DGUSLCD_SCREEN_STATUS
#endif
