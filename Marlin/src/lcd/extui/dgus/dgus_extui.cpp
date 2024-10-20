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

/**
 * lcd/extui/dgus/dgus_extui.cpp
 */

#include "../../../inc/MarlinConfigPre.h"

#if HAS_DGUS_LCD

#include "../ui_api.h"
#include "DGUSDisplay.h"
#include "DGUSDisplayDef.h"
#include "DGUSScreenHandler.h"
#include "../../../module/planner.h"

#include "../../../module/stepper.h"

namespace ExtUI {

  void onStartup(uint8_t lanague_tm) {
    dgusdisplay.InitDisplay();
	ScreenHandler.GotoScreen(DGUSLCD_SCREEN_BOOT);

    ScreenHandler.UpdateScreenVPData();
	//delay(800);

	if(lanague_tm==UI_LANGUAGE_CHINESE)
	{
		ScreenHandler.GotoScreen(DGUSLCD_CN_SCREEN_WELCOME);
	}
	else
	{
		ScreenHandler.GotoScreen(DGUSLCD_EN_SCREEN_BOOT);
	}	
	
	delay(2000);
	if(lanague_tm==UI_LANGUAGE_CHINESE)
	{
		ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_MAIN);
	}
	else
	{
		ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
	}
	uint8_t tmp=2;
	dgusdisplay.ReadVariable(VP_GetCFG, &tmp, 1, true);//get System_Config data addr == 0x0080
    ScreenHandler.UpdateScreenVPData();
  }

  void onIdle() { ScreenHandler.loop(); }

  void onPrinterKilled(PGM_P const error, PGM_P const component) {
    ScreenHandler.sendinfoscreen(GET_TEXT(MSG_HALTED), error, NUL_STR, GET_TEXT(MSG_PLEASE_RESET), true, true, true, true);
    ScreenHandler.GotoScreen(DGUSLCD_SCREEN_KILL);
    while (!ScreenHandler.loop());  // Wait while anything is left to be sent
  }

  void onMediaInserted() { TERN_(SDSUPPORT, ScreenHandler.SDCardInserted()); }
  void onMediaError()    { TERN_(SDSUPPORT, ScreenHandler.SDCardError()); }
  void onMediaRemoved()  { TERN_(SDSUPPORT, ScreenHandler.SDCardRemoved()); }
  void SDPrintingFinished()  { ScreenHandler.SDPrintingFinished(); }
  

  void onPlayTone(const uint16_t frequency, const uint16_t duration) {}
  void onPrintTimerStarted() {
  		
  	    if(ScreenHandler.power_loss_resume==0){ //david if no power loss print
			ScreenHandler.WaitMove();
			planner.synchronize();
  	    }

		if(GCodeQueue::is_online_print)
		{
			if(ui.language==UI_LANGUAGE_ENGLISH)		  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_ONLINEPRINT);		
			else										  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_ONLINEPRINT);
		
		}
		else
		{
			if((ScreenHandler.power_loss_state ==0))  //isFileOpen cura   
			{
				ScreenHandler.power_loss_cnt =0;
				{
					if(ui.language==UI_LANGUAGE_ENGLISH)		  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_STATUS);
					
					else										  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_STATUS);
				}					
			}	
			else //if((ScreenHandler.power_loss_state) &&(ScreenHandler.power_loss_cnt>=1))//power loss cnt two times
			{	
				ScreenHandler.power_loss_cnt++;
				
				ScreenHandler.power_loss_state =0;
			}
		}
  }
  void onPrintTimerPaused() {
		ScreenHandler.WaitMove();
	    ScreenHandler.temp_current_position_x=current_position.x;
	    ScreenHandler.temp_current_position_y=current_position.y;
	    ScreenHandler.temp_current_position_z=current_position.z;
	    ScreenHandler.temp_current_position_e=current_position.e;
		do_blocking_move_to_z(current_position.z+5);
		do_blocking_move_to_xy(0,0,50);
		planner.synchronize();
		do_blocking_move_to_z(current_position.z-5);
		planner.synchronize();
		if(ExtUI::getFilamentRunoutState()){
			if(ui.language==UI_LANGUAGE_CHINESE)	ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_NO_FILAMENT);
			else									ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_NO_FILAMENT);					
			ScreenHandler.Filament_Runout_AutoRecovery_State =1;
			ScreenHandler.Filament_Runout_AutoRecovery_Cnt++;						
		}
		else
		{
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_STATUS_PAUSE);
		  else		  								  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_STATUS_PAUSE);
		}
  	}
  void onPrintTimerStopped() {
		feedrate_percentage=100;
		ScreenHandler.temp_current_position_x=ScreenHandler.temp_current_position_y=ScreenHandler.temp_current_position_z=0;
  	}
  void onFilamentRunout(const extruder_t extruder,uint8_t err_code) {
	
	if(ui.language==UI_LANGUAGE_CHINESE)	ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);
	else									ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
	queue.ring_buffer.clear();
  }

  void onUserConfirmRequired(const char * const msg) {
    if (msg) {
      ScreenHandler.sendinfoscreen(PSTR("Please confirm."), nullptr, msg, nullptr, true, true, false, true);
      ScreenHandler.SetupConfirmAction(setUserConfirmed);
      ScreenHandler.GotoScreen(DGUSLCD_SCREEN_KILL);
//	  do{ MYSERIAL1.print(__FILE__); MYSERIAL1.println(__LINE__); }while(0);
    }
    else if (ScreenHandler.getCurrentScreen() == DGUSLCD_SCREEN_KILL ) {
      ScreenHandler.SetupConfirmAction(nullptr);
      ScreenHandler.PopToOldScreen();
//	  do{ MYSERIAL1.print(__FILE__); MYSERIAL1.println(__LINE__); }while(0);
    }
  }

  void onStatusChanged(const char * const msg) { ScreenHandler.setstatusmessage(msg); }

  void onHomingStart() {
	ScreenHandler.onHomingStart();
}
  void onHomingComplete(bool t) {
	ScreenHandler.onHomingComplete(t);
  }
  
  void onStartMove() {
	//ScreenHandler.onStartMove();
  }
  
  void onEndMove() {
	//ScreenHandler.onEndMove();
  }

  int16_t getZ_compensate()
  {
  	return ScreenHandler.z_compensate_adust;
  }
  void onPrintFinished() {}

  void onFactoryReset() {
		ScreenHandler.z_compensate_adust=0;
		ui.auto_level=1;
  	}

  void onStoreSettings(char *buff) {
    // Called when saving to EEPROM (i.e. M500). If the ExtUI needs
    // permanent data to be stored, it can write up to eeprom_data_size bytes
    // into buff.

    // Example:
    //  static_assert(sizeof(myDataStruct) <= eeprom_data_size);
    //  memcpy(buff, &myDataStruct, sizeof(myDataStruct));
    int save_index=0;
    static_assert(sizeof(uint16_t) <= eeprom_data_size);
	memcpy(buff+save_index, &ScreenHandler.z_compensate_adust, sizeof(uint16_t));
	save_index+=sizeof(uint16_t);
	memcpy(buff+save_index, &ui.auto_level, sizeof(ui.auto_level));
	save_index+=sizeof(ui.auto_level);
	memcpy(buff+save_index, &ui.auto_turn_off, sizeof(ui.auto_turn_off));
	save_index+=sizeof(ui.auto_turn_off);
 	memcpy(buff+save_index, &ui.select_fast_print, sizeof(ui.select_fast_print));
	save_index+=sizeof(ui.select_fast_print); 
	
    
  }

  void onLoadSettings(const char *buff) {
    // Called while loading settings from EEPROM. If the ExtUI
    // needs to retrieve data, it should copy up to eeprom_data_size bytes
    // from buff

    // Example:
    //  static_assert(sizeof(myDataStruct) <= eeprom_data_size);
    //  memcpy(&myDataStruct, buff, sizeof(myDataStruct));
    
    int load_index=0;
    static_assert(sizeof(uint16_t) <= eeprom_data_size);
	memcpy(&ScreenHandler.z_compensate_adust,buff+load_index,  sizeof(uint16_t));
	load_index += sizeof(uint16_t);
	memcpy(&ui.auto_level,buff+load_index,  sizeof(ui.auto_level));
	load_index += sizeof(ui.auto_level);
	memcpy(&ui.auto_turn_off,buff+load_index,  sizeof(ui.auto_turn_off));
	load_index += sizeof(ui.auto_turn_off);
 	memcpy(&ui.select_fast_print, buff + load_index, sizeof(ui.select_fast_print));
	load_index += sizeof(ui.select_fast_print); 
	ui.select_fast_print = fast_print_enable_pre=fast_print_enable = false;  // zcj
  }

  void onPostprocessSettings() {
    // Called after loading or resetting stored settings
  }

  void onConfigurationStoreWritten(bool success) {
    // Called after the entire EEPROM has been written,
    // whether successful or not.
  }

  void onConfigurationStoreRead(bool success) {
    // Called after the entire EEPROM has been read,
    // whether successful or not.
  }

  #if HAS_MESH
    void onMeshLevelingStart() {}

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const_float_t zval) {
      // Called when any mesh points are updated
    }

    void onMeshUpdate(const int8_t xpos, const int8_t ypos, const probe_state_t state) {
      // Called to indicate a special condition
    }

    void onMeshUpdate(const_float_t zval,int8_t index) {
      // Called when any mesh points are updated
	//do{ MYSERIAL1.print(__FILE__); MYSERIAL1.println(__LINE__); }while(0);
          ScreenHandler.DisplayLevelingZ(zval,index);
    }
  #endif

  #if ENABLED(POWER_LOSS_RECOVERY)
    void onPowerLossResume() {
      // Called on resume from power-loss
      if(ui.language==UI_LANGUAGE_CHINESE)
      IF_DISABLED(DGUS_LCD_UI_MKS, ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_POWER_LOSS));//david ��ʱ����
      else
      IF_DISABLED(DGUS_LCD_UI_MKS, ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_POWER_LOSS));//david ��ʱ����
      ScreenHandler.DisplayResumeFileName();
	  	
    }
  #endif

  #if HAS_PID_HEATING
    void onPidTuning(const result_t rst) {
      // Called for temperature PID tuning result
      switch (rst) {
        case PID_BAD_EXTRUDER_NUM:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_BAD_EXTRUDER_NUM));
          break;
        case PID_TEMP_TOO_HIGH:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_TEMP_TOO_HIGH));
          break;
        case PID_TUNING_TIMEOUT:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_TIMEOUT));
          break;
        case PID_DONE:
          ScreenHandler.setstatusmessagePGM(GET_TEXT(MSG_PID_AUTOTUNE_DONE));
          break;
        case PID_STARTED: break;
      }
      ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
    }
  #endif

  void onSteppersDisabled() {}
  void onSteppersEnabled()  {}
}

#endif // HAS_DGUS_LCD
