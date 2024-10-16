#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/dgus/sunlu/DGUSDisplayDef.cpp"
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
 * lcd/extui/dgus/origin/DGUSDisplayDef.cpp
 */

#include "../../../../inc/MarlinConfigPre.h"

#if ENABLED(DGUS_LCD_UI_SUNLU)

#include "DGUSDisplayDef.h"
#include "../DGUSDisplay.h"
#include "../DGUSScreenHandler.h"

#include "../../../../module/temperature.h"
#include "../../../../module/motion.h"
#include "../../../../module/planner.h"

#include "../../../marlinui.h"
#include "../../ui_api.h"

#if ENABLED(DGUS_UI_MOVE_DIS_OPTION)
  uint16_t distanceToMove = 10;
#endif
using namespace ExtUI;

///////////////////////////////////////////////////////////////////////
const uint16_t VPList_Main[] PROGMEM = {
  head_temp_real,
  head_temp_targe,
  bed_temp_real,
  bed_temp_targe,
  0x0000
};

const uint16_t VPList_WaitHeat[] PROGMEM = {
  head_temp_real,
  head_temp_targe,
  bed_temp_real,
  bed_temp_targe,
  0x0000
};

const uint16_t VPList_Filament[] PROGMEM = {
  head_temp_real,
  head_temp_targe,
  VP_NUM_Temp,
  VP_NUM_filament_len,
//  VP_RK_load_filament,
//  VP_RK_unload_filament,
  0x0000
};


const uint16_t VPList_Leveling[] PROGMEM = {
  VP_RK_Leveling,
  0x0000
};


const uint16_t VPList_Leveling_child[] PROGMEM = {
	VP_Num_Point_1,
	VP_Num_Point_2,
	VP_Num_Point_3,
	VP_Num_Point_4,
	VP_Num_Point_5,
	VP_Num_Point_7,
	VP_Num_Point_8,
	VP_Num_Point_9,
	VP_Num_Point_10,
	VP_Num_Point_11,
	VP_Num_Point_12,
	VP_Num_Point_13,
	VP_Num_Point_14,
	VP_Num_Point_15,
	VP_Num_Point_16,
  	0x0000
};


const uint16_t VPList_DEAL_EVENT[] PROGMEM = {
	DEAL_EVENT,
  	0x0000
};


const uint16_t VPList_DRYBOX[] PROGMEM = {
	VP_Cur_Temp,
	VP_Cur_humidity,
	VP_Dry_Time,
	VP_Targe_Temp,
  	0x0000
};




///////////////////////////////////////////////////////////////////////


const uint16_t VPList_Boot[] PROGMEM = {
  0x0000
};

const uint16_t VPList_Temp[] PROGMEM = {
#ifndef DGUS_LCD_UI_SUNLU

  #if HOTENDS >= 1
    VP_T_E0_Is, VP_T_E0_Set,
  #endif
  #if HOTENDS >= 2
    VP_T_E1_Is, VP_T_E1_Set,
  #endif
  #if HAS_HEATED_BED
    VP_T_Bed_Is, VP_T_Bed_Set,
  #endif
  0x0000
  #endif
};

const uint16_t VPList_TempControl[] PROGMEM={
  head_temp_real,
  head_temp_targe,
  bed_temp_real,
  bed_temp_targe,
  0x0000	
};

const uint16_t VPList_Status[] PROGMEM = {
  //RTX_filename,
  #if HOTENDS >= 1
  head_temp_real, head_temp_targe,
  #endif
  #if HAS_HEATED_BED
  bed_temp_real, bed_temp_targe,
  #endif
 /* VP_XPos, VP_YPos, VP_ZPos,*/VP_EPos,
  VP_Feedrate_Percentage,
  VP_PrintTime,
  VP_real_rate,
  VP_PrintProgress_Percentage,
  0x0000
};

const uint16_t VPList_Status2[] PROGMEM = {
	#ifndef DGUS_LCD_UI_SUNLU
  // VP_M117, for completeness, but it cannot be auto-uploaded
  #if HOTENDS >= 1
    VP_Flowrate_E0,
  #endif
  #if HOTENDS >= 2
    VP_Flowrate_E1,
  #endif
  VP_PrintProgress_Percentage,
  VP_PrintTime,
  0x0000
  #endif
};

const uint16_t VPList_ManualMove[] PROGMEM = {
  VP_XPos, VP_YPos, VP_ZPos,
  0x0000
};

const uint16_t VPList_ManualExtrude[] PROGMEM = {
  VP_EPos,
  0x0000
};

const uint16_t VPList_FanAndFeedrate[] PROGMEM = {
	#ifndef DGUS_LCD_UI_SUNLU
  VP_Feedrate_Percentage, VP_Fan0_Percentage,
  0x0000
  #endif
};

const uint16_t VPList_SD_FlowRates[] PROGMEM = {
	#ifndef DGUS_LCD_UI_SUNLU
  VP_Flowrate_E0, VP_Flowrate_E1,
  0x0000
  #endif
};
const uint16_t VPList_SDFileList[] PROGMEM = {
  VP_RTX_sdfile_col_1, 
  VP_RTX_sdfile_col_2,
  VP_RTX_sdfile_col_3,
  VP_RTX_sdfile_col_4,
 // RTX_filename,
  0x0000
};
const uint16_t VPList_SDFileNullList[] PROGMEM = {
  0x0000
};
const uint16_t VPList_SD_PrintManipulation[] PROGMEM = {
  VP_PrintProgress_Percentage, VP_PrintTime,
  0x0000
};


const struct VPMapping VPMap[] PROGMEM = {
  {DGUSLCD_SCREEN_BOOT     , VPList_Boot},
  { DGUSLCD_SCREEN_CN_MAIN, VPList_Main },
  { DGUSLCD_SCREEN_EN_MAIN, VPList_Main },
 // { DGUSLCD_SCREEN_TEMPERATURE, VPList_Temp },
  { DGUSLCD_SCREEN_EN_STATUS, VPList_Status },
  { DGUSLCD_SCREEN_CN_STATUS, VPList_Status },
  { DGUSLCD_SCREEN_EN_PAUSE_SELECT, VPList_Status },
  { DGUSLCD_SCREEN_CN_PAUSE_SELECT, VPList_Status },
  { DGUSLCD_SCREEN_CN_STATUS_PAUSE, VPList_Status },
  { DGUSLCD_SCREEN_EN_STATUS_PAUSE, VPList_Status },
//  { DGUSLCD_SCREEN_STATUS2, VPList_Status2 },
  { DGUSLCD_SCREEN_EN_AXIS_PAGE, VPList_ManualMove },
  

////  { DGUSLCD_SCREEN_EN_MENSUR_LEVEL, VPList_ManualMove },
  //{ DGUSLCD_SCREEN_MANUALEXTRUDE, VPList_ManualExtrude },
  //{ DGUSLCD_SCREEN_FANANDFEEDRATE, VPList_FanAndFeedrate },
//  { DGUSLCD_SCREEN_FLOWRATES, VPList_SD_FlowRates },
  { DGUSLCD_SCREEN_SDPRINTMANIPULATION, VPList_SD_PrintManipulation },
  { DGUSLCD_SCREEN_CN_SDFILELIST, VPList_SDFileList },
  { DGUSLCD_SCREEN_EN_SDFILELIST, VPList_SDFileList },
  { DGUSLCD_SCREEN_SDFILELIST_NULL, VPList_SDFileNullList },
  { DGUSLCD_SCREEN_SDFILELIST_NULL_CN, VPList_SDFileNullList },
  { DGUSLCD_SCREEN_CN_LEVELING, VPList_Leveling },
  { DGUSLCD_SCREEN_EN_LEVELING, VPList_Leveling },
  { DGUSLCD_SCREEN_EN_TEMP,VPList_TempControl},
  { DGUSLCD_SCREEN_CN_TEMP,VPList_TempControl},
  { DGUSLCD_SCREEN_CN_TEMP_OTHER,VPList_TempControl},
  { DGUSLCD_SCREEN_EN_TEMP_OTHER,VPList_TempControl},
  
  
  { DGUSLCD_SCREEN_EN_FILAMENT_PAGE,VPList_Filament},
  { DGUSLCD_SCREEN_CN_FILAMENT_PAGE,VPList_Filament},
  { DGUSLCD_SCREEN_EN_UTILITIES,VPList_Main},
//  { DGUSLCD_SCREEN_EN_RATE_PAGE,VPList_Rate},
 // { DGUSLCD_SCREEN_CN_RATE_PAGE,VPList_Rate},
  { DGUSLCD_SCREEN_CN_LEVELING_Child,VPList_Leveling_child},  
  { DGUSLCD_SCREEN_EN_LEVELING_Child,VPList_Leveling_child},  
//  { DGUSLCD_SCREEN_EN_CHANGE_FILAMENT,VPList_DEAL_EVENT},  
//  { DGUSLCD_SCREEN_CN_CHANGE_FILAMENT,VPList_DEAL_EVENT},  

  { DGUSLCD_SCREEN_EN_CHANGE_FILAMENT,VPList_Main},  
  { DGUSLCD_SCREEN_CN_CHANGE_FILAMENT,VPList_Main},  

  
  { DGUSLCD_SCREEN_CN_DRYBOX,VPList_DRYBOX},  
  { DGUSLCD_SCREEN_EN_DRYBOX,VPList_DRYBOX},  

  { DGUSLCD_SCREEN_CN_DTYBOXOTHER,VPList_DRYBOX},  
  { DGUSLCD_SCREEN_EN_DTYBOXOTHER,VPList_DRYBOX},  
  { DGUSLCD_SCREEN_CN_DTYBOX_TWO_OTHER,VPList_DRYBOX},  
  { DGUSLCD_SCREEN_EN_DTYBOX_TWO_OTHER,VPList_DRYBOX},  

  

  { DGUSLCD_SCREEN_CN_DTYBOX_OTHER,VPList_DRYBOX},  
  { DGUSLCD_SCREEN_EN_DTYBOX_OTHER,VPList_DRYBOX},  
//  { DGUSLCD_SCREEN_CN_DTYBOX_TWO,VPList_DRYBOX},	
//  { DGUSLCD_SCREEN_EN_DTYBOX_TWO,VPList_DRYBOX},	

  
  
  { DGUSLCD_SCREEN_CONFIRM,VPList_SDFileList},  

  { DGUSLCD_SCREEN_CN_WAITPOWERLOSS,   VPList_Main },
  { DGUSLCD_SCREEN_EN_WAITPOWERLOSS,   VPList_Main },
  { DGUSLCD_SCREEN_EN_AXIS_PAGE,       VPList_ManualMove },
  { DGUSLCD_SCREEN_CN_AXIS_PAGE,   VPList_ManualMove },
  { DGUSLCD_SCREEN_ONE_EN_AXIS_PAGE,   VPList_ManualMove },
  { DGUSLCD_SCREEN_TEN_EN_AXIS_PAGE,   VPList_ManualMove },

  { DGUSLCD_SCREEN_ONE_CN_AXIS_PAGE,   VPList_ManualMove },
  { DGUSLCD_SCREEN_TWO_CN_AXIS_PAGE,   VPList_ManualMove },
  { DGUSLCD_SCREEN_THREE_CN_AXIS_PAGE, VPList_ManualMove },


  
  { DGUSLCD_SCREEN_CN_ONLINEPRINT, VPList_Status },
  { DGUSLCD_SCREEN_EN_ONLINEPRINT, VPList_Status },
  { DGUSLCD_SCREEN_CN_WAITHEATING, VPList_WaitHeat },
  { DGUSLCD_SCREEN_EN_WAITHEATING, VPList_WaitHeat },
  { DGUSLCD_SCREEN_CN_WAITOPERATE, VPList_Main },
  { DGUSLCD_SCREEN_EN_WAITOPERATE, VPList_Main },
  { DGUSLCD_SCREEN_CN_UTILITIES, VPList_Main },
  
  { 0 , nullptr } // List is terminated with an nullptr as table entry.
};
const char MarlinVersion[] PROGMEM = SHORT_BUILD_VERSION;
// Helper to define a DGUS_VP_Variable for common use cases.
#define VPHELPER(VPADR, VPADRVAR, RXFPTR, TXFPTR ) { .VP=VPADR, .memadr=VPADRVAR, .size=sizeof(VPADRVAR), \
  .set_by_display_handler = RXFPTR, .send_to_display_handler = TXFPTR }

// Helper to define a DGUS_VP_Variable when the sizeo of the var cannot be determined automaticalyl (eg. a string)
#define VPHELPER_STR(VPADR, VPADRVAR, STRLEN, RXFPTR, TXFPTR ) { .VP=VPADR, .memadr=VPADRVAR, .size=STRLEN, \
  .set_by_display_handler = RXFPTR, .send_to_display_handler = TXFPTR }
static float testtemp=-1.3152;
static float aacelsius=5.523;
static int16_t dddd=5;
const struct DGUS_VP_Variable ListOfVP[] PROGMEM = {
  // Helper to detect touch events
  	//LOW POWER
  	
    VPHELPER(VP_GetCFG,nullptr ,&ScreenHandler.DGUSLCD_SYS_config ,nullptr),

	//main
	
    VPHELPER(E_VP_UI_PK_PRINT,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(C_VP_UI_PK_PRINT,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(E_VP_UI_RK_UTILITIES,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(C_VP_UI_RK_UTILITIES,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(E_VP_UI_RK_INFO,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
  
  // Temperature Data
  
    VPHELPER(VP_RK_Temp,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
  
    VPHELPER(VP_RK_pla_temp,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_abs_temp,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_cooling_head,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_cooling_bed,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_down_temp_head,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_down_temp_bed,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_up_temp_head,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    VPHELPER(VP_RK_up_temp_bed,nullptr ,&ScreenHandler.HandleTemperatureChanged ,nullptr),
    
    VPHELPER(Key_up_temp_head,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
    VPHELPER(Key_up_temp_bed,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
    VPHELPER(Key_up_printrate,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
    VPHELPER(Keyboard_x_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
    VPHELPER(Keyboard_y_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
    VPHELPER(Keyboard_z_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
	  
    VPHELPER(Keyboard_jinliao_temp_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
	VPHELPER(Keyboard_jinliao_length_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
	VPHELPER(Keyboard_cooldown_head_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
	VPHELPER(Keyboard_cooldown_bed_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
	  
    VPHELPER(Keyboard_Filament_head_input,nullptr ,&ScreenHandler.HandlekeyboardChanged ,nullptr),
  


	//axis
	
    VPHELPER(VP_RK_Axis,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    
    VPHELPER(VP_RK_01_step,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_RK_1_step,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_RK_10_step,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    
    VPHELPER(VP_RK_home_all,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_move_x_r,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_move_x_p,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_move_z_p,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_move_z_r,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_move_y_p,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_move_y_r,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_home_y,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_home_z,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),
    VPHELPER(VP_RK_home_x,nullptr ,&ScreenHandler.HandleManualMove ,nullptr),



  
	//filament
    VPHELPER(VP_RK_Filament,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    
    VPHELPER(VP_RK_filament_pla,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_RK_filament_abs,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    
    VPHELPER(VP_RK_load_filament,nullptr ,ScreenHandler.HandleFilamentOption ,nullptr),
    VPHELPER(VP_RK_unload_filament,nullptr ,ScreenHandler.HandleFilamentOption ,nullptr),//ScreenHandler.HandleFilamentLoadUnload
//    VPHELPER(VP_NUM_Temp, &ScreenHandler.filament_temp_u, nullptr, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_NUM_Temp, &ScreenHandler.filament_display_data, nullptr, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  	VPHELPER(VP_RK_dec_filament_len,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
  	VPHELPER(VP_RK_add_filament_len,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
  	VPHELPER(VP_NUM_filament_len,&ScreenHandler.Filament_Len ,nullptr ,&ScreenHandler.DGUSLCD_SendWordValueToDisplay),
  	
	//drybox
//		,
//	VP_Cur_humidity,
//	VP_Dry_Time,
	

    VPHELPER(VP_RK_DryBox,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_Add_Targe_Temp,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_Dec_Targe_Temp,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_Add_Dry_Time,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_Dec_Dry_Time,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_DRYBOX_CANCEL,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
    VPHELPER(VP_DRYBOX_apply,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),    
//    VPHELPER(VP_Cur_Temp,&thermalManager.temp_drybox_center_hotend[0].celsius , nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
	VPHELPER(VP_Cur_Temp,&thermalManager.Temperature_Center_Val , nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
	

    VPHELPER(VP_Targe_Temp,&ScreenHandler.drybox_targe_temp , nullptr, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    VPHELPER(VP_Cur_humidity,&thermalManager.temp_drybox_ph_hotend[0].celsius , nullptr,ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    VPHELPER_STR(VP_Dry_Time, nullptr , VP_PrintTime_LEN, nullptr,ScreenHandler.DGUSLCD_SendPrintTimeToDisplay),
    VPHELPER(VP_RK_PowerLow,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
       

   //disable axis
    VPHELPER(VP_RK_disableaxis,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),

  //langauge
  
    VPHELPER(VP_RK_language,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
	//thermalManager.temp_hotend[0].target


   //leveling
    VPHELPER(VP_RK_Leveling,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Leveling ,nullptr),//&ScreenHandler.DGUSLCD_UTILITIES_Leveling
    VPHELPER(VP_RK_Aux_Level,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Leveling ,nullptr),
    VPHELPER(VP_RK_Measure_Level,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Leveling ,nullptr),

  
   //reset
  VPHELPER(VP_RK_reset,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),

  //POWER_LOSS_RECOVERY
  VPHELPER(VP_RK_POWER_LOSS_RECOVERY,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
   
  

	//print status
	  // Feedrate
  VPHELPER(VP_Feedrate_Percentage, &feedrate_percentage, ScreenHandler.DGUSLCD_SetValueDirectly<int16_t>, &ScreenHandler.DGUSLCD_SendWordValueToDisplay ),
  VPHELPER(VP_RK_add_rate,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
  VPHELPER(VP_RK_dec_rate,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
  #if ENABLED(BABYSTEPPING)
  VPHELPER(VP_SD_Print_LiveAdjustZ_up, nullptr, ScreenHandler.HandleLiveAdjustZ, nullptr),
  VPHELPER(VP_SD_Print_LiveAdjustZ_down, nullptr, ScreenHandler.HandleLiveAdjustZ, nullptr),
  #endif

  // Position Data
  VPHELPER(VP_XPos, &current_position.x, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
  VPHELPER(VP_YPos, &current_position.y, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
  VPHELPER(VP_ZPos, &current_position.z, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<1>),
  VPHELPER(VP_EPos, &probe.offset.z, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<2>),
  
  // Print Progress
  VPHELPER(VP_PrintProgress_Percentage, nullptr, nullptr, ScreenHandler.DGUSLCD_SendPrintProgressToDisplay ),
  VPHELPER_STR(VP_PrintTime, nullptr, VP_PrintTime_LEN, nullptr, ScreenHandler.DGUSLCD_SendPrintTimeToDisplay ),
  VPHELPER(VP_SD_ResumePauseAbort, nullptr, ScreenHandler.DGUSLCD_SD_ResumePauseAbort, nullptr),
  VPHELPER(VP_SD_Print_drybox, nullptr, ScreenHandler.DGUSLCD_SD_Enterdrybox, nullptr),
  VPHELPER(Back_RK_returndrybox, nullptr, ScreenHandler.DGUSLCD_SD_Enterdrybox, nullptr),
  VPHELPER(TmpReturn_drybox, nullptr, ScreenHandler.DGUSLCD_SD_Enterdrybox, nullptr),
  VPHELPER(OnlineReturn_drybox, nullptr, ScreenHandler.DGUSLCD_SD_Enterdrybox, nullptr),

  

  
  VPHELPER(Flianment_print_pause, nullptr, ScreenHandler.DGUSLCD_SD_FilamentResumePauseAbort, nullptr),
  

  
  #if HOTENDS >= 1
  //&thermalManager.temp_hotend[0].celsius
    VPHELPER(head_temp_real,&thermalManager.temp_hotend[0].celsius , nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    //VPHELPER(head_temp_real,&thermalManager.temp_drybox_center_hotend[0].celsius , nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    VPHELPER(head_temp_targe, &thermalManager.temp_hotend[0].target, nullptr, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
    //VPHELPER(VP_T_E0_Is, nullptr, nullptr, SET_VARIABLE(getActualTemp_celsius, E0, long)),
    //VPHELPER(VP_T_E0_Set, nullptr, GET_VARIABLE(setTargetTemp_celsius, E0),SET_VARIABLE(getTargetTemp_celsius, E0)),
  #endif
  #if HAS_HEATED_BED
  //&thermalManager.temp_bed.celsius// //DGUSLCD_SendFloatAsLongValueToDisplay<1>//thermalManager.temp_bed.target
  //ScreenHandler.HandleTemperatureChanged
    VPHELPER(bed_temp_real, &thermalManager.temp_bed.celsius, nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
   // VPHELPER(bed_temp_real, &thermalManager.temp_drybox_rth_hotend[0].celsius , nullptr, ScreenHandler.DGUSLCD_SendFloatAsIntValueToDisplay<0>),
    VPHELPER(bed_temp_targe, &thermalManager.temp_bed.target, nullptr, &ScreenHandler.DGUSLCD_SendWordValueToDisplay),
   // VPHELPER(VP_BED_CONTROL, &thermalManager.temp_bed.target, &ScreenHandler.HandleHeaterControl, nullptr),
   // VPHELPER(VP_BED_STATUS, &thermalManager.temp_bed.target, nullptr, &ScreenHandler.DGUSLCD_SendHeaterStatusToDisplay),
    #if ENABLED(PIDTEMPBED)
      VPHELPER(VP_BED_PID_P, &thermalManager.temp_bed.pid.Kp, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      VPHELPER(VP_BED_PID_I, &thermalManager.temp_bed.pid.Ki, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
      VPHELPER(VP_BED_PID_D, &thermalManager.temp_bed.pid.Kd, ScreenHandler.HandleTemperaturePIDChanged, ScreenHandler.DGUSLCD_SendTemperaturePID),
    #endif
  #endif

  // SDCard File listing.
  #if ENABLED(SDSUPPORT)
    VPHELPER(VP_SD_ScrollEvent, nullptr, ScreenHandler.DGUSLCD_SD_ScrollFilelist, nullptr),
    VPHELPER(VP_SD_FileSelected, nullptr, ScreenHandler.DGUSLCD_SD_FileSelected, nullptr),
    VPHELPER(VP_SD_FileSelectConfirm, nullptr, ScreenHandler.DGUSLCD_SD_StartPrint, nullptr),
    VPHELPER_STR(VP_RTX_sdfile_col_1,  nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_RTX_sdfile_col_2,  nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_RTX_sdfile_col_3,  nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_RTX_sdfile_col_4,  nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    //VPHELPER_STR(RTX_filename,  nullptr, VP_SD_FileName_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
	  
	VPHELPER(VP_RK_Fastprint,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
	VPHELPER(VP_SD_FilePrint_AutoLeve,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
	VPHELPER(VP_SD_FilePrint_FilamentRunout,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
	VPHELPER(VP_SD_FilePrint_Filament_Jams,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),

    
  #endif
// Back_do
  

    VPHELPER_STR(VP_MSGSTR1,  nullptr, VP_MSGSTR1_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_MSGSTR2,  nullptr, VP_MSGSTR2_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_MSGSTR3,  nullptr, VP_MSGSTR3_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_MSGSTR4,  nullptr, VP_MSGSTR4_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    VPHELPER_STR(VP_device_info,  nullptr, VP_MSGSTR4_LEN, nullptr, ScreenHandler.DGUSLCD_SD_SendFilename ),
    
	VPHELPER(VP_M108,nullptr ,&ScreenHandler.DGUSLCD_UTILITIES_Deal ,nullptr),
	VPHELPER(Back_RK_returnmain,nullptr, ScreenHandler.DGUSLCD_BACK_Deal,nullptr),
	VPHELPER(Back_RK_returnutilities,nullptr, ScreenHandler.DGUSLCD_BACK_Deal,nullptr),
	VPHELPER(Back_RK_returnleveling,nullptr, ScreenHandler.DGUSLCD_BACK_Deal,nullptr),
	
  // Messages for the User, shared by the popup and the kill screen. They cant be autouploaded as we do not buffer content.
  VPHELPER(0, 0, 0, 0)  // must be last entry.
};

#endif // DGUS_LCD_UI_SUNLU
