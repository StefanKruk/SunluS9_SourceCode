#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/dgus/DGUSScreenHandler.cpp"
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

#include "../../../inc/MarlinConfigPre.h"

#if HAS_DGUS_LCD

#include "DGUSScreenHandler.h"

#include "../../../MarlinCore.h"
#include "../../../gcode/queue.h"
#include "../../../libs/duration_t.h"
#include "../../../module/settings.h"
#include "../../../module/temperature.h"
#include "../../../module/motion.h"
#include "../../../module/planner.h"
#include "../../../module/printcounter.h"
#include "../../../sd/cardreader.h"

#if ENABLED(POWER_LOSS_RECOVERY)
  #include "../../../feature/powerloss.h"
#endif

DGUSScreenHandler ScreenHandler;
DGUSLCD_Screens DGUSScreenHandler::current_screen;
DGUSLCD_Screens DGUSScreenHandler::past_screens[NUM_PAST_SCREENS];
uint8_t DGUSScreenHandler::update_ptr;
uint8_t DGUSScreenHandler::measure_index;
uint16_t DGUSScreenHandler::ConfirmVP;
uint16_t DGUSScreenHandler::skipVP;
uint16_t DGUSScreenHandler::motor_stper;
uint16_t DGUSScreenHandler::filament_temp_u=0;//PREHEAT_1_TEMP_HOTEND;
uint16_t DGUSScreenHandler::filament_display_data=0;//PREHEAT_1_TEMP_HOTEND;
uint16_t DGUSScreenHandler::drybox_targe_temp=DRYBOX_DEFAULT_TEMP;
uint16_t DGUSScreenHandler::Filament_Len=10;
uint16_t DGUSScreenHandler::VP_Value=0;
int16_t DGUSScreenHandler::z_compensate_adust=0;


bool DGUSScreenHandler::has_sdcar;
bool DGUSScreenHandler::No_Refresh=false;
bool DGUSScreenHandler::save_par=false;
bool DGUSScreenHandler::smile_adjustZ=false;
bool DGUSScreenHandler::ScreenComplete;
uint8_t DGUSScreenHandler::temp_runout_enable;
uint8_t DGUSScreenHandler::System_Config_0X80_D1[4]={0};
volatile uint8_t DGUSScreenHandler::power_loss_resume=0;
volatile uint8_t DGUSScreenHandler::power_loss_cnt=0;
volatile uint8_t DGUSScreenHandler::power_loss_state=0;
volatile uint8_t DGUSScreenHandler::Filament_Runout_AutoRecovery_State=0;
volatile uint8_t DGUSScreenHandler::Filament_Runout_AutoRecovery_Cnt=0;
volatile uint8_t DGUSScreenHandler::back_Fliament_State=0;
volatile uint8_t DGUSScreenHandler::Filament_Runout_screen_state=0;
volatile uint8_t DGUSScreenHandler::Filament_Runout_Check_Flag=0;



float DGUSScreenHandler::back_e=0;
float DGUSScreenHandler::temp_current_position_x=0,
	  DGUSScreenHandler::temp_current_position_y=0,
	  DGUSScreenHandler::temp_current_position_z=0,
	  DGUSScreenHandler::temp_current_position_e=0;
uint16_t Screen_Fresh_Error_Cnt =0;
uint32_t watchdog_cnt =0;
bool Screen_Fresh_Error_Flag =false;
bool Start_watchdog =true ;
void (*DGUSScreenHandler::confirm_action_cb)() = nullptr;


#if ENABLED(SDSUPPORT)
  int16_t DGUSScreenHandler::top_file = 0,
          DGUSScreenHandler::gcode_file_offset = 0,
          DGUSScreenHandler::file_to_print = 0;
  
static ExtUI::FileList filelist;
#endif

#if ENABLED(DGUS_FILAMENT_LOADUNLOAD)
  filament_data_t filament_data;
#endif

void DGUSScreenHandler::sendinfoscreen(const char *line1, const char *line2, const char *line3, const char *line4, bool l1inflash, bool l2inflash, bool l3inflash, bool l4inflash) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_MSGSTR1, &ramcopy)) {
    ramcopy.memadr = (void*) line1;
    l1inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR2, &ramcopy)) {
    ramcopy.memadr = (void*) line2;
    l2inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR3, &ramcopy)) {
    ramcopy.memadr = (void*) line3;
    l3inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
  }
  if (populate_VPVar(VP_MSGSTR4, &ramcopy)) {
    ramcopy.memadr = (void*) line4;
    l4inflash ? DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy) : DGUSScreenHandler::DGUSLCD_SendStringToDisplay(ramcopy);
  }
}
void DGUSScreenHandler::Address_Beyond_Fun(uint32_t TmpGetAddr,uint32_t dataN0)
{
	if(TmpGetAddr>=0x1f000)
		sendkillscreen(TmpGetAddr,dataN0);
}
void DGUSScreenHandler::Display_Para_screen(uint32_t dataN0,uint32_t dataN1)
{
	char commandStr[30];  
	DGUS_VP_Variable tmpval;
	sprintf(commandStr,"Two_address= %ld_%ld",dataN0,dataN1);	

	char tmpfilename[VP_SD_FileName_LEN + 1] = "";
	snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s%c"), commandStr,0); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
	tmpval.VP = VP_MSGSTR3;
	tmpval.size = VP_SD_FileName_LEN;
	tmpval.memadr = (void*)tmpfilename;
	DGUSLCD_SendStringToDisplay(tmpval);	  
  
	kill(PSTR("Screen Refresh Failed"));			

}

void DGUSScreenHandler::sendkillscreen(uint32_t tmpaddress,uint32_t dataN0)
{
	char commandStr[30];  
	DGUS_VP_Variable tmpval;
	sprintf(commandStr,"address= %ld_%ld",tmpaddress,dataN0);	

	char tmpfilename[VP_SD_FileName_LEN + 1] = "";
	snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s%c"), commandStr,0); // snprintf_P(tmpfilename, VP_SD_FileName_LEN, PSTR("%s"), filelist.filename());
	tmpval.VP = VP_MSGSTR3;
	tmpval.size = VP_SD_FileName_LEN;
	tmpval.memadr = (void*)tmpfilename;
	DGUSLCD_SendStringToDisplay(tmpval);	  
  
	kill(PSTR("Screen Refresh Failed"));			

}


void DGUSScreenHandler::sendsoftwareversionscreen(const char *line1) 
{
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_device_info, &ramcopy)) {
    ramcopy.memadr = (void*) line1;
     DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy);
  }  
} 

void DGUSScreenHandler::sendprintinfoscreen(const char *line1) 
{
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_printfinfo_info, &ramcopy)) {
    ramcopy.memadr = (void*) line1;
     DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(ramcopy);
  }  
}




void DGUSScreenHandler::HandleUserConfirmationPopUp(uint16_t VP, const char *line1, const char *line2, const char *line3, const char *line4, bool l1, bool l2, bool l3, bool l4) {
  if (current_screen == DGUSLCD_SCREEN_CONFIRM || current_screen == DGUSLCD_SCREEN_CONFIRM_EN) // Already showing a pop up, so we need to cancel that first.
    PopToOldScreen();

  ConfirmVP = VP;
  
  sendinfoscreen(line1, line2, line3, line4, l1, l2, l3, l4);
  if(ui.language==UI_LANGUAGE_CHINESE)
  {
  	GotoScreen(DGUSLCD_SCREEN_CONFIRM);
  }
  else
  {
  	GotoScreen(DGUSLCD_SCREEN_CONFIRM_EN);
  }
 #if 1
  if(ExtUI::getFilamentRunout_enabled() & (0x01<<FilamentJams_Bit))
  {
	dgusdisplay.WriteVariable(VP_SD_FilePrint_Filament_Jams, 0);
  }
  else
  {
	dgusdisplay.WriteVariable(VP_SD_FilePrint_Filament_Jams, 1);
  }
  if(ExtUI::getFilamentRunout_enabled() & (0x01<<FilamentRunout_Bit))
  {
	dgusdisplay.WriteVariable(VP_SD_FilePrint_FilamentRunout, 0);
  }
  else
  {
	dgusdisplay.WriteVariable(VP_SD_FilePrint_FilamentRunout, 1);
  }
#endif
  if(ui.auto_level==1)
  {
    dgusdisplay.WriteVariable(VP_SD_FilePrint_AutoLeve, 0);
  }
  else
  {
    dgusdisplay.WriteVariable(VP_SD_FilePrint_AutoLeve, 1);
  }
  if(ui.auto_turn_off)
  {
  	dgusdisplay.WriteVariable(VP_RK_PowerLow, 0);
  }
  else
  {
  	dgusdisplay.WriteVariable(VP_RK_PowerLow, 1);
  }
  if(ui.select_fast_print)
  {
  	dgusdisplay.WriteVariable(VP_RK_Fastprint, (uint16_t)0);
  }
  else
  {
  	dgusdisplay.WriteVariable(VP_RK_Fastprint, (uint16_t)1);
  }  
  	
}

void DGUSScreenHandler::setstatusmessage(const char *msg) {
	//#ifndef DGUS_LCD_UI_SUNLU
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_M117, &ramcopy)) {
    ramcopy.memadr = (void*) msg;
    DGUSLCD_SendStringToDisplay(ramcopy);
  }
  //#endif
}

void DGUSScreenHandler::setstatusmessagePGM(PGM_P const msg) {
  DGUS_VP_Variable ramcopy;
  if (populate_VPVar(VP_M117, &ramcopy)) {
    ramcopy.memadr = (void*) msg;
    DGUSLCD_SendStringToDisplayPGM(ramcopy);
  }
}

// Send an 8 bit or 16 bit value to the display.
void DGUSScreenHandler::DGUSLCD_SendWordValueToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    //DEBUG_ECHOPAIR(" DGUS_LCD_SendWordValueToDisplay ", var.VP);
    //DEBUG_ECHOLNPAIR(" data ", *(uint16_t *)var.memadr);
    float f=*(float *)var.memadr;
    int16_t uf=*(int16_t *)var.memadr;
    if (var.size > 1)
      dgusdisplay.WriteVariable(var.VP, *(int16_t*)var.memadr);
    else
      dgusdisplay.WriteVariable(var.VP, *(int8_t*)var.memadr);
  }
}

// Send an uint8_t between 0 and 255 to the display, but scale to a percentage (0..100)
void DGUSScreenHandler::DGUSLCD_SendPercentageToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    //DEBUG_ECHOPAIR(" DGUS_LCD_SendWordValueToDisplay ", var.VP);
    //DEBUG_ECHOLNPAIR(" data ", *(uint16_t *)var.memadr);
    uint16_t tmp = *(uint8_t *) var.memadr + 1; // +1 -> avoid rounding issues for the display.
    tmp = map(tmp, 0, 255, 0, 100);
    dgusdisplay.WriteVariable(var.VP, tmp);
  }
}

// Send the current print progress to the display.
void DGUSScreenHandler::DGUSLCD_SendPrintProgressToDisplay(DGUS_VP_Variable &var) {
  //DEBUG_ECHOPAIR(" DGUSLCD_SendPrintProgressToDisplay ", var.VP);
  uint16_t tmp = ExtUI::getProgress_percent();
  //DEBUG_ECHOLNPAIR(" data ", tmp);
  dgusdisplay.WriteVariable(var.VP, tmp);
}

// Send the current print time to the display.
// It is using a hex display for that: It expects BSD coded data in the format xxyyzz
void DGUSScreenHandler::DGUSLCD_SendPrintTimeToDisplay(DGUS_VP_Variable &var) {
  duration_t elapsed = 0;
  if(var.VP==VP_PrintTime)	elapsed =   print_job_timer.duration();
  else if(var.VP==VP_Dry_Time)
  {
//  	elapsed =   drybox_timer-MS_TO_SEC(drybox_ing ? (millis()  - drybox_timer_starttime):0);
  if(thermalManager.drybox_ing)
	elapsed =  thermalManager.dry_time;// drybox_timer-MS_TO_SEC(drybox_ing ? (millis()  - drybox_timer_starttime):0);
	else
	elapsed =	thermalManager.drybox_timer-MS_TO_SEC(thermalManager.drybox_ing ? (millis()  - thermalManager.drybox_timer_starttime):0);
		
//  do{ MYSERIAL1.print("DGUSLCD_SendPrintTimeToDisplay_elapsed:"); MYSERIAL1.println(thermalManager.dry_time); }while(0);

		
  }
  char buf[32];
  elapsed.toString(buf);
  dgusdisplay.WriteVariable(var.VP, buf, var.size, true);
}

// Send an uint8_t between 0 and 100 to a variable scale to 0..255
void DGUSScreenHandler::DGUSLCD_PercentageToUint8(DGUS_VP_Variable &var, void *val_ptr) {
  if (var.memadr) {
    uint16_t value = swap16(*(uint16_t*)val_ptr);
    DEBUG_ECHOLNPAIR("FAN value get:", value);
    *(uint8_t*)var.memadr = map(constrain(value, 0, 100), 0, 100, 0, 255);
    DEBUG_ECHOLNPAIR("FAN value change:", *(uint8_t*)var.memadr);
  }
}

// Sends a (RAM located) string to the DGUS Display
// (Note: The DGUS Display does not clear after the \0, you have to
// overwrite the remainings with spaces.// var.size has the display buffer size!
void DGUSScreenHandler::DGUSLCD_SendStringToDisplay(DGUS_VP_Variable &var) {
  char *tmp = (char*) var.memadr;
  dgusdisplay.WriteVariable(var.VP, tmp, var.size, true);
}

// Sends a (flash located) string to the DGUS Display
// (Note: The DGUS Display does not clear after the \0, you have to
// overwrite the remainings with spaces.// var.size has the display buffer size!
void DGUSScreenHandler::DGUSLCD_SendStringToDisplayPGM(DGUS_VP_Variable &var) {
  char *tmp = (char*) var.memadr;
  dgusdisplay.WriteVariablePGM(var.VP, tmp, var.size, true);
}

#if HAS_PID_HEATING 
  void DGUSScreenHandler::DGUSLCD_SendTemperaturePID(DGUS_VP_Variable &var) {
  #ifndef DGUS_LCD_UI_SUNLU
    float value = *(float *)var.memadr;
    value /= 10;
    float valuesend = 0;
    switch (var.VP) {
      default: return;
      #if HOTENDS >= 1
        case VP_E0_PID_P: valuesend = value; break;
        case VP_E0_PID_I: valuesend = unscalePID_i(value); break;
        case VP_E0_PID_D: valuesend = unscalePID_d(value); break;
      #endif
      #if HOTENDS >= 2
        case VP_E1_PID_P: valuesend = value; break;
        case VP_E1_PID_I: valuesend = unscalePID_i(value); break;
        case VP_E1_PID_D: valuesend = unscalePID_d(value); break;
      #endif
      #if HAS_HEATED_BED
        case VP_BED_PID_P: valuesend = value; break;
        case VP_BED_PID_I: valuesend = unscalePID_i(value); break;
        case VP_BED_PID_D: valuesend = unscalePID_d(value); break;
      #endif
    }

    valuesend *= cpow(10, 1);
    union { int16_t i; char lb[2]; } endian;

    char tmp[2];
    endian.i = valuesend;
    tmp[0] = endian.lb[1];
    tmp[1] = endian.lb[0];
    dgusdisplay.WriteVariable(var.VP, tmp, 2);
	#endif
  }
#endif

#if ENABLED(PRINTCOUNTER)

  // Send the accumulate print time to the display.
  // It is using a hex display for that: It expects BSD coded data in the format xxyyzz
  void DGUSScreenHandler::DGUSLCD_SendPrintAccTimeToDisplay(DGUS_VP_Variable &var) {
    printStatistics state = print_job_timer.getStats();
    char buf[22];
    duration_t elapsed = state.printTime;
    elapsed.toString(buf);
    dgusdisplay.WriteVariable(VP_PrintAccTime, buf, var.size, true);
  }

  void DGUSScreenHandler::DGUSLCD_SendPrintsTotalToDisplay(DGUS_VP_Variable &var) {
    printStatistics state = print_job_timer.getStats();
    char buf[10];
    sprintf_P(buf, PSTR("%u"), state.totalPrints);
    dgusdisplay.WriteVariable(VP_PrintsTotal, buf, var.size, true);
  }

#endif

// Send fan status value to the display.
#if HAS_FAN

  void DGUSScreenHandler::DGUSLCD_SendFanStatusToDisplay(DGUS_VP_Variable &var) {
    if (var.memadr) {
      DEBUG_ECHOPAIR(" DGUSLCD_SendFanStatusToDisplay ", var.VP);
      DEBUG_ECHOLNPAIR(" data ", *(uint8_t *)var.memadr);
      uint16_t data_to_send = 0;
      if (*(uint8_t *) var.memadr) data_to_send = 1;
      dgusdisplay.WriteVariable(var.VP, data_to_send);
    }
  }

#endif

// Send heater status value to the display.
void DGUSScreenHandler::DGUSLCD_SendHeaterStatusToDisplay(DGUS_VP_Variable &var) {
  if (var.memadr) {
    DEBUG_ECHOPAIR(" DGUSLCD_SendHeaterStatusToDisplay ", var.VP);
    DEBUG_ECHOLNPAIR(" data ", *(int16_t *)var.memadr);
    uint16_t data_to_send = 0;
    if (*(int16_t *) var.memadr) data_to_send = 1;
    dgusdisplay.WriteVariable(var.VP, data_to_send);
  }
}

#if ENABLED(DGUS_UI_WAITING)

  void DGUSScreenHandler::DGUSLCD_SendWaitingStatusToDisplay(DGUS_VP_Variable &var) {
    // In FYSETC UI design there are 10 statuses to loop
    static uint16_t period = 0;
    static uint16_t index = 0;
    //DEBUG_ECHOPAIR(" DGUSLCD_SendWaitingStatusToDisplay ", var.VP);
    //DEBUG_ECHOLNPAIR(" data ", swap16(index));
    if (period++ > DGUS_UI_WAITING_STATUS_PERIOD) {
      dgusdisplay.WriteVariable(var.VP, index);
      //DEBUG_ECHOLNPAIR(" data ", swap16(index));
      if (++index >= DGUS_UI_WAITING_STATUS) index = 0;
      period = 0;
    }
  }

#endif

#if ENABLED(SDSUPPORT)

  void DGUSScreenHandler::ScreenChangeHookIfSD(DGUS_VP_Variable &var, void *val_ptr) {
    // default action executed when there is a SD card, but not printing
    if (ExtUI::isMediaInserted() && !ExtUI::isPrintingFromMedia()) {
      ScreenChangeHook(var, val_ptr);
      dgusdisplay.RequestScreen(current_screen);
      return;
    }

    // if we are printing, we jump to two screens after the requested one.
    // This should host e.g a print pause / print abort / print resume dialog.
    // This concept allows to recycle this hook for other file
    if (ExtUI::isPrintingFromMedia() && !card.flag.abort_sd_printing) {
      GotoScreen(DGUSLCD_SCREEN_SDPRINTMANIPULATION);
      return;
    }

    // Don't let the user in the dark why there is no reaction.
    if (!ExtUI::isMediaInserted()) {
      setstatusmessagePGM(GET_TEXT(MSG_NO_MEDIA));
      return;
    }
    if (card.flag.abort_sd_printing) {
      setstatusmessagePGM(GET_TEXT(MSG_MEDIA_ABORTING));
      return;
    }
  }

  void DGUSScreenHandler::DGUSLCD_SD_ScrollFilelist(DGUS_VP_Variable& var, void *val_ptr) {
    auto old_top = top_file;
    int16_t scroll = (int16_t)swap16(*(uint16_t*)val_ptr);
	if(scroll==0)	scroll=-1;
	No_Refresh=false;
	gcode_file_offset=0;
    if (scroll) {
      top_file += scroll;
      DEBUG_ECHOPAIR("new topfile calculated:", top_file);
      if (top_file < 0) {
        top_file = 0;
        DEBUG_ECHOLNPGM("Top of filelist reached");
      }
      else {
        int16_t max_top = filelist.count() -  DGUS_SD_FILESPERSCREEN;
        NOLESS(max_top, 0);
        NOMORE(top_file, max_top);
      }
      DEBUG_ECHOPAIR("new topfile adjusted:", top_file);
    }
    else if (!filelist.isAtRootDir()) {
      IF_DISABLED(DGUS_LCD_UI_MKS, filelist.upDir());
      top_file = 0;
      ForceCompleteUpdate();
    }
    if (old_top != top_file) ForceCompleteUpdate();
  }

  void DGUSScreenHandler::DGUSLCD_SD_ReallyAbort(DGUS_VP_Variable &var, void *val_ptr) {
  	
	int16_t cancel = (int16_t)swap16(*(uint16_t*)val_ptr);
	if(cancel==1){
	    ExtUI::stopPrint();
		if(ui.language==UI_LANGUAGE_CHINESE)    GotoScreen(DGUSLCD_SCREEN_CN_MAIN);
		else if(ui.language==UI_LANGUAGE_ENGLISH)    GotoScreen(DGUSLCD_SCREEN_EN_MAIN);
	}
  }

  void DGUSScreenHandler::DGUSLCD_SD_PrintTune(DGUS_VP_Variable &var, void *val_ptr) {
    if (!ExtUI::isPrintingFromMedia()) return; // avoid race condition when user stays in this menu and printer finishes.
    GotoScreen(DGUSLCD_SCREEN_SDPRINTTUNE);
  }

  void DGUSScreenHandler::SDCardError() {
    DGUSScreenHandler::SDCardRemoved();
    sendinfoscreen(PSTR("NOTICE"), nullptr, PSTR("SD card error"), nullptr, true, true, true, true);
    SetupConfirmAction(nullptr);
    //GotoScreen(DGUSLCD_SCREEN_POPUP);
  }
#endif // SDSUPPORT

void DGUSScreenHandler::ScreenConfirmedOK(DGUS_VP_Variable &var, void *val_ptr) {
  DGUS_VP_Variable ramcopy;
  if (!populate_VPVar(ConfirmVP, &ramcopy)) return;
  if (ramcopy.set_by_display_handler) ramcopy.set_by_display_handler(ramcopy, val_ptr);
}
uint16_t Screen_Address_Error(struct VPMapping *tmpmap) {
	uint32_t  Current_Addr1 =0;
	uint32_t  Current_Addr2 =0;
	Current_Addr1 = &(tmpmap->VPList);
	Current_Addr2 = &(tmpmap->screen);
	//current_addr1 =0x1f000;//test
	if((Current_Addr1>=0x1f000)||(Current_Addr2>=0x1f000))
	{
	  Screen_Fresh_Error_Cnt++;
	}
	else
	  Screen_Fresh_Error_Cnt =0;

	if(Screen_Fresh_Error_Cnt>=100)
	{
#ifdef  Test_Screen_Fresh
	Screen_Fresh_Error_Cnt =0;

	if(ui.language==UI_LANGUAGE_CHINESE)
	  tmpmap->screen =DGUSLCD_SCREEN_CN_STATUS;
	else
	  tmpmap->screen =DGUSLCD_SCREEN_EN_STATUS;
	  tmpmap->VPList =VPList_Status;	

#else
	 Screen_Fresh_Error_Cnt =0;
	 ExtUI::pausePrint();
	 ScreenHandler.Display_Para_screen(Current_Addr1,Current_Addr2);
#endif
	}
	
}



const uint16_t* DGUSLCD_FindScreenVPMapList(uint8_t screen) {
  const uint16_t *ret;
  struct VPMapping *map = VPMap;
  //map =0x1f000;
  if(!Screen_Fresh_Error_Flag)
	{
		Screen_Fresh_Error_Flag =true;
		Screen_Address_Error(map);
	}
  ScreenHandler.Address_Beyond_Fun(&(map->VPList),7);
  //ScreenHandler.Address_Beyond_Fun(0x1f000,65535);
  while ((ret = (uint16_t*) pgm_read_ptr(&(map->VPList)))) {	
	  Screen_Address_Error(map);
	  ScreenHandler.Address_Beyond_Fun(&(map->screen),8);
    if (pgm_read_byte(&(map->screen)) == screen) return ret;
    map++;
  }
  return nullptr;
}

const DGUS_VP_Variable* DGUSLCD_FindVPVar(const uint16_t vp) {
  const DGUS_VP_Variable *ret = ListOfVP;
  do {
  	ScreenHandler.Address_Beyond_Fun(&(ret->VP),9);
    const uint16_t vpcheck = pgm_read_word(&(ret->VP));
    if (vpcheck == 0) break;
    if (vpcheck == vp) return ret;
    ++ret;
  } while (1);

  DEBUG_ECHOLNPAIR("FindVPVar NOT FOUND ", vp);
  return nullptr;
}

void DGUSScreenHandler::ScreenChangeHookIfIdle(DGUS_VP_Variable &var, void *val_ptr) {
  if (!ExtUI::isPrinting()) {
    ScreenChangeHook(var, val_ptr);
    dgusdisplay.RequestScreen(current_screen);
  }
}

void DGUSScreenHandler::HandleAllHeatersOff(DGUS_VP_Variable &var, void *val_ptr) {
  thermalManager.disable_all_heaters();
  ForceCompleteUpdate(); // hint to send all data.
}

void DGUSScreenHandler::HandlekeyboardChanged(DGUS_VP_Variable &var, void *val_ptr) {
	celsius_t newvalue = swap16(*(uint16_t*)val_ptr);
	celsius_t acceptedvalue;
	uint8_t   turn_falg=0;

	switch (var.VP) {

	
		case Key_up_temp_head:
		case Keyboard_cooldown_head_input:
		case Keyboard_Filament_head_input:
			
		    //do{ MYSERIAL1.print("Keyboard_Filament_head_input:"); }while(0);
	        NOMORE(newvalue, HEATER_0_MAXTEMP);
			
		    thermalManager.keyboard_nozzle_temp = newvalue;
	        thermalManager.setTargetHotend(newvalue, 0);
	        acceptedvalue = thermalManager.degTargetHotend(0);
			turn_falg =1;
			break;
		case Key_up_temp_bed:
		case Keyboard_cooldown_bed_input:
	        NOMORE(newvalue, BED_MAXTEMP);	
		    thermalManager.keyboard_bed_temp = newvalue;
	        thermalManager.setTargetBed(newvalue);
	        acceptedvalue = thermalManager.degTargetBed();
			turn_falg =1;
			break;	
		case Key_up_printrate:
			feedrate_percentage = newvalue;
			
			NOMORE(feedrate_percentage, 250);	
			key_Input_feedrate_percentage =feedrate_percentage;
			break;

			case Keyboard_jinliao_temp_input:
	        NOMORE(newvalue, HEATER_0_MAXTEMP);
			if(newvalue<EXTRUDE_MINTEMP)
			newvalue =	EXTRUDE_MINTEMP;
			
			thermalManager.setTargetHotend(newvalue, 0);
			acceptedvalue = thermalManager.degTargetHotend(0);
			filament_display_data =thermalManager.degTargetHotend(0);
			filament_temp_u       =thermalManager.degTargetHotend(0);
			turn_falg =1;
			break;
							
			case Keyboard_jinliao_length_input:
				Filament_Len = newvalue;
				NOMORE(Filament_Len, 500);
			break;
			case Keyboard_x_input:
			case Keyboard_y_input:
			case Keyboard_z_input:
			{
			    char buf[32]; // G1 X9999.99 F12345
			    char axiscode=0;
				if(var.VP==Keyboard_x_input)
				{
					axiscode='X';
				}
				else if(var.VP==Keyboard_y_input)
				{
					axiscode='Y';
				}
				else if(var.VP==Keyboard_z_input)
				{
					axiscode='Z';
				}
			    unsigned int value=int((uint16_t)newvalue)/10;
				unsigned int fraction=((uint16_t)(newvalue)-(value*10))%10;
			    snprintf_P(buf, 32, PSTR("G0 %c%d.%d F900"), axiscode, value, fraction);
				ExtUI::enqueue_one_now(buf);		
			}
			break;			
		default:
			break;
		
		
	}
	if(turn_falg ==1)
	{
		// reply to display the new value to update the view if the new value was rejected by the Thermal Manager.
		if (newvalue != acceptedvalue && var.send_to_display_handler) 
		{
		  var.send_to_display_handler(var);
		}
		skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
	}

}


void DGUSScreenHandler::HandleTemperatureChanged(DGUS_VP_Variable &var, void *val_ptr) {
  celsius_t newvalue = swap16(*(uint16_t*)val_ptr);
  celsius_t acceptedvalue;

  switch (var.VP) {
    #if HOTENDS >= 1
      case VP_RK_pla_temp:
	  	newvalue=PLA_TEMP;
        NOMORE(newvalue, HEATER_0_MAXTEMP);
        thermalManager.setTargetHotend(newvalue, 0);
        acceptedvalue = thermalManager.degTargetHotend(0);
		filament_display_data =thermalManager.degTargetHotend(0);

		newvalue = PLA_TEMP_BED;
        NOMORE(newvalue, BED_MAXTEMP);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
        break;
    #endif
	case VP_RK_abs_temp:
	  	newvalue=ABS_TEMP;
        NOMORE(newvalue, HEATER_0_MAXTEMP);
        thermalManager.setTargetHotend(newvalue, 0);
        acceptedvalue = thermalManager.degTargetHotend(0);	
		filament_display_data =thermalManager.degTargetHotend(0);
		
	  	newvalue=ABS_TEMP_BED;
        NOMORE(newvalue, BED_MAXTEMP);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
		break;
	case VP_RK_cooling_head:
	  	newvalue=0;
        NOMORE(newvalue, HEATER_0_MAXTEMP);
        thermalManager.setTargetHotend(newvalue, 0);
        acceptedvalue = thermalManager.degTargetHotend(0);
		break;
	case VP_RK_cooling_bed:
	  	newvalue=0;
        NOMORE(newvalue, BED_MAXTEMP);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
		break;
	case VP_RK_down_temp_head:
		if(thermalManager.degTargetHotend(0)>0)
			newvalue=thermalManager.degTargetHotend(0)-1;
		else
			newvalue=thermalManager.degTargetHotend(0);
			
        NOMORE(newvalue, HEATER_0_MAXTEMP);
        thermalManager.setTargetHotend(newvalue, 0);
        acceptedvalue = thermalManager.degTargetHotend(0);		
		filament_temp_u =thermalManager.degTargetHotend(0);
		break;
	case VP_RK_up_temp_head:
		newvalue=thermalManager.degTargetHotend(0)+1;
        NOMORE(newvalue, HEATER_0_MAXTEMP);
        thermalManager.setTargetHotend(newvalue, 0);
        acceptedvalue = thermalManager.degTargetHotend(0);
		filament_temp_u =thermalManager.degTargetHotend(0);
		
		break;
	case VP_RK_down_temp_bed:
		if(thermalManager.degTargetBed()>0)		
			newvalue=thermalManager.degTargetBed()-1;
		else
			newvalue=thermalManager.degTargetBed();
			
        NOMORE(newvalue, BED_MAXTEMP);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
		break;
	case VP_RK_up_temp_bed:
		newvalue=thermalManager.degTargetBed()+1;
        NOMORE(newvalue, BED_MAXTEMP);
        thermalManager.setTargetBed(newvalue);
        acceptedvalue = thermalManager.degTargetBed();
		break;
  }
  // reply to display the new value to update the view if the new value was rejected by the Thermal Manager.
  if (newvalue != acceptedvalue && var.send_to_display_handler) 
  {
  	var.send_to_display_handler(var);
  }
  skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
}

void DGUSScreenHandler::HandleFlowRateChanged(DGUS_VP_Variable &var, void *val_ptr) {
	#ifndef DGUS_LCD_UI_SUNLU
  #if HAS_EXTRUDERS
    uint16_t newvalue = swap16(*(uint16_t*)val_ptr);
    uint8_t target_extruder;
    switch (var.VP) {
      default: return;
      #if HOTENDS >= 1
        case VP_Flowrate_E0: target_extruder = 0; break;
      #endif
      #if HOTENDS >= 2
        case VP_Flowrate_E1: target_extruder = 1; break;
      #endif
    }

    planner.set_flow(target_extruder, newvalue);
    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  #else
    UNUSED(var); UNUSED(val_ptr);
  #endif
  #endif
}

void DGUSScreenHandler::HandleManualExtrude(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleManualExtrude");
#ifndef DGUS_LCD_UI_SUNLU

  int16_t movevalue = swap16(*(uint16_t*)val_ptr);
  float target = movevalue * 0.01f;
  ExtUI::extruder_t target_extruder;

  switch (var.VP) {
    #if HOTENDS >= 1
      case VP_MOVE_E0: target_extruder = ExtUI::extruder_t::E0; break;
    #endif
    #if HOTENDS >= 2
      case VP_MOVE_E1: target_extruder = ExtUI::extruder_t::E1; break;
    #endif
    default: return;
  }

  target += ExtUI::getAxisPosition_mm(target_extruder);
  ExtUI::setAxisPosition_mm(target, target_extruder);
  skipVP = var.VP;
  #endif
}

#if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
  void DGUSScreenHandler::HandleManualMoveOption(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleManualMoveOption");
    *(uint16_t*)var.memadr = swap16(*(uint16_t*)val_ptr);
  }
#endif

void DGUSScreenHandler::HandleMotorLockUnlock(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleMotorLockUnlock");

  char buf[4];
  const int16_t lock = swap16(*(uint16_t*)val_ptr);
  strcpy_P(buf, lock ? PSTR("M18") : PSTR("M17"));

  //DEBUG_ECHOPAIR(" ", buf);
  queue.enqueue_one_now(buf);
}

void DGUSScreenHandler::HandleSettings(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleSettings");
  uint16_t value = swap16(*(uint16_t*)val_ptr);
  switch (value) {
    default: break;
    case 1:
      TERN_(PRINTCOUNTER, print_job_timer.initStats());
      settings.reset();
      settings.save();
      break;
    case 2: settings.load(); break;
    case 3: settings.save(); break;
  }
}

void DGUSScreenHandler::HandleStepPerMMChanged(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleStepPerMMChanged");
#ifndef DGUS_LCD_UI_SUNLU

  uint16_t value_raw = swap16(*(uint16_t*)val_ptr);
  DEBUG_ECHOLNPAIR("value_raw:", value_raw);
  float value = (float)value_raw / 10;
  ExtUI::axis_t axis;
  switch (var.VP) {
    case VP_X_STEP_PER_MM: axis = ExtUI::axis_t::X; break;
    case VP_Y_STEP_PER_MM: axis = ExtUI::axis_t::Y; break;
    case VP_Z_STEP_PER_MM: axis = ExtUI::axis_t::Z; break;
    default: return;
  }
  DEBUG_ECHOLNPAIR_F("value:", value);
  ExtUI::setAxisSteps_per_mm(value, axis);
  DEBUG_ECHOLNPAIR_F("value_set:", ExtUI::getAxisSteps_per_mm(axis));
  skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  #endif
  return;
}

void DGUSScreenHandler::HandleStepPerMMExtruderChanged(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleStepPerMMExtruderChanged");
#ifndef DGUS_LCD_UI_SUNLU

  uint16_t value_raw = swap16(*(uint16_t*)val_ptr);
  DEBUG_ECHOLNPAIR("value_raw:", value_raw);
  float value = (float)value_raw / 10;
  ExtUI::extruder_t extruder;
  switch (var.VP) {
    default: return;
      #if HOTENDS >= 1
        case VP_E0_STEP_PER_MM: extruder = ExtUI::extruder_t::E0; break;
      #endif
      #if HOTENDS >= 2
        case VP_E1_STEP_PER_MM: extruder = ExtUI::extruder_t::E1; break;
      #endif
  }
  DEBUG_ECHOLNPAIR_F("value:", value);
  ExtUI::setAxisSteps_per_mm(value, extruder);
  DEBUG_ECHOLNPAIR_F("value_set:", ExtUI::getAxisSteps_per_mm(extruder));
  skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
  #endif
}

#if HAS_PID_HEATING
  void DGUSScreenHandler::HandlePIDAutotune(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandlePIDAutotune");
#ifndef DGUS_LCD_UI_SUNLU

    char buf[32] = {0};

    switch (var.VP) {
      default: break;
        #if ENABLED(PIDTEMP)
          #if HOTENDS >= 1
            case VP_PID_AUTOTUNE_E0: // Autotune Extruder 0
              sprintf_P(buf, PSTR("M303 E%d C5 S210 U1"), ExtUI::extruder_t::E0);
              break;
          #endif
          #if HOTENDS >= 2
            case VP_PID_AUTOTUNE_E1:
              sprintf_P(buf, PSTR("M303 E%d C5 S210 U1"), ExtUI::extruder_t::E1);
              break;
          #endif
        #endif
        #if ENABLED(PIDTEMPBED)
          case VP_PID_AUTOTUNE_BED:
            sprintf_P(buf, PSTR("M303 E-1 C5 S70 U1"));
            break;
        #endif
    }

    if (buf[0]) queue.enqueue_one_now(buf);

    #if ENABLED(DGUS_UI_WAITING)
      sendinfoscreen(PSTR("PID is autotuning"), PSTR("please wait"), NUL_STR, NUL_STR, true, true, true, true);
      GotoScreen(DGUSLCD_SCREEN_WAITING);
    #endif
	#endif
  }
#endif // HAS_PID_HEATING

#if HAS_BED_PROBE
  void DGUSScreenHandler::HandleProbeOffsetZChanged(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleProbeOffsetZChanged");

    const float offset = float(int16_t(swap16(*(uint16_t*)val_ptr))) / 100.0f;
    ExtUI::setZOffset_mm(offset);
    skipVP = var.VP; // don't overwrite value the next update time as the display might autoincrement in parallel
    return;
  }
#endif

#if HAS_FAN
  void DGUSScreenHandler::HandleFanControl(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandleFanControl");
    *(uint8_t*)var.memadr = *(uint8_t*)var.memadr > 0 ? 0 : 255;
  }
#endif

void DGUSScreenHandler::HandleHeaterControl(DGUS_VP_Variable &var, void *val_ptr) {
  DEBUG_ECHOLNPGM("HandleHeaterControl");
#ifndef DGUS_LCD_UI_SUNLU

  uint8_t preheat_temp = 0;
  switch (var.VP) {
    #if HOTENDS >= 1
      case VP_E0_CONTROL:
    #endif
    #if HOTENDS >= 2
      case VP_E1_CONTROL:
    #endif
    #if HOTENDS >= 3
      case VP_E2_CONTROL:
    #endif
    preheat_temp = PREHEAT_1_TEMP_HOTEND;
    break;

    case VP_BED_CONTROL:
      preheat_temp = PREHEAT_1_TEMP_BED;
      break;
  }

  *(int16_t*)var.memadr = *(int16_t*)var.memadr > 0 ? 0 : preheat_temp;
  #endif
}

#if ENABLED(DGUS_PREHEAT_UI)

  void DGUSScreenHandler::HandlePreheat(DGUS_VP_Variable &var, void *val_ptr) {
    DEBUG_ECHOLNPGM("HandlePreheat");
#ifndef DGUS_LCD_UI_SUNLU

    uint8_t e_temp = 0;
    #if ENABLED(HAS_HEATED_BED)
      uint8_t bed_temp = 0;
    #endif
    const uint16_t preheat_option = swap16(*(uint16_t*)val_ptr);
    switch (preheat_option) {
      default:
      case 0: // Preheat PLA
        #if defined(PREHEAT_1_TEMP_HOTEND) && defined(PREHEAT_1_TEMP_BED)
          e_temp = PREHEAT_1_TEMP_HOTEND;
          TERN_(HAS_HEATED_BED, bed_temp = PREHEAT_1_TEMP_BED);
        #endif
        break;
      case 1: // Preheat ABS
        #if defined(PREHEAT_2_TEMP_HOTEND) && defined(PREHEAT_2_TEMP_BED)
          e_temp = PREHEAT_2_TEMP_HOTEND;
          TERN_(HAS_HEATED_BED, bed_temp = PREHEAT_2_TEMP_BED);
        #endif
        break;
      case 2: // Preheat PET
        #if defined(PREHEAT_3_TEMP_HOTEND) && defined(PREHEAT_3_TEMP_BED)
          e_temp = PREHEAT_3_TEMP_HOTEND;
          TERN_(HAS_HEATED_BED, bed_temp = PREHEAT_3_TEMP_BED);
        #endif
        break;
      case 3: // Preheat FLEX
        #if defined(PREHEAT_4_TEMP_HOTEND) && defined(PREHEAT_4_TEMP_BED)
          e_temp = PREHEAT_4_TEMP_HOTEND;
          TERN_(HAS_HEATED_BED, bed_temp = PREHEAT_4_TEMP_BED);
        #endif
        break;
      case 7: break; // Custom preheat
      case 9: break; // Cool down
    }

    switch (var.VP) {
      default: return;
        #if HOTENDS >= 1
          case VP_E0_BED_PREHEAT:
            thermalManager.setTargetHotend(e_temp, 0);
            TERN_(HAS_HEATED_BED, thermalManager.setTargetBed(bed_temp));
            break;
        #endif
        #if HOTENDS >= 2
          case VP_E1_BED_PREHEAT:
            thermalManager.setTargetHotend(e_temp, 1);
            TERN_(HAS_HEATED_BED, thermalManager.setTargetBed(bed_temp));
            break;
        #endif
    }

    // Go to the preheat screen to show the heating progress
    GotoScreen(DGUSLCD_SCREEN_PREHEAT);
	#endif
  }

#endif // DGUS_PREHEAT_UI

#if ENABLED(POWER_LOSS_RECOVERY)

  void DGUSScreenHandler::HandlePowerLossRecovery(DGUS_VP_Variable &var, void *val_ptr) {
    uint16_t value = swap16(*(uint16_t*)val_ptr);
    if (value) {
      queue.inject_P(PSTR("M1000"));
      dgusdisplay.WriteVariable(RTX_filename, filelist.filename(), 32, true);
      GotoScreen(PLR_SCREEN_RECOVER);
    }
    else {
      recovery.cancel();
      GotoScreen(PLR_SCREEN_CANCEL);
    }
  }

#endif

void DGUSScreenHandler::UpdateNewScreen(DGUSLCD_Screens newscreen, bool popup) {
  DEBUG_ECHOLNPAIR("SetNewScreen: ", newscreen);
  if (!popup) {
    memmove(&past_screens[1], &past_screens[0], sizeof(past_screens) - 1);
    past_screens[0] = current_screen;
  }
  current_screen = newscreen;
  skipVP = 0;
  ForceCompleteUpdate();
}

void DGUSScreenHandler::PopToOldScreen() {
  DEBUG_ECHOLNPAIR("PopToOldScreen s=", past_screens[0]);
  
  //do{ MYSERIAL1.println(__FILE__); MYSERIAL1.println(__LINE__); }while(0);
//  do{ MYSERIAL1.print("past_screens:"); MYSERIAL1.println(past_screens[0]); }while(0);
  GotoScreen(past_screens[0], true);
  memmove(&past_screens[0], &past_screens[1], sizeof(past_screens) - 1);
  if(ui.language==UI_LANGUAGE_CHINESE)  past_screens[sizeof(past_screens) - 1] = DGUSLCD_SCREEN_CN_MAIN;
  else									past_screens[sizeof(past_screens) - 1] = DGUSLCD_SCREEN_EN_MAIN;
}
void DGUSScreenHandler::printtest() {
//	do{ MYSERIAL1.print(__FILE__); MYSERIAL1.println(__LINE__); }while(0);
//	MYSERIAL1.println(current_screen);
}
void DGUSScreenHandler::UpdateScreenVPData() {
  DEBUG_ECHOPAIR(" UpdateScreenVPData Screen: ", current_screen);
  
  watchdog_cnt =0;
  const uint16_t *VPList = DGUSLCD_FindScreenVPMapList(current_screen);
  if (!VPList) {
    DEBUG_ECHOLNPAIR(" NO SCREEN FOR: ", current_screen);
    ScreenComplete = true;
    return; // nothing to do, likely a bug or boring screen.
  }

  // Round-robin updating of all VPs.
  VPList += update_ptr;//?

  bool sent_one = false;
  do {
  	ScreenHandler.Address_Beyond_Fun(VPList,10);
    uint16_t VP = pgm_read_word(VPList);
    DEBUG_ECHOPAIR(" VP: ", VP);
    if (!VP) {
      update_ptr = 0;
      DEBUG_ECHOLNPGM(" UpdateScreenVPData done");
      ScreenComplete = true;
      return; // Screen completed.
    }
	

    if (VP == skipVP) { skipVP = 0; continue; }
	

    DGUS_VP_Variable rcpy;
    if (populate_VPVar(VP, &rcpy)) {
      uint8_t expected_tx = 6 + rcpy.size; // expected overhead is 6 bytes + payload.
      // Send the VP to the display, but try to avoid overrunning the Tx Buffer.
      // But send at least one VP, to avoid getting stalled.
      if (rcpy.send_to_display_handler && (!sent_one || expected_tx <= dgusdisplay.GetFreeTxBuffer())) {
        //DEBUG_ECHOPAIR(" calling handler for ", rcpy.VP);
        sent_one = true;
        rcpy.send_to_display_handler(rcpy);
      }
      else {
        ScreenComplete = false;
        return; // please call again!
      }
    }
  } while (++update_ptr, ++VPList, true);
  
}

void DGUSScreenHandler::GotoScreen(DGUSLCD_Screens screen, bool ispopup) {
  dgusdisplay.RequestScreen(screen);
  UpdateNewScreen(screen, ispopup);
}

void DGUSDisplay::RequestScreen(DGUSLCD_Screens screen) {
  DEBUG_ECHOLNPAIR("GotoScreen ", screen);
  const unsigned char gotoscreen[] = { 0x5A, 0x01, (unsigned char) (screen >> 8U), (unsigned char) (screen & 0xFFU) };
  WriteVariable(0x84, gotoscreen, sizeof(gotoscreen));
}

#endif // HAS_DGUS_LCD
