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

#include "../../../../inc/MarlinConfigPre.h"

#if ENABLED(DGUS_LCD_UI_SUNLU)

#include "../DGUSScreenHandler.h"

#include "../../../../MarlinCore.h"
#include "../../../../gcode/queue.h"
#include "../../../../libs/duration_t.h"
#include "../../../../module/settings.h"
#include "../../../../module/temperature.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"
#include "../../../../module/printcounter.h"
#include "../../../../sd/cardreader.h"
#include "../../ui_api.h"
#include "../../../../module/stepper.h"

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../../feature/powerloss.h"
#endif



#if ENABLED(SDSUPPORT)

  static ExtUI::FileList filelist;

  void DGUSScreenHandler::DGUSLCD_SD_FileSelected(DGUS_VP_Variable &var, void *val_ptr) {
	uint16_t touched_nr = (int16_t)swap16(*(uint16_t*)val_ptr) + top_file-1;
	if (touched_nr > filelist.count()) return;
	if (!filelist.seek(touched_nr)) return;
	#if ENABLED(DGUS_PRINT_FILENAME)
      // Send print filename
      DGUS_VP_Variable tvar;
	  char tmpfilename[VP_SD_FileName_LEN + 1] = "";
	  tvar.size=32;
	  tvar.VP=RTX_filename;
	  tvar.memadr=(void*)tmpfilename;
	  memset(tmpfilename,'\0',sizeof(tmpfilename));
	  snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s%c"), filelist.filename(), filelist.isDir() ? '/' : 0);
      DGUSLCD_SendStringToDisplay(tvar);
    #endif
	file_to_print = touched_nr;
	temp_runout_enable=ExtUI::getFilamentRunout_enabled();
    HandleUserConfirmationPopUp(VP_SD_FileSelectConfirm, nullptr, PSTR("Print file"), filelist.filename(), PSTR("from SD Card?"), true, true, false, true);
	No_Refresh=false;//david //The file list will be refreshed next time;
	Fresh_Ui_Icon_Fun();
  }

  void DGUSScreenHandler::DGUSLCD_SD_StartPrint(DGUS_VP_Variable &var, void *val_ptr) {
  	
    uint16_t result = (int16_t)swap16(*(uint16_t*)val_ptr);
    if (!filelist.seek(file_to_print) || result==2)
    {
    	PopToOldScreen();
		return;
    }
	ExtUI::setFilamentRunout_enabled(temp_runout_enable);
	
	ExtUI::injectCommands_P(PSTR("M500"));
    ExtUI::printFile(filelist.shortFilename());
  	if(ui.language==UI_LANGUAGE_CHINESE)
    	GotoScreen(DGUSLCD_SCREEN_CN_STATUS);
  	else
    	GotoScreen(DGUSLCD_SCREEN_EN_STATUS);
	No_Refresh=false;//david //The file list will be refreshed next time;
	
	thermalManager.set_dry_time();
	uint16_t Tmp_val = drybox_targe_temp+Temperature_Center_Offset;
	thermalManager.setTargetHotend_DRYBOX(Tmp_val);
	thermalManager.degTargetHotend_drybox(TEMP_DRYBOX_CENTER_PIN);
	ui.set_select_drybox_state(1);

	
  }


  void DGUSScreenHandler::Filament_AutoHoming_Resume_Z() 
 {
	 temp_current_position_z = current_position.z;
	 gcode.process_subcommands_now_P(PSTR("G28 X1 Y1"));
	 planner.synchronize();
	 current_position.z=temp_current_position_z;
	 do_blocking_move_to_z(current_position.z);
	 planner.synchronize();
 }

void DGUSScreenHandler::Set_Filament_Length(float input_AxisPosition_mm)
{
	  ExtUI::setAxisPosition_mm(input_AxisPosition_mm, filament_data.extruder);
	  planner.synchronize();
}
  
void DGUSScreenHandler::Set_Filament_State()
{
	ExtUI::ResetFilamentRunout();
	ExtUI::setTestFilamentRunoutState(true);
}
void DGUSScreenHandler::Reset_e_Position(float input_AxisPosition_mm)
{
	current_position.e=input_AxisPosition_mm;
	planner.set_e_position_mm(current_position.e);
	planner.synchronize();			

}

void DGUSScreenHandler::Filament_Runout_AutoRecovery() 
{
#ifdef	Cancel_FilamentRunout	
		Filament_AutoHoming_Resume_Z();
		if(ExtUI::getFilamentRunout_enabled()&0x03){//very important
			Set_Filament_State();
			ExtUI::setTestFilamentRunoutState(false);
		}

		float temp_AxisPosition_mm=ExtUI::getAxisPosition_mm(filament_data.extruder);
		if(ExtUI::getFilamentRunout_enabled()&0x03){
			ScreenHandler.setFilament_Check_Flag(true);
			Set_Filament_State();
			
			Set_Filament_Length(temp_AxisPosition_mm+6);
			Set_Filament_Length(temp_AxisPosition_mm+12);
			Set_Filament_Length(temp_AxisPosition_mm+18);
			
			ExtUI::setTestFilamentRunoutState(false);	
			if((ExtUI::getFilamentRunoutState())==0){	
				ScreenHandler.back_Fliament_State =true;
				Set_Filament_Length(temp_AxisPosition_mm+12);				
			}
			
		}
		Reset_e_Position(temp_AxisPosition_mm);

		if(ui.language==UI_LANGUAGE_CHINESE)	ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_CHANGE_FILAMENT);
		else									ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_CHANGE_FILAMENT);
		
		if((ExtUI::getFilamentRunoutState())==0){
			if (ExtUI::get_has_run_out()==0) 
			{
				
			  ExtUI::resumePrint();
			}
			else	
			{
			ScreenHandler.setFilament_Check_Flag(false);
			
			ExtUI::setFilamentRunoutState(true);//close
			}
		}			
#endif
}


  
void DGUSScreenHandler::DGUSLCD_SD_Enterdrybox(DGUS_VP_Variable &var, void *val_ptr) {
	uint16_t Tmp_val =0;
	static bool drybox_state =0;
	
	switch(var.VP)
	{
		case Back_RK_returndrybox:
			PopToOldScreen();
		break;	
		case OnlineReturn_drybox:
		{
			//do{ MYSERIAL1.print("TmpReturn_drybox ="); MYSERIAL1.println(TmpReturn_drybox); }while(0);
			
			PopToOldScreen();
		}
		break;
		case VP_SD_Print_drybox:		
		if(thermalManager.degdrybox()<-9){
		
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_N0_CN_DTYBOX);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_N0_EN_DTYBOX);
			}				
		}
		else{
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				if(ui.select_drybox){
					GotoScreen(DGUSLCD_SCREEN_CN_DTYBOX_TWO_OTHER);
					
				}
				else{
					GotoScreen(DGUSLCD_SCREEN_CN_DTYBOXOTHER);			
				}				
			}
			else
			{
				if(ui.select_drybox){
					GotoScreen(DGUSLCD_SCREEN_EN_DTYBOX_TWO_OTHER);
					
				}
				else{
					GotoScreen(DGUSLCD_SCREEN_EN_DTYBOXOTHER);			
				}
			}
		}
		
		int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
		if(ui.select_drybox)
			ui.select_drybox=false;
		else
			ui.select_drybox=true;
		
		if(thermalManager.degdrybox()<-9){
			thermalManager.stop_dry_work();	
			ui.set_select_drybox_state(false);
		}
		break;				
		default:
		break;
	}


}

  void DGUSScreenHandler::DGUSLCD_SD_ResumePauseAbort(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t touched_nr = (int16_t)swap16(*(uint16_t*)val_ptr);

    switch (swap16(*(uint16_t*)val_ptr)) {
	case 0://  pause print
		if(ui.language==UI_LANGUAGE_ENGLISH)		GotoScreen(DGUSLCD_SCREEN_EN_PAUSE_SELECT);
		else										GotoScreen(DGUSLCD_SCREEN_CN_PAUSE_SELECT);
	break;
		
	  case 3: { // Resume
			planner.plan_ignore_e = false;
			power_loss_resume=0;
			if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
			else										  GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing
			
			Filament_AutoHoming_Resume_Z();

#ifdef Filament_Check_Process
		
			float temp_AxisPosition_mm=ExtUI::getAxisPosition_mm(filament_data.extruder);	
			Set_Filament_State();

			Set_Filament_Length(temp_AxisPosition_mm+6);
			Set_Filament_Length(temp_AxisPosition_mm+12);
			Set_Filament_Length(temp_AxisPosition_mm+18);
			ExtUI::setTestFilamentRunoutState(false);			
			Reset_e_Position(temp_AxisPosition_mm);

#endif
			 back_e =0;
			 ExtUI::resumePrint();			

	  }
		break;	


      case 1: // Pause     
        if (!ExtUI::isPrintingFromMediaPaused()) 
		{
			
          ExtUI::pausePrint();
        }
        break;
      case 2: // Abort
  
		  planner.plan_ignore_e = false;
		  ExtUI::ResetFilamentRunout();
      	  ExtUI::stopPrint();
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing
			
      	  planner.synchronize();
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_MAIN);
		  Fresh_Ui_Icon_Fun();	  
		  thermalManager.stop_dry_work();
        break;
	  case 4:
		if(ScreenHandler.getFilament_Screen_State()){	
			ScreenHandler.setFilament_Screen_State(false);
			GotoScreen(DGUSLCD_SCREEN_CN_CHANGE_FILAMENT);
		}
		else
	  	PopToOldScreen();
	  break;
	  case 5://cancel jump
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_CANCEL_SELECT);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_CANCEL_SELECT);
	  break;
	  case 7://start print
	  
		  ScreenHandler.setFilament_Screen_State(true);
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_PRINTINGCONTINUE);
		  else										  GotoScreen(DGUSLCD_SCREEN_CN_PRINTINGCONTINUE);
	  break;
     	default:
     	break;
    }
  }



    void DGUSScreenHandler::DGUSLCD_SD_FilamentResumePauseAbort(DGUS_VP_Variable &var, void *val_ptr){
    uint16_t touched_nr = (int16_t)swap16(*(uint16_t*)val_ptr);
    switch (swap16(*(uint16_t*)val_ptr)) {
	case 0://  pause print
		if(ui.language==UI_LANGUAGE_ENGLISH)		GotoScreen(DGUSLCD_SCREEN_EN_PAUSE_SELECT);
		else										GotoScreen(DGUSLCD_SCREEN_CN_PAUSE_SELECT);
	break;
		
      case 3: { // Resume
	   	    ScreenHandler.Filament_Runout_AutoRecovery_Cnt =0;	  
		    planner.plan_ignore_e = false;
		    power_loss_resume=0;
			if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
			else		  								  GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing
			Filament_AutoHoming_Resume_Z();

			float temp_AxisPosition_mm =0;
		    if(ExtUI::getFilamentRunoutState()){
	      		if(ExtUI::getFilamentRunout_enabled()&0x03){
					ExtUI::ResetFilamentRunout();
	      		}

	      		if(back_e!=0)		temp_AxisPosition_mm=back_e;
				else				temp_AxisPosition_mm=ExtUI::getAxisPosition_mm(filament_data.extruder);		
				Reset_e_Position(temp_AxisPosition_mm);
				
		    }
			if(back_e!=0)		temp_AxisPosition_mm=back_e;
			else				temp_AxisPosition_mm=ExtUI::getAxisPosition_mm(filament_data.extruder);
			
			Reset_e_Position(temp_AxisPosition_mm);
			back_e =0;
	        ExtUI::resumePrint();			  
      } break;
      case 1: // Pause
        if (!ExtUI::isPrintingFromMediaPaused()) {
			if(ui.language==UI_LANGUAGE_ENGLISH)		  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
			else		  								  ScreenHandler.GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing
          ExtUI::pausePrint();
        }
        break;
      case 2: // Abort
     	
 		  planner.plan_ignore_e = false;
		  ExtUI::ResetFilamentRunout();
		  ScreenHandler.Filament_Runout_AutoRecovery_Cnt =0;
      	  ExtUI::stopPrint();
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing			
      	  planner.synchronize();
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_MAIN);
     
		  thermalManager.stop_dry_work();
        break;
	  case 4:
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_CHANGE_FILAMENT);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_CHANGE_FILAMENT);

	  break;
	  case 5://cancel jump
		  if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_FILAMENT_CANCEL);
		  else		  								  GotoScreen(DGUSLCD_SCREEN_CN_FILAMENT_CANCEL);
	  break;
	  case 7://start print
	  break;
     	default:
     	break;
    }
  } 
    
  void DGUSScreenHandler::DGUSLCD_SD_SendFilename(DGUS_VP_Variable& var) {

	static uint8_t findex=0;
	if(No_Refresh)	return;
	if(var.VP==VP_RTX_sdfile_col_4)	{
		No_Refresh=true;
	}
    uint16_t target_line = (var.VP - VP_RTX_sdfile_col_1) / VP_SD_FileName_LEN;////VP_SD_FileName0
    char tmpfilename[VP_SD_FileName_LEN + 1] = "";
    char tmpfilename_NULL[VP_SD_FileName_LEN + 1] = "";
    var.memadr = (void*)tmpfilename;
	if (filelist.seek(top_file + target_line)) {
	  snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s%c"), filelist.filename(), filelist.isDir() ? '/' : 0); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
	}
	else {
		//memset(tmpfilename,' ',sizeof(tmpfilename));
	   	var.memadr = (void*)tmpfilename_NULL;
	   	DGUSLCD_SendStringToDisplay(var);
		return;
	}
	
	var.memadr = (void*)tmpfilename_NULL;
	DGUSLCD_SendStringToDisplay(var);
	var.memadr = (void*)tmpfilename;
	DGUSLCD_SendStringToDisplay(var);

  }

  void DGUSScreenHandler::SDCardInserted() {
    top_file = 0;
	gcode_file_offset=0;
    filelist.refresh();
	has_sdcar=true;
    auto cs = getCurrentScreen();
    if (cs == DGUSLCD_SCREEN_CN_MAIN ||cs == DGUSLCD_SCREEN_EN_MAIN || cs == DGUSLCD_SCREEN_SDFILELIST_NULL|| cs == DGUSLCD_SCREEN_SDFILELIST_NULL_CN ){
    }
  }

  void DGUSScreenHandler::SDCardRemoved() {
	has_sdcar=false;
    if (current_screen == DGUSLCD_SCREEN_EN_SDFILELIST || current_screen == DGUSLCD_SCREEN_CN_SDFILELIST)
	{
		if(ui.language==UI_LANGUAGE_ENGLISH)      GotoScreen(DGUSLCD_SCREEN_SDFILELIST_NULL);
		else									  GotoScreen(DGUSLCD_SCREEN_SDFILELIST_NULL_CN);
    }
  }
  void DGUSScreenHandler::IntoSleep()
  {
  	uint8_t System_Config[4];
	memcpy(System_Config,System_Config_0X80_D1,sizeof(System_Config));	
	System_Config[0]=0x5A;	
	System_Config[1]=0x14;
	System_Config[2]=0x03;
	System_Config[3]=0x3C;
		
	dgusdisplay.WriteVariable(VP_GetCFG, System_Config, sizeof(System_Config), true);
  }
  void DGUSScreenHandler::OutoSleep()
  {
   	uint8_t System_Config[4];
	memcpy(System_Config,System_Config_0X80_D1,sizeof(System_Config));	
	System_Config[0]=0x5A;	
	System_Config[1]=0x14;
	System_Config[2]=0x03;
	System_Config[3]=0x38;			
	dgusdisplay.WriteVariable(VP_GetCFG, System_Config, sizeof(System_Config), true); 	
  }
  void DGUSScreenHandler::WaitMove()
  {
	if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
	else		  								  GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing
  	while(ExtUI::isMoving())	planner.synchronize();	 	
  }
  void DGUSScreenHandler::SDPrintingFinished() {

	WaitMove();
	thermalManager.stop_dry_work();
    if(ui.language==UI_LANGUAGE_CHINESE)    GotoScreen(DGUSLCD_SCREEN_CN_PRINTINGFINISHED);
	else									GotoScreen(DGUSLCD_SCREEN_EN_PRINTINGFINISHED);  	
    if (ui.auto_turn_off) {
      queue.exhaust();
	  queue.ring_buffer.clear();
	  IntoSleep();
      thermalManager.setTargetHotend(0, 0);
	  thermalManager.setTargetBed(0);	
      gcode.process_subcommands_now_P(PSTR("M81"));
    }
    gcode.process_subcommands_now_P(PSTR("M18 Z0"));
  }

#endif // SDSUPPORT

void DGUSScreenHandler::ScreenChangeHook(DGUS_VP_Variable &var, void *val_ptr) {
  uint8_t *tmp = (uint8_t*)val_ptr;

  // The keycode in target is coded as <from-frame><to-frame>, so 0x0100A means
  // from screen 1 (main) to 10 (temperature). DGUSLCD_SCREEN_POPUP is special,
  // meaning "return to previous screen"
  DGUSLCD_Screens target = (DGUSLCD_Screens)tmp[1];

  DEBUG_ECHOLNPAIR("\n DEBUG target", target);

  if (target == DGUSLCD_SCREEN_POPUP) {
    // Special handling for popup is to return to previous menu
    if (current_screen == DGUSLCD_SCREEN_POPUP && confirm_action_cb) confirm_action_cb();
    PopToOldScreen();
    return;
  }

  UpdateNewScreen(target);
  #ifdef DEBUG_DGUSLCD
    if (!DGUSLCD_FindScreenVPMapList(target)) DEBUG_ECHOLNPAIR("WARNING: No screen Mapping found for ", target);
  #endif
}

void DGUSScreenHandler:: HandleManualMove(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleManualMove");
  int16_t movevalue = 0;//swap16(*(uint16_t*)val_ptr);
  char axiscode;
  unsigned int speed = 1500; // FIXME: get default feedrate for manual moves, dont hardcode.
  uint8_t Z_ADD =0,Z_SUB =0;
  static millis_t get_cur_time=0,get_last_time=0;  
  switch (var.VP) {

    case VP_RK_move_x_r:	
  	  movevalue=0-motor_stper;
	  if(current_position.x<=0)	return;
	  if(current_position.x-(movevalue/100)<=0)
		movevalue=current_position.x*100;
      axiscode = 'X';
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
      break;
    case VP_RK_move_x_p:
		
  	  movevalue=motor_stper;
      axiscode = 'X';
      if (!ExtUI::canMove(ExtUI::axis_t::X)) goto cannotmove;
      break;

    case VP_RK_move_y_r:
		
  	  movevalue=0-motor_stper;
	  if(current_position.y<=0)	return;
	  if(current_position.y-(movevalue/100)<=0)
		movevalue=current_position.y*100;
      axiscode = 'Y';
      if (!ExtUI::canMove(ExtUI::axis_t::Y)) goto cannotmove;
      break;
    case VP_RK_move_y_p:
		
      axiscode = 'Y';
  	  movevalue=motor_stper;
      if (!ExtUI::canMove(ExtUI::axis_t::Y)) goto cannotmove;
      break;

    case VP_RK_move_z_r:
	  	Z_SUB =1;
	  
      if(current_screen==DGUSLCD_SCREEN_CN_LEVELING ||
	  	current_screen==DGUSLCD_SCREEN_EN_LEVELING ||
	  	current_screen==DGUSLCD_SCREEN_EN_LEVELING_Child ||
	  	current_screen==DGUSLCD_SCREEN_CN_LEVELING_Child ||
	  	current_screen==DGUSLCD_SCREEN_EN_LEVELING_Child_OVER ||
	  	current_screen==DGUSLCD_SCREEN_CN_LEVELING_Child_OVER )	
      	{
			if(planner.position.z==0)
			{
				planner.position.z+=40;
				z_compensate_adust+=40;
				ExtUI::setProbeOffset_Z_mm(-0.1);
				save_par=true;
				smile_adjustZ=true;
			}
      	}
	  
  	  movevalue=0-motor_stper;
      if(current_screen==DGUSLCD_SCREEN_CN_AXIS_PAGE ||
	  	current_screen==DGUSLCD_SCREEN_ONE_EN_AXIS_PAGE ||
	  	current_screen==DGUSLCD_SCREEN_TEN_EN_AXIS_PAGE ||
	  	current_screen==DGUSLCD_SCREEN_ONE_CN_AXIS_PAGE ||
	  	current_screen==DGUSLCD_SCREEN_TWO_CN_AXIS_PAGE ||
	  	current_screen==DGUSLCD_SCREEN_THREE_CN_AXIS_PAGE ){
		if(!smile_adjustZ)
		{
			  if(current_position.z<=0) return; 
			  if(current_position.z-(abs(movevalue)/100)<=0)
				movevalue=-(current_position.z*100);
		}
	    if(movevalue ==0)
		  return;  	
   
      	}
	 	else{
		if(!smile_adjustZ)
		  {
			  if(current_position.z<=0)	return; 
			  if(current_position.z-(movevalue/100)<=0)
				movevalue=-(current_position.z*100);
		  }
	  }
	  	
      speed = 300; // default to 5mm/s
      if (!ExtUI::canMove(ExtUI::axis_t::Z)) goto cannotmove;
      break;
    case VP_RK_move_z_p:
  	  movevalue=motor_stper;
      axiscode = 'Z';	
	  Z_ADD =1;
      speed = 300; // default to 5mm/s
      
      if(current_screen==DGUSLCD_SCREEN_CN_LEVELING ||
	  	current_screen==DGUSLCD_SCREEN_EN_LEVELING ||
	  	current_screen==DGUSLCD_SCREEN_EN_LEVELING_Child ||
	  	current_screen==DGUSLCD_SCREEN_CN_LEVELING_Child ||
	  	current_screen==DGUSLCD_SCREEN_EN_LEVELING_Child_OVER ||
	  	current_screen==DGUSLCD_SCREEN_CN_LEVELING_Child_OVER )
	  	
      	{
			if(z_compensate_adust<0)//zb
			{
				z_compensate_adust=0;
				ExtUI::setProbeOffset_mm(0,2);
			}
			else
			{
				z_compensate_adust-=40;
				ExtUI::setProbeOffset_Z_mm(+0.1);
			}
			
			save_par=true;
			smile_adjustZ=true;
      	}
      if (!ExtUI::canMove(ExtUI::axis_t::Z)) goto cannotmove;
      break;

    case VP_RK_home_all: // only used for homing
      axiscode  = '\0';
      movevalue = 0; // ignore value sent from display, this VP is _ONLY_ for homing.
      break;
    case VP_RK_home_x: // only used for homing
      axiscode  = 'X';
      movevalue = 0; // ignore value sent from display, this VP is _ONLY_ for homing.
      break;
    case VP_RK_home_y: // only used for homing
      axiscode  = 'Y';
      movevalue = 0; // ignore value sent from display, this VP is _ONLY_ for homing.
      break;
    case VP_RK_home_z: // only used for homing
      axiscode  = 'Z';
      movevalue = 0; // ignore value sent from display, this VP is _ONLY_ for homing.
      break;
  }

  if (!movevalue) {
    // homing
    DEBUG_ECHOPAIR(" homing ", AS_CHAR(axiscode));
    char buf[6] = "G28 X";
    buf[4] = axiscode;
    queue.enqueue_one_now(buf);
    motor_stper=10;//david for reset 0.1
    ForceCompleteUpdate();
    return;
  }
  else {
    // movement
	if(Z_SUB||Z_ADD)
	{
 		 get_cur_time=millis();
		 if(get_cur_time-get_last_time<800)
		 {
			 return;	
		 }
		 else 
		 {
			 get_last_time=get_cur_time;
		
		 }	
	}

	if(motor_stper == VP_RK_10_step)
	{
		if (ExtUI::isMoving()) return ;
	}
	
    DEBUG_ECHOPAIR(" move ", AS_CHAR(axiscode));
    bool old_relative_mode = relative_mode;
    if (!relative_mode ) {
      queue.enqueue_now_P(PSTR("G91"));
    }
    char buf[32]; // G1 X9999.99 F12345
    unsigned int backup_speed = MMS_TO_MMM(feedrate_mm_s);
    char sign[] = "\0";
    int16_t value = movevalue / 100;
    if (movevalue < 0) { value = -value; sign[0] = '-';}
    int16_t fraction = ABS(movevalue) % 100;
    snprintf_P(buf, 32, PSTR("G0 %c%s%d.%02d F%d"), axiscode, sign, value, fraction, speed);
    queue.enqueue_one_now(buf);
    if (backup_speed != speed) {
      snprintf_P(buf, 32, PSTR("G0 F%d"), backup_speed);
      queue.enqueue_one_now(buf);
    }
    if (!old_relative_mode) {
      queue.enqueue_now_P(PSTR("G90"));
    }
	smile_adjustZ=false;
  }

  ForceCompleteUpdate();
  DEBUG_ECHOLNPGM("manmv done.");
  return;

  cannotmove:
    DEBUG_ECHOLNPAIR(" cannot move ", AS_CHAR(axiscode));
    return;
}

#if HAS_PID_HEATING
  void DGUSScreenHandler::HandleTemperaturePIDChanged(DGUS_VP_Variable &var, void *val_ptr) {
  #ifndef DGUS_LCD_UI_SUNLU
    uint16_t rawvalue = swap16(*(uint16_t*)val_ptr);
    DEBUG_ECHOLNPAIR("V1:", rawvalue);
    float value = (float)rawvalue / 10;
    DEBUG_ECHOLNPAIR("V2:", value);
    float newvalue = 0;

    switch (var.VP) {
      default: return;
        #if HOTENDS >= 1
          case VP_E0_PID_P: newvalue = value; break;
          case VP_E0_PID_I: newvalue = scalePID_i(value); break;
          case VP_E0_PID_D: newvalue = scalePID_d(value); break;
        #endif
        #if HOTENDS >= 2
          case VP_E1_PID_P: newvalue = value; break;
          case VP_E1_PID_I: newvalue = scalePID_i(value); break;
          case VP_E1_PID_D: newvalue = scalePID_d(value); break;
        #endif
        #if HAS_HEATED_BED
          case VP_BED_PID_P: newvalue = value; break;
          case VP_BED_PID_I: newvalue = scalePID_i(value); break;
          case VP_BED_PID_D: newvalue = scalePID_d(value); break;
        #endif
    }

    DEBUG_ECHOLNPAIR_F("V3:", newvalue);
    *(float *)var.memadr = newvalue;

    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
    #endif
  }
#endif // HAS_PID_HEATING

#if ENABLED(BABYSTEPPING)
  void DGUSScreenHandler::HandleLiveAdjustZ(DGUS_VP_Variable &var, void *val_ptr) {

    int16_t flag  = 0;//swap16(*(uint16_t*)val_ptr),
  	switch(var.VP)
  	{
  		case VP_SD_Print_LiveAdjustZ_up:
			flag=20;
		break;
		case VP_SD_Print_LiveAdjustZ_down:
			flag=-20;
		break;
  	}
    int16_t  steps = flag;// ? -20 : 20;
    ExtUI::smartAdjustAxis_steps(steps, ExtUI::axis_t::Z, true);
    ForceCompleteUpdate();
	save_par=true;
	
  }
#endif

#if ENABLED(DGUS_FILAMENT_LOADUNLOAD)

  void DGUSScreenHandler::HandleFilamentOption(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleFilamentOption");
	if(back_e==0)
	{
		back_e=ExtUI::getAxisPosition_mm(filament_data.extruder);
	}
    filament_data.heated = false;
	char str[11]="\0";
	int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
	switch(var.VP)
	{
		case VP_RK_load_filament:
		{
      		filament_data.action = 1;
		}
		break;
		case VP_RK_unload_filament:
      		filament_data.action = 2;
		break;
	}
	if(en==1)	filament_data.purge_length = 100;
    else		filament_data.purge_length = Filament_Len;
    filament_data.extruder = ExtUI::extruder_t::E0;
	if (!(thermalManager.hotEnoughToExtrude(filament_data.extruder) && \
        thermalManager.targetHotEnoughToExtrude(filament_data.extruder)))
	{
	 	thermalManager.setTargetHotend(filament_temp_u, filament_data.extruder);
	}		
	if(ExtUI::isMoving())	return;		
	memset(str,'\0',sizeof(str));
	if(filament_data.action ==1) 	sprintf(str,"M701 L%d",int(filament_data.purge_length));
	else 						 	sprintf(str,"M702 U%d",int(filament_data.purge_length));
	if(current_screen==DGUSLCD_SCREEN_CN_CHANGE_FILAMENT )
	{
		if(ui.language==UI_LANGUAGE_CHINESE)
			GotoScreen(DGUSLCD_SCREEN_CN_WAITOPERATE);
		else
			GotoScreen(DGUSLCD_SCREEN_EN_WAITOPERATE);

	}
	else
	{
		if(ui.language==UI_LANGUAGE_CHINESE)
			GotoScreen(DGUSLCD_SCREEN_CN_WAITHEATING);
		else
			GotoScreen(DGUSLCD_SCREEN_EN_WAITHEATING);

	}
	gcode.process_subcommands_now(str);
	PopToOldScreen();

  }
#endif // DGUS_FILAMENT_LOADUNLOAD

void DGUSScreenHandler::DisplayResumeFileName()
{
	 DGUS_VP_Variable tvar;
	char tmpfilename[VP_SD_FileName_LEN + 1] = "";
	 tvar.size=32;
	 tvar.VP=RTX_filename;
	 tvar.memadr=(void*)tmpfilename;
	 memset(tmpfilename,'\0',sizeof(tmpfilename));
	 snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s%s"), recovery.info.last_filename, "power");
	 DGUSLCD_SendStringToDisplay(tvar);
}

void DGUSScreenHandler::DGUSLCD_BACK_Deal(DGUS_VP_Variable &var,void *val_ptr)
{
	switch(var.VP)
	{
		case Back_RK_returnmain:
		{
			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(ui.language == UI_LANGUAGE_ENGLISH)			GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
			else											GotoScreen(DGUSLCD_SCREEN_CN_MAIN);
			if(en==1)
			{
				OutoSleep();
				
			}
			No_Refresh=false;//david //The file list will be refreshed next time;
		}
		break;
		case Back_RK_returnutilities:
		{
			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(ui.language == UI_LANGUAGE_ENGLISH)			GotoScreen(DGUSLCD_SCREEN_EN_UTILITIES);
			else											GotoScreen(DGUSLCD_SCREEN_CN_UTILITIES);
//			PopToOldScreen();
			if(save_par)	{ExtUI::injectCommands_P(PSTR("M500"));save_par=false;}
		}
		break;
		case Back_RK_returnleveling:
			if(ui.language == UI_LANGUAGE_ENGLISH)
			{
				GotoScreen(DGUSLCD_SCREEN_EN_LEVELING_Child);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_CN_LEVELING_Child);			
			}
		break;
		default:
		break;
	}
}




void DGUSScreenHandler::DisplayLevelingZ(const_float_t zval,int8_t index) {

	float f = zval;
    f *= cpow(10, 3);
	measure_index=index;
  	dgusdisplay.WriteVariable(VP_Num_Point_1+((index-1)*2),(uint16_t)f );
	if(index<16)  	dgusdisplay.WriteVariable(VP_Num_Point_1+((index)*2),0 );
	if(index==15)	queue.enqueue_one_P(PSTR("M500"));
	if(current_screen==DGUSLCD_SCREEN_CN_MENSUR_LEVEL|| current_screen==DGUSLCD_SCREEN_EN_MENSUR_LEVEL){
		if(measure_index==((GRID_MAX_POINTS_X) * (GRID_MAX_POINTS_Y)))
		{
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_CN_LEVELING_Child_OVER);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_EN_LEVELING_Child_OVER);
			}
			measure_index=0;
		}
	}
}
void DGUSScreenHandler::DGUSLCD_UTILITIES_Leveling(DGUS_VP_Variable &var,void *val_ptr)
{
	switch(var.VP)
	{
		case VP_RK_Aux_Level:
		{
		
			int16_t index = (int16_t)swap16(*(uint16_t*)val_ptr);
			switch(index)
			{
				case 1:
					queue.enqueue_one_P(PSTR("G0 Z5.0"));
					queue.enqueue_one_P(PSTR("G0 X155 G0 Y155"));
					queue.enqueue_one_P(PSTR("G0 Z0.0"));
				break;
				case 2:
					queue.enqueue_one_P(PSTR("G0 Z5.0"));
					queue.enqueue_one_P(PSTR("G0 X72.5 G0 Y72.5"));
					queue.enqueue_one_P(PSTR("G0 Z0.0"));
				break;
				case 3:
					queue.enqueue_one_P(PSTR("G0 Z5.0"));
					queue.enqueue_one_P(PSTR("G0 X227.5 G0 Y72.5"));
					queue.enqueue_one_P(PSTR("G0 Z0.0"));
				break;
				case 4:
					queue.enqueue_one_P(PSTR("G0 Z5.0"));
					queue.enqueue_one_P(PSTR("G0 X227.5 G0 Y227.5"));
					queue.enqueue_one_P(PSTR("G0 Z0.0"));
				break;
				case 5:
					queue.enqueue_one_P(PSTR("G0 Z5.0"));
					queue.enqueue_one_P(PSTR("G0 X72.5 G0 Y227.5"));
					queue.enqueue_one_P(PSTR("G0 Z0.0"));
				break;
			}
		}
		break;
		case VP_RK_Leveling:
		{
			motor_stper=10;
			measure_index=0;			
			{
				ExtUI::injectCommands_P(PSTR("G28"));
				if(ui.language==UI_LANGUAGE_CHINESE)		    GotoScreen(DGUSLCD_SCREEN_CN_LEVELING_Child);
				else if(ui.language==UI_LANGUAGE_ENGLISH)		GotoScreen(DGUSLCD_SCREEN_EN_LEVELING_Child);
				InitLevelData();
			}
		}
		break;
		case VP_RK_Measure_Level:
			if(measure_index==0){
				if(ui.language == UI_LANGUAGE_CHINESE)	GotoScreen(DGUSLCD_SCREEN_CN_MENSUR_LEVEL);
				else									GotoScreen(DGUSLCD_SCREEN_EN_MENSUR_LEVEL);
				ExtUI::injectCommands_P(PSTR("G29"));
			}
			else if(measure_index==((GRID_MAX_POINTS_X) * (GRID_MAX_POINTS_Y)))
			{
				if(ui.language == UI_LANGUAGE_CHINESE)	GotoScreen(DGUSLCD_SCREEN_CN_LEVELING_Child_OVER);
				else									GotoScreen(DGUSLCD_SCREEN_EN_LEVELING_Child_OVER);
			}
		break;
		default:
		break;
	}
}

void DGUSScreenHandler::DGUSLCD_SYS_config(DGUS_VP_Variable &var,void *val_ptr)
{
	switch(var.VP)
	{
		case VP_GetCFG:
		{
			uint8_t System_Config[4];
			memcpy(System_Config,(uint8_t*)val_ptr,sizeof(System_Config));
			memcpy(System_Config_0X80_D1,System_Config,sizeof(System_Config));
		}
		break;
	}
}
uint16_t  DGUSScreenHandler::Fresh_Ui_Icon_Fun(void)
{
	if(ui.select_drybox)
	{
	//
	}
	else
	{	
	//
	}	
}

void DGUSScreenHandler::DGUSLCD_UTILITIES_Deal(DGUS_VP_Variable &var,void *val_ptr)
{
	uint16_t Tmp_val =0;
	switch(var.VP)
	{
		case VP_RK_Fastprint:
		{
			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(en==1)
			{
				ui.select_fast_print=false;
			}	
			else
			{
				ui.select_fast_print = true;;
			}
			//settings.set_eeprom_save_par_enabled(true);
			save_par=true;
			//ExtUI::injectCommands_P(PSTR("M500"));
			ForceCompleteUpdate();		
			
			do{ MYSERIAL1.print("VP_RK_Fastprint:"); MYSERIAL1.println(ui.select_fast_print); }while(0);
			do{ MYSERIAL1.print("GetPrintSpeedMode:"); MYSERIAL1.println(stepper.GetPrintSpeedMode()); }while(0);
		}
		break;

		case E_VP_UI_PK_PRINT:
		    top_file = 0;
			gcode_file_offset=0;
		    filelist.refresh();
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				if(has_sdcar)	GotoScreen(DGUSLCD_SCREEN_CN_SDFILELIST);
				else			GotoScreen(DGUSLCD_SCREEN_SDFILELIST_NULL_CN);
			}
			else
			{
				if(has_sdcar)	GotoScreen(DGUSLCD_SCREEN_EN_SDFILELIST);
				else			GotoScreen(DGUSLCD_SCREEN_SDFILELIST_NULL);
			}
		break;
		case E_VP_UI_RK_UTILITIES:
		{	
			
			//do{ MYSERIAL1.print("E_VP_UI_RK_UTILITIES"); }while(0);
			motor_stper=10;//0.1*100;
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_CN_UTILITIES);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_EN_UTILITIES);
			}	
		}
		break;
		case E_VP_UI_RK_INFO:
		{
			
	  		gcode.process_subcommands_now_P(PSTR("M18"));	  
	  		gcode.process_subcommands_now_P(PSTR("M84"));	
			queue.enqueue_one_P(PSTR("M18"));
				queue.enqueue_one_P(PSTR("M84"));
			planner.synchronize();		
			sendsoftwareversionscreen(GET_TEXT(MSG_SOTFWARE_VERSION));
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_CN_INFO);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_EN_INFO);
			}
		}	
		break;
		case VP_RK_Temp:
		{
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_CN_TEMP);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_EN_TEMP);
			}
		}
		break;
		case VP_RK_Axis:
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_CN_AXIS_PAGE);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_EN_AXIS_PAGE);
			}
			
    		motor_stper=10;//david for reset 0.1
		break;
		case VP_RK_Filament:
			if(ui.language == UI_LANGUAGE_CHINESE)
			{
				GotoScreen(DGUSLCD_SCREEN_CN_FILAMENT_PAGE);
			}
			else
			{
				GotoScreen(DGUSLCD_SCREEN_EN_FILAMENT_PAGE);
			}
		break;
		case VP_RK_DryBox:
			
        	if(thermalManager.degdrybox()<-9)
        	{
				if(ui.language == UI_LANGUAGE_CHINESE)
				{
					GotoScreen(DGUSLCD_SCREEN_CN_TEST_DRYBOX);
				}
				else
				{
					GotoScreen(DGUSLCD_SCREEN_EN_TEST_DRYBOX);
				}        		
        	}
			else{
				if(ui.language == UI_LANGUAGE_CHINESE)
				{
					if(ui.select_drybox){
						GotoScreen(DGUSLCD_SCREEN_CN_DTYBOX_OTHER);
						
					}
					else{
						GotoScreen(DGUSLCD_SCREEN_CN_DRYBOX);			
					}
				}
				else
				{
					if(ui.select_drybox){
						GotoScreen(DGUSLCD_SCREEN_EN_DTYBOX_OTHER);
						
					}
					else{
						GotoScreen(DGUSLCD_SCREEN_EN_DRYBOX);			
					}				
				}
			}
		break;
		case VP_RK_POWER_LOSS_RECOVERY:
		{

			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(en==1)
			{
		      power_loss_resume=1;		  
			  power_loss_state =1;			
			  //dry heat
			  thermalManager.set_dry_time();
			  uint16_t Tmp_val = drybox_targe_temp+Temperature_Center_Offset;
			  thermalManager.setTargetHotend_DRYBOX(Tmp_val);
			  thermalManager.degTargetHotend_drybox(TEMP_DRYBOX_CENTER_PIN);
			  ui.set_select_drybox_state(1);
			  if(ui.language == UI_LANGUAGE_CHINESE)			GotoScreen(DGUSLCD_SCREEN_CN_WAITPOWERLOSS);
			  else												GotoScreen(DGUSLCD_SCREEN_EN_WAITPOWERLOSS);
	  		   recovery.resume();
			}
			else if(en == 2)
			{
     			recovery.cancel();
				if(ui.language == UI_LANGUAGE_CHINESE)				GotoScreen(DGUSLCD_SCREEN_CN_MAIN);
				else												GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
			}
		}
		break;		
		case VP_RK_PowerLow:
		{
			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(en==1)
			{
				ui.auto_turn_off=false;
			}	
			else
			{
				ui.auto_turn_off=true;;
			}
			save_par=true;
		}
		break;

		case VP_RK_disableaxis:
		{
			if(ui.language == UI_LANGUAGE_CHINESE)			  GotoScreen(DGUSLCD_SCREEN_CN_SHUTMOTO);
			else											  GotoScreen(DGUSLCD_SCREEN_EN_SHUTMOTO);
		
			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(en==1)
			{
				ExtUI::injectCommands_P(PSTR("M18"));
				//queue.enqueue_one_P(PSTR("M500"));
			}
			if(ui.language == UI_LANGUAGE_CHINESE)			  GotoScreen(DGUSLCD_SCREEN_CN_UTILITIES);
			else											  GotoScreen(DGUSLCD_SCREEN_EN_UTILITIES);
			
		}
		break;
		case VP_RK_reset:
		{
			int16_t en = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(en==1)
			{
				queue.enqueue_one_P(PSTR("M502"));
				queue.enqueue_one_P(PSTR("M500"));
				queue.enqueue_one_P(PSTR("M18"));
				queue.enqueue_one_P(PSTR("M1003"));
			}
		}
		break;
		case VP_RK_dec_filament_len:
			if(Filament_Len>0)
			Filament_Len--;
		break;
		case VP_RK_add_filament_len:
			if(Filament_Len<500)
			Filament_Len++;
		break;
		case VP_RK_language:
		{
			int16_t cn = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(cn==1)//chinese
			{
				ui.language=UI_LANGUAGE_CHINESE;
				GotoScreen(DGUSLCD_SCREEN_CN_UTILITIES);
				ExtUI::injectCommands_P(PSTR("M500"));
			    ForceCompleteUpdate();				
			}
			else if(cn==2)//english
			{
				ui.language=UI_LANGUAGE_ENGLISH;
				GotoScreen(DGUSLCD_SCREEN_EN_UTILITIES);
				ExtUI::injectCommands_P(PSTR("M500"));
			    ForceCompleteUpdate();		
			}
			else //into language ui
			{
				if(ui.language==UI_LANGUAGE_CHINESE)				GotoScreen(DGUSLCD_SCREEN_LANGUAGE_SELECT);
				else												GotoScreen(DGUSLCD_SCREEN_LANGUAGE_SELECT_EN);
			}
		}
		break;
		case VP_RK_01_step:
			motor_stper=10;//0.1*100;
		break;
		case VP_RK_1_step:
			motor_stper=1*100;
		break;
		case VP_RK_10_step:
			motor_stper=10*100;
		break;
		case VP_RK_filament_pla:
		thermalManager.setTargetHotend(PREHEAT_1_TEMP_HOTEND, 0);
		filament_display_data = thermalManager.degTargetHotend(0);;
		filament_temp_u 	  =thermalManager.degTargetHotend(0);

		break;
		case VP_RK_filament_abs:
			thermalManager.setTargetHotend(PREHEAT_2_TEMP_HOTEND, 0);
			filament_display_data = thermalManager.degTargetHotend(0);;
			filament_temp_u 	  =thermalManager.degTargetHotend(0);
			
		break;
		case VP_RK_add_rate:
			if(feedrate_percentage<250)
			feedrate_percentage++;
		break;
		case VP_Add_Targe_Temp:
			if(drybox_targe_temp<DRYBOX_MAXTEMP)
			{
				drybox_targe_temp++;
			}
		break;
		case VP_Dec_Targe_Temp:
			if(drybox_targe_temp>DRYBOX_MINTEMP)
			{
				drybox_targe_temp--;
			}
		break;
		case VP_Add_Dry_Time:
			if(thermalManager.drybox_timer< drybox_MaxTime){
			thermalManager.drybox_timer+=1800;//30;
			thermalManager.dry_time =thermalManager.drybox_timer;			
			}
		break;
		case VP_Dec_Dry_Time:
			if(thermalManager.drybox_timer>0){	
				thermalManager.drybox_timer-=1800;//30;
				thermalManager.dry_time =thermalManager.drybox_timer;
			}
			 
		break;		
		case VP_DRYBOX_CANCEL:	
			thermalManager.stop_dry_work();		
			ui.set_select_drybox_state(0);
			Fresh_Ui_Icon_Fun();


			
		break;
		case VP_DRYBOX_apply:
			ui.set_select_drybox_state(1);
			Fresh_Ui_Icon_Fun();
			Tmp_val = drybox_targe_temp+Temperature_Center_Offset;
			thermalManager.setTargetHotend_DRYBOX(Tmp_val);
//        	thermalManager.setTargetHotend_DRYBOX(drybox_targe_temp);
        	thermalManager.degTargetHotend_drybox(TEMP_DRYBOX_CENTER_PIN);
			thermalManager.drybox_timer_starttime=millis();
			thermalManager.drybox_ing=true;
			if((thermalManager.drybox_timer==0)||(thermalManager.dry_time==0))
			{
				thermalManager.drybox_ing=false;				
				thermalManager.setTargetHotend_DRYBOX(0);
				thermalManager.degTargetHotend_drybox(TEMP_DRYBOX_CENTER_PIN);
			}
			if(current_screen == DGUSLCD_SCREEN_CN_DTYBOXOTHER||current_screen == DGUSLCD_SCREEN_EN_DTYBOXOTHER)
				thermalManager.set_dry_time();
			
		break;
		case VP_RK_dec_rate:
			if(feedrate_percentage>0)
			feedrate_percentage--;
		break;
		case VP_SD_FilePrint_AutoLeve:
		{
			int16_t enable = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(enable==0)
			{
				ui.auto_level=1;
			}
			else if (enable==1)
			{
				ui.auto_level=0;
			}
			ForceCompleteUpdate();		
		}
		break;
		case VP_SD_FilePrint_FilamentRunout:
		{
			int16_t enable = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(enable==0)
			{
				temp_runout_enable|= (0x01<<FilamentRunout_Bit);
			}
			else if (enable==1)
			{
				temp_runout_enable &= ~(0x01<<FilamentRunout_Bit);
			}
			if((temp_runout_enable&0x03) == 0)
			{
				detachInterrupt(0);
			}
			save_par=true;
			ForceCompleteUpdate();	
		}
		break;
		case VP_SD_FilePrint_Filament_Jams:
		{
			int16_t enable = (int16_t)swap16(*(uint16_t*)val_ptr);
			if(enable==0)
			{
				temp_runout_enable|= (0x01<<FilamentJams_Bit);
			}
			else if (enable==1)
			{
				temp_runout_enable &= ~(0x01<<FilamentJams_Bit);
			}
			if((temp_runout_enable&0x03) == 0)
			{
				detachInterrupt(0);
			}
			save_par=true;
			ForceCompleteUpdate();			
		}
		break;
		case VP_M108:
			ExtUI::injectCommands_P(PSTR("M108"));
			//PopToOldScreen();
		break;
		default:
		break;
	}	
}

uint16_t  DGUSScreenHandler::Get_drybox_targe_temp(void)
{
	return drybox_targe_temp;
}




void DGUSScreenHandler::onStartMove()
{
	if(ExtUI::isPrintingFromMedia())	return;
    if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_WAIT_MOVE);
	else		  								  GotoScreen(DGUSLCD_SCREEN_CN_WAIT_MOVE);//homeing
	
}
void DGUSScreenHandler::onEndMove()
{
	if(ExtUI::isPrintingFromMedia())	return;
	PopToOldScreen();
}


void DGUSScreenHandler::onHomingStart()
{
    if(ui.language==UI_LANGUAGE_ENGLISH)		  GotoScreen(DGUSLCD_SCREEN_EN_LEVELING);
	else		  								  GotoScreen(DGUSLCD_SCREEN_CN_LEVELING);//homeing
	
}

void DGUSScreenHandler::onHomingComplete(bool t)
{
	planner.synchronize();
	if(t){
	}
	//do{ MYSERIAL1.print(__FILE__); MYSERIAL1.println(__LINE__); }while(0);
	if(ExtUI::isPrintingFromMedia())
	{
		if(planner.leveling_active)
		{
			ExtUI::injectCommands("G29");
		}
	}
	PopToOldScreen();
}
void DGUSScreenHandler::resume_printUI()
{
  if((GCodeQueue::is_online_print  || card.isPrinting() || card.isPaused())&& !card.isAbort())
  {
  	if(ui.language==UI_LANGUAGE_CHINESE)
  	{
  		if(current_screen!=DGUSLCD_SCREEN_CN_STATUS && current_screen!=DGUSLCD_SCREEN_CN_STATUS_PAUSE && current_screen!=DGUSLCD_SCREEN_CN_CHANGE_FILAMENT 
			&& current_screen!=DGUSLCD_SCREEN_CN_PRINTINGFINISHED && current_screen!=DGUSLCD_SCREEN_CN_LEVELING&& current_screen!=DGUSLCD_SCREEN_CN_PAUSE_SELECT
			&& current_screen!=DGUSLCD_SCREEN_CN_CANCEL_SELECT&& current_screen!=DGUSLCD_SCREEN_CN_PRINTINGCONTINUE&& current_screen!=DGUSLCD_SCREEN_CN_WAITHEATING
			&& current_screen!=DGUSLCD_SCREEN_CN_WAITOPERATE&&current_screen!=DGUSLCD_SCREEN_CN_WAITPOWERLOSS
			&&current_screen!=DGUSLCD_SCREEN_CN_ONLINEPRINT &&current_screen!=DGUSLCD_SCREEN_KILL
			&&current_screen!=DGUSLCD_SCREEN_CN_FILAMENT_CANCEL &&current_screen!=DGUSLCD_SCREEN_CN_DRYBOX
			&&current_screen!=DGUSLCD_SCREEN_CN_DTYBOXOTHER &&current_screen!=DGUSLCD_SCREEN_CN_DTYBOX_OTHER
			&&current_screen!=DGUSLCD_SCREEN_N0_CN_DTYBOX&&current_screen!=DGUSLCD_SCREEN_CN_NO_FILAMENT
			&&current_screen!=DGUSLCD_SCREEN_CN_DTYBOX_TWO_OTHER
		)
		{		
			if(card.isPrinting()){
				//do{ MYSERIAL1.print("goto_DGUSLCD_SCREEN_CN_STATUS11111");	}while(0);
				
				GotoScreen(DGUSLCD_SCREEN_CN_STATUS);
				thermalManager.set_dry_time();
			}
			else if((GCodeQueue::is_online_print)){
				if(GCodeQueue::pause_online_print()==0)				
				GotoScreen(DGUSLCD_SCREEN_CN_ONLINEPRINT);
			
			}
			else{
				GotoScreen(DGUSLCD_SCREEN_CN_STATUS_PAUSE);
			}
			
  		}
  	}
	else
	{
  		if(current_screen!=DGUSLCD_SCREEN_EN_STATUS && current_screen!=DGUSLCD_SCREEN_EN_STATUS_PAUSE && current_screen!=DGUSLCD_SCREEN_EN_CHANGE_FILAMENT 
			&& current_screen!=DGUSLCD_SCREEN_EN_PRINTINGFINISHED && current_screen!=DGUSLCD_SCREEN_EN_LEVELING&& current_screen!=DGUSLCD_SCREEN_EN_PAUSE_SELECT
			&& current_screen!=DGUSLCD_SCREEN_EN_CANCEL_SELECT&& current_screen!=DGUSLCD_SCREEN_EN_PRINTINGCONTINUE&& current_screen!=DGUSLCD_SCREEN_EN_WAITHEATING
			&& current_screen!=DGUSLCD_SCREEN_EN_WAITOPERATE&&current_screen!=DGUSLCD_SCREEN_CN_WAITPOWERLOSS
			&&current_screen!=DGUSLCD_SCREEN_EN_ONLINEPRINT &&current_screen!=DGUSLCD_SCREEN_KILL
			&&current_screen!=DGUSLCD_SCREEN_EN_FILAMENT_CANCEL &&current_screen!=DGUSLCD_SCREEN_EN_DRYBOX  			
		    &&current_screen!=DGUSLCD_SCREEN_EN_DTYBOXOTHER&&current_screen!=DGUSLCD_SCREEN_EN_DTYBOX_OTHER		    
	    	&&current_screen!=DGUSLCD_SCREEN_N0_EN_DTYBOX&&current_screen!=DGUSLCD_SCREEN_EN_NO_FILAMENT	    	
			&&current_screen!=DGUSLCD_SCREEN_EN_DTYBOX_TWO_OTHER
		)
		{	
			if(card.isPrinting()){
				GotoScreen(DGUSLCD_SCREEN_EN_STATUS);
				thermalManager.set_dry_time();
			}
			else if((GCodeQueue::is_online_print)){
				if(GCodeQueue::pause_online_print()==0)				
				GotoScreen(DGUSLCD_SCREEN_EN_ONLINEPRINT);
			
			}
			else{
				GotoScreen(DGUSLCD_SCREEN_EN_STATUS_PAUSE);
			}			
  		}
  	}
  }	
}
void DGUSScreenHandler::Periodic_task()
{
	if(save_par)
	{
		save_par=false;
		settings.save();
	}
}

bool DGUSScreenHandler::loop() {
  static millis_t cur_time=0,last_time=0;
  dgusdisplay.loop();//���մ�����Ϣ

  const millis_t ms = millis();
  static millis_t next_event_ms = 0;
  static int millis_counter=0;

  if (!IsScreenComplete() || ELAPSED(ms, next_event_ms)){
    next_event_ms = ms + DGUS_UPDATE_INTERVAL_MS;
	resume_printUI();
	if(millis_counter++>120)
	{
		Periodic_task();
		millis_counter=0;
	}
    UpdateScreenVPData();
  }

  #if ENABLED(SHOW_BOOTSCREEN)
    static bool booted = false;

    if (!booted && TERN0(POWER_LOSS_RECOVERY, recovery.valid()))
      booted = true;

    if (!booted && ELAPSED(ms, TERN(USE_MKS_GREEN_UI, 1000, BOOTSCREEN_TIMEOUT)))
      booted = true;
  #endif
  return IsScreenComplete();
}

bool DGUSScreenHandler:: GetFilamentState_Check()
{
	if(ExtUI::getFilamentRunoutState()){
		if(ExtUI::getFilamentRunout_enabled()&0x03){		  
		  return 1;
		}	
		
		return 1;
	}
	return 0;
}

void DGUSScreenHandler:: InitLevelData()
{
		float (*p)[GRID_MAX_POINTS_Y]= (ExtUI::getMeshArray());
		//1 	
		dgusdisplay.WriteVariable(VP_Num_Point_4,(uint16_t)(  (*(*(p+0)+0)) * cpow(10, 3)) );		
		//2
		dgusdisplay.WriteVariable(VP_Num_Point_5,(uint16_t)(  (*(*(p+0)+1)) * cpow(10, 3)) );
		//3
		dgusdisplay.WriteVariable(VP_Num_Point_12,(uint16_t)(  (*(*(p+0)+2)) * cpow(10, 3)) );
		//4
		dgusdisplay.WriteVariable(VP_Num_Point_13,(uint16_t)(  (*(*(p+0)+3)) * cpow(10, 3)) );
		//5
		dgusdisplay.WriteVariable(VP_Num_Point_3,(uint16_t)(  (*(*(p+1)+0)) * cpow(10, 3)) );
		//6
		dgusdisplay.WriteVariable(VP_Num_Point_6,(uint16_t)(  (*(*(p+1)+1)) * cpow(10, 3)) );
		//7
		dgusdisplay.WriteVariable(VP_Num_Point_11,(uint16_t)(  (*(*(p+1)+2)) * cpow(10, 3)) );
		//8
		dgusdisplay.WriteVariable(VP_Num_Point_14,(uint16_t)(  (*(*(p+1)+3)) * cpow(10, 3)) );
		//9
		dgusdisplay.WriteVariable(VP_Num_Point_2,(uint16_t)(  (*(*(p+2)+0)) * cpow(10, 3)) );
		//10
		dgusdisplay.WriteVariable(VP_Num_Point_7,(uint16_t)(  (*(*(p+2)+1)) * cpow(10, 3)) );
		//11
		dgusdisplay.WriteVariable(VP_Num_Point_10,(uint16_t)(  (*(*(p+2)+2)) * cpow(10, 3)) );
		//12
		dgusdisplay.WriteVariable(VP_Num_Point_15,(uint16_t)(  (*(*(p+2)+3)) * cpow(10, 3)) );
		//13
		dgusdisplay.WriteVariable(VP_Num_Point_1,(uint16_t)(  (*(*(p+3)+0)) * cpow(10, 3)) );
		//14
		dgusdisplay.WriteVariable(VP_Num_Point_8,(uint16_t)(  (*(*(p+3)+1)) * cpow(10, 3)) );
		//15
		dgusdisplay.WriteVariable(VP_Num_Point_9,(uint16_t)(  (*(*(p+3)+2)) * cpow(10, 3)) );
		//16
		dgusdisplay.WriteVariable(VP_Num_Point_16,(uint16_t)(  (*(*(p+3)+3)) * cpow(10, 3)) );			

}

void DGUSScreenHandler:: Temp_Calibration_Timer(void)
{
	millis_t get_cur_time=0,get_last_time=0;
	celsius_t newvalue =0;
	if(card.isPrinting())
	{
	
		 get_cur_time =millis();
		 if(get_cur_time-get_last_time<Temp_Calibration_Clock)//120s
		 {
			 return;	
		 }
		 else 
		 {
		    if(thermalManager.keyboard_nozzle_temp>0)
		    {
				newvalue =thermalManager.keyboard_nozzle_temp;
		        NOMORE(newvalue, HEATER_0_MAXTEMP);
				thermalManager.setTargetHotend(newvalue, 0);
		    }
		    if(thermalManager.keyboard_bed_temp>0)
	    	{
				newvalue =thermalManager.keyboard_bed_temp;
		        NOMORE(newvalue, BED_MAXTEMP);				 
		        thermalManager.setTargetBed(newvalue);
	    	}
		    if(key_Input_feedrate_percentage>0)
	    	{
				newvalue =key_Input_feedrate_percentage;
		        NOMORE(newvalue, 250);		 
				feedrate_percentage = newvalue;
	    	}
				 
			 get_last_time=get_cur_time;
		
		 }	
	}

}


#endif // DGUS_LCD_UI_SUNLU
