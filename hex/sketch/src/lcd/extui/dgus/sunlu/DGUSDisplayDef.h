#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/extui/dgus/sunlu/DGUSDisplayDef.h"
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

#include "../DGUSDisplayDef.h"

enum DGUSLCD_Screens : uint8_t {
  DGUSLCD_SCREEN_BOOT                = 0,
  DGUSLCD_SCREEN_CN_MAIN             = 1,
  DGUSLCD_SCREEN_EN_MAIN             = 2,
  DGUSLCD_SCREEN_CN_SDFILELIST		 = 3,
  DGUSLCD_SCREEN_EN_SDFILELIST       = 4,
  DGUSLCD_SCREEN_CN_STATUS           = 5,
  DGUSLCD_SCREEN_EN_STATUS           = 6,
  DGUSLCD_SCREEN_CN_UTILITIES		 = 7,
  DGUSLCD_SCREEN_EN_UTILITIES		 = 8,
  DGUSLCD_SCREEN_EN_TEMP		 	 = 9,
  DGUSLCD_SCREEN_CN_AXIS_PAGE        = 10,
  DGUSLCD_SCREEN_CN_FILAMENT_PAGE    = 11,
  DGUSLCD_SCREEN_EN_FILAMENT_PAGE    = 12,
  DGUSLCD_SCREEN_ONE_EN_AXIS_PAGE    = 13,
  DGUSLCD_SCREEN_TEN_EN_AXIS_PAGE    = 14,
  DGUSLCD_SCREEN_EN_LEVELING_Child_OVER = 15,
  DGUSLCD_SCREEN_CN_LEVELING_Child_OVER = 16,
  DGUSLCD_SCREEN_CN_PAUSE_SELECT		= 17,
  DGUSLCD_SCREEN_EN_PAUSE_SELECT		= 18,
  DGUSLCD_SCREEN_CN_CANCEL_SELECT 		= 19,
  DGUSLCD_SCREEN_EN_CANCEL_SELECT		= 20,
  //DGUSLCD_SCREEN_TEMPERATURE         = 20,
  DGUSLCD_SCREEN_EN_CHANGE_FILAMENT  = 21,
  DGUSLCD_SCREEN_CN_CHANGE_FILAMENT  = 22,
  DGUSLCD_SCREEN_CN_PRINTINGFINISHED  = 23,
  DGUSLCD_SCREEN_EN_PRINTINGFINISHED  = 24,
  DGUSLCD_SCREEN_CN_PRINTINGCONTINUE  = 25,
  DGUSLCD_SCREEN_EN_PRINTINGCONTINUE  = 26,
  DGUSLCD_SCREEN_CN_SHUTMOTO		  = 27,
  DGUSLCD_SCREEN_EN_SHUTMOTO 		  = 28,
  
  DGUSLCD_SCREEN_CONFIRM             = 29,
  //DGUSLCD_SCREEN_STATUS              = 30,
  DGUSLCD_SCREEN_CN_DRYBOX           = 32,
  DGUSLCD_SCREEN_CN_AUXLEVEL	     = 33,
  DGUSLCD_SCREEN_EN_AUXLEVEL	     = 34,
  DGUSLCD_SCREEN_SDFILELIST_NULL     = 35,
  DGUSLCD_SCREEN_LANGUAGE_SELECT     = 36,
  DGUSLCD_SCREEN_SDFILELIST_NULL_CN  = 37,
  DGUSLCD_SCREEN_CN_LEVELING_Child	 = 38,
  DGUSLCD_SCREEN_CN_LEVELING		 = 39,
  DGUSLCD_SCREEN_CN_MENSUR_LEVEL     = 40,
  DGUSLCD_SCREEN_CN_STATUS_PAUSE     = 41,
  DGUSLCD_SCREEN_EN_STATUS_PAUSE     = 42,
  DGUSLCD_SCREEN_CONFIRM_EN          = 43,
  DGUSLCD_SCREEN_CN_TEMP		 	 = 44,
  DGUSLCD_SCREEN_EN_LEVELING		 = 45,
  DGUSLCD_SCREEN_CN_WAIT_MOVE        = 46,
  DGUSLCD_SCREEN_EN_WAIT_MOVE        = 47,
  //DGUSLCD_SCREEN_FLOWRATES           = 47,
  DGUSLCD_SCREEN_EN_LEVELING_Child	 = 48,
  DGUSLCD_SCREEN_EN_MENSUR_LEVEL     = 49,
  DGUSLCD_SCREEN_EN_DRYBOX           = 50,
  DGUSLCD_SCREEN_SDPRINTMANIPULATION = 52,
  DGUSLCD_SCREEN_LANGUAGE_SELECT_EN  = 53,
  DGUSLCD_SCREEN_EN_POWER_LOSS       = 54,
  DGUSLCD_SCREEN_CN_POWER_LOSS       = 55,
  DGUSLCD_SCREEN_CN_TEST_DRYBOX      = 58,
  DGUSLCD_SCREEN_EN_TEST_DRYBOX      = 59,

  DGUSLCD_SCREEN_ONE_CN_AXIS_PAGE    = 60,
  DGUSLCD_SCREEN_TWO_CN_AXIS_PAGE	 = 61,
  DGUSLCD_SCREEN_THREE_CN_AXIS_PAGE	 = 62,


  
  DGUSLCD_SCREEN_EN_AXIS_PAGE		 = 62,
  
  DGUSLCD_SCREEN_CN_INFO 		     = 63,
  DGUSLCD_SCREEN_KILL 		         = 64,
  DGUSLCD_SCREEN_EN_INFO 		     = 65,
  DGUSLCD_SCREEN_CN_WAITPOWERLOSS	 = 67,
  DGUSLCD_SCREEN_CN_WAITHEATING		 = 68,
  DGUSLCD_SCREEN_CN_WAITOPERATE		 = 69,

  DGUSLCD_SCREEN_CN_ONLINEPRINT		 = 92,
  DGUSLCD_SCREEN_CN_FILAMENT_CANCEL	 = 95,

  DGUSLCD_SCREEN_EN_FILAMENT_CANCEL	 = 97,
  DGUSLCD_SCREEN_EN_WAITPOWERLOSS	 = 98,
  
  DGUSLCD_SCREEN_EN_WAITHEATING 	 = 99,
  DGUSLCD_SCREEN_EN_WAITOPERATE 	 = 100,
  DGUSLCD_SCREEN_EN_ONLINEPRINT 	 = 101,
  DGUSLCD_SCREEN_CN_DTYBOXOTHER 	 = 102,//  use
  DGUSLCD_SCREEN_EN_DTYBOXOTHER 	 = 103,//  use
  DGUSLCD_SCREEN_CN_TEMP_OTHER	 	 = 104,
  DGUSLCD_SCREEN_EN_TEMP_OTHER		 = 105,

  DGUSLCD_SCREEN_CN_DTYBOX_OTHER	 = 110,
  DGUSLCD_SCREEN_EN_DTYBOX_OTHER	 = 111,
  
  DGUSLCD_SCREEN_N0_CN_DTYBOX	     = 112,
  DGUSLCD_SCREEN_N0_EN_DTYBOX		 = 113,
  DGUSLCD_SCREEN_CN_NO_FILAMENT		 = 114,
  DGUSLCD_SCREEN_EN_NO_FILAMENT		 = 115,
  DGUSLCD_EN_SCREEN_BOOT 			 = 116,

  DGUSLCD_SCREEN_CN_DTYBOX_TWO_OTHER = 117,
  DGUSLCD_SCREEN_EN_DTYBOX_TWO_OTHER = 118,
  DGUSLCD_CN_SCREEN_WELCOME			 = 119,
  
//  DGUSLCD_SCREEN_POWER_LOSS          = 100,
  DGUSLCD_SCREEN_PREHEAT             = 120,
  DGUSLCD_SCREEN_UTILITY             = 110,
  DGUSLCD_SCREEN_FILAMENT_HEATING    = 146,
  DGUSLCD_SCREEN_FILAMENT_LOADING    = 148,
  DGUSLCD_SCREEN_FILAMENT_UNLOADING  = 158,
  DGUSLCD_SCREEN_SDPRINTTUNE         = 170,
 // DGUSLCD_SCREEN_KILL                = 250, ///< Kill Screen. Must always be 250 (to be able to display "Error wrong LCD Version")
  DGUSLCD_SCREEN_WAITING             = 251,
  DGUSLCD_SCREEN_POPUP               = 252, ///< special target, popup screen will also return this code to say "return to previous screen"
  DGUSLDC_SCREEN_UNUSED              = 255
};




/*sunlu ui config*/

//C--->chinese   E---->English

constexpr uint16_t C_UI_MAIN_PAGE= 1;
constexpr uint16_t E_UI_MAIN_PAGE= 2;
constexpr uint16_t E_UI_PRINT_DONE_PAGE= 24;










constexpr uint16_t DEAL_EVENT= 0xFFFF;

constexpr uint16_t VP_GetCFG=0x0080;

constexpr uint16_t E_VP_UI_PK_PRINT= 0x1000;
constexpr uint16_t E_VP_UI_RK_UTILITIES= 0x2000;
constexpr uint16_t E_VP_UI_RK_INFO= 0x3000;

constexpr uint16_t C_VP_UI_PK_PRINT= E_VP_UI_PK_PRINT+0x3000;
constexpr uint16_t C_VP_UI_RK_UTILITIES= E_VP_UI_RK_UTILITIES+0x3000;






constexpr uint16_t head_temp_targe=0xF002;
constexpr uint16_t head_temp_real=0xF000;
constexpr uint16_t bed_temp_real=0xF004;
constexpr uint16_t bed_temp_targe=0xF006;
constexpr uint16_t test_vp=0xF008;

constexpr uint16_t VP_T_Bed_Is = 0x3080;  // 4 Byte Integer



//Back
constexpr uint16_t Back_RK_returnmain=0x2FFF;
constexpr uint16_t Back_RK_returnutilities=0x24F0;
constexpr uint16_t Back_RK_returnleveling=0x24F1;
constexpr uint16_t Back_RK_returndrybox=0x24F2;
constexpr uint16_t TmpReturn_drybox=0x24F3;
constexpr uint16_t OnlineReturn_drybox=0x24F4;




//print info


constexpr uint16_t RTX_filename=0x1090+3;

////SD FILE SELECT contorl
constexpr uint16_t VP_RTX_sdfile_col_1=0x1010+3;
constexpr uint16_t VP_RTX_sdfile_col_2=0x1030+3;
constexpr uint16_t VP_RTX_sdfile_col_3=0x1050+3;
constexpr uint16_t VP_RTX_sdfile_col_4=0x1070+3;

constexpr uint16_t VP_RK_sdfile_col_1=0x1005;
constexpr uint16_t VP_RK_sdfile_col_2=0x1005;
constexpr uint16_t VP_RK_sdfile_col_3=0x1005;
constexpr uint16_t VP_RK_sdfile_col_4=0x1005;

constexpr uint16_t VP_RK_UP_PAGE=0x1009;
constexpr uint16_t VP_RK_DOWN_PAGE=0x1009;

//PRINT INFO MESSAGE
//constexpr uint16_t VP_TX_print_time=0x1101;
constexpr uint16_t VP_TX_surplus_time=0x1102;

constexpr uint16_t VP_Feedrate_Percentage = 0x1102; // 2 Byte Integer (0..100)
// Actual Position
constexpr uint16_t VP_XPos = 0x1104;  // 4 Byte Fixed point number; format xxx.yy
constexpr uint16_t VP_YPos = 0x1106;  // 4 Byte Fixed point number; format xxx.yy
constexpr uint16_t VP_ZPos = 0x1108;  // 4 Byte Fixed point number; format xxx.yy
constexpr uint16_t VP_EPos = 0x110A;  // 4 Byte Fixed point number; format xxx.yy
constexpr uint16_t VP_PrintProgress_Percentage = 0x110C; // 2 Byte Integer (0..100)
constexpr uint16_t VP_PrintTime = 0x1110;
constexpr uint16_t VP_PrintTime_LEN = 10;
constexpr uint16_t VP_SD_ResumePauseAbort = 0x1100; // Resume(Data=0), Pause(Data=1), Abort(Data=2) SD Card prints
constexpr uint16_t VP_RK_print_continue=0x1109;
constexpr uint16_t VP_RK_print_pause=0x1100;
//constexpr uint16_t VP_RK_print_cancel=0x1100;
constexpr uint16_t VP_RK_PowerLow=0x1101;
constexpr uint16_t VP_RK_Fastprint=0x1103;
constexpr uint16_t Flianment_print_pause=0x1105;



constexpr uint16_t VP_RK_add_rate=0x1120;
constexpr uint16_t VP_RK_dec_rate=0x1121;
constexpr uint16_t VP_real_rate=0x1102;
constexpr uint16_t VP_SD_Print_LiveAdjustZ_up = 0x1122; //
constexpr uint16_t VP_SD_Print_LiveAdjustZ_down = 0x1123; // 

constexpr uint16_t VP_SD_Print_drybox = 0x1125; // 

//UTILITES UI
constexpr uint16_t VP_RK_Temp=0x2100;
constexpr uint16_t VP_RK_Axis=0x2200;
constexpr uint16_t VP_RK_DryBox=0x2300;
constexpr uint16_t VP_RK_Filament=0x2400;
constexpr uint16_t VP_RK_CN_Filament=VP_RK_Filament+0x3000;
constexpr uint16_t VP_RK_Leveling=0x2500;
constexpr uint16_t VP_RK_Disableaxis=0x2600;
constexpr uint16_t VP_RK_Language=0x2700;
constexpr uint16_t VP_RK_reset=0x2800;


//UTILITES-->Reset UI
////constexpr uint16_t VP_RK_reset=0x2800;

//UTILITES-->TEMP UI
constexpr uint16_t VP_RK_pla_temp=0x2110;
constexpr uint16_t VP_RK_abs_temp=0x2120;
constexpr uint16_t VP_RK_cooling_head=0x2130;
constexpr uint16_t VP_RK_cooling_bed=0x2140;
constexpr uint16_t VP_RK_down_temp_head=0x2150;
constexpr uint16_t VP_RK_down_temp_bed=0x2160;
constexpr uint16_t VP_RK_up_temp_head=0x2170;
constexpr uint16_t VP_RK_up_temp_bed=0x2180;
constexpr uint16_t Key_up_temp_head=0x2190;
constexpr uint16_t Key_up_temp_bed=0x2192;

constexpr uint16_t Key_up_printrate=0x2194;


//move x,y,z display

constexpr uint16_t Keyboard_x_input=0x2198;
constexpr uint16_t Keyboard_y_input=0x219A;
constexpr uint16_t Keyboard_z_input=0x219C;

// jinliao  tuiliao
constexpr uint16_t Keyboard_jinliao_temp_input  =0x21A0;
constexpr uint16_t Keyboard_jinliao_length_input=0x21A2;


//44  cool down
constexpr uint16_t Keyboard_cooldown_head_input  =0x21A4;
constexpr uint16_t Keyboard_cooldown_bed_input   =0x21A6;

//check Filament
constexpr uint16_t Keyboard_Filament_head_input   =0x21A8;


//UTILITES-->AXIS UI
constexpr uint16_t VP_RK_01_step=0x2210;
constexpr uint16_t VP_RK_1_step=0x2220;
constexpr uint16_t VP_RK_10_step=0x2230;
constexpr uint16_t VP_RK_home_all=0x2240;
constexpr uint16_t VP_RK_move_x_r=0x2250;
constexpr uint16_t VP_RK_move_x_p=0x2260;
constexpr uint16_t VP_RK_move_z_p=0x2270;
constexpr uint16_t VP_RK_move_z_r=0x2280;
constexpr uint16_t VP_RK_move_y_p=0x2290;
constexpr uint16_t VP_RK_move_y_r=0x22A0;
constexpr uint16_t VP_RK_home_x=0x22B0;
constexpr uint16_t VP_RK_home_y=0x22C0;
constexpr uint16_t VP_RK_home_z=0x22D0;
constexpr uint16_t keyboard_RK_home_x=0x22E0;
constexpr uint16_t keyboard_RK_home_y=0x22E6;
constexpr uint16_t keyboard_RK_home_z=0x22EC;




//UTILITES-->DRYBOX UI
constexpr uint16_t VP_Cur_Temp=0x2301;
constexpr uint16_t VP_Cur_humidity=0x2303;
constexpr uint16_t VP_Targe_Temp=0x2305;
constexpr uint16_t VP_Dry_Time=0x2310;
constexpr uint16_t VP_Add_Targe_Temp=0x2307;
constexpr uint16_t VP_Dec_Targe_Temp=0x2308;
constexpr uint16_t VP_Add_Dry_Time=0x2309;
constexpr uint16_t VP_Dec_Dry_Time=0x230A;
constexpr uint16_t VP_DRYBOX_CANCEL=0x230B;
constexpr uint16_t VP_DRYBOX_apply=0x230C;



//UTILITES-->FILEMENT UI
constexpr uint16_t VP_RK_filament_pla=0x2410;
constexpr uint16_t VP_RK_filament_abs=0x2420;
constexpr uint16_t VP_RK_load_filament=0x2430;
constexpr uint16_t VP_RK_unload_filament=0x2440;
constexpr uint16_t VP_NUM_filament_len=0x2450;
constexpr uint16_t VP_NUM_Temp=0x2460;
constexpr uint16_t VP_RK_add_filament_len=0x245A;
constexpr uint16_t VP_RK_dec_filament_len=0x245B;







//UTILITES-->LEVEL UI
constexpr uint16_t VP_RK_Aux_Level=0x2503;
constexpr uint16_t VP_RK_Measure_Level=0x2504;
constexpr uint16_t VP_RK_Auto_Level_switch=0x2505;
constexpr uint16_t VP_Num_Point_1=0x2506;
constexpr uint16_t VP_Num_Point_2=0x2508;
constexpr uint16_t VP_Num_Point_3=0x250a;
constexpr uint16_t VP_Num_Point_4=0x250c;
constexpr uint16_t VP_Num_Point_5=0x250e;
constexpr uint16_t VP_Num_Point_6=0x2510;
constexpr uint16_t VP_Num_Point_7=0x2512;
constexpr uint16_t VP_Num_Point_8=0x2514;
constexpr uint16_t VP_Num_Point_9=0x2516;
constexpr uint16_t VP_Num_Point_10=0x2518;
constexpr uint16_t VP_Num_Point_11=0x251a;
constexpr uint16_t VP_Num_Point_12=0x251c;
constexpr uint16_t VP_Num_Point_13=0x251e;
constexpr uint16_t VP_Num_Point_14=0x2520;
constexpr uint16_t VP_Num_Point_15=0x2522;
constexpr uint16_t VP_Num_Point_16=0x2524;

//UTILITES-->disableaxis UI
constexpr uint16_t VP_RK_disableaxis=0x2600;



//UTILITES-->language UI
constexpr uint16_t VP_RK_language=0x2700;



//POWER LOSS SAVE UI
constexpr uint16_t VP_RK_POWER_LOSS_RECOVERY=0x2900;


//device info
constexpr uint16_t VP_device_info=0xf090+3;

//print info
constexpr uint16_t VP_printfinfo_info=0xf0B0+3;


//VP_M108
constexpr uint16_t VP_M108=0xFEEE;



constexpr uint16_t VP_M117 = 0xE000;
constexpr uint8_t VP_M117_LEN = 0x20;




// Display Memory layout used (T5UID)
// Except system variables this is arbitrary, just to organize stuff....

// 0x0000 .. 0x0FFF  -- System variables and reserved by the display
// 0x1000 .. 0x1FFF  -- Variables to never change location, regardless of UI Version
// 0x2000 .. 0x2FFF  -- Controls (VPs that will trigger some action)
// 0x3000 .. 0x4FFF  -- Marlin Data to be displayed
// 0x5000 ..         -- SPs (if we want to modify display elements, e.g change color or like) -- currently unused

// As there is plenty of space (at least most displays have >8k RAM), we do not pack them too tight,
// so that we can keep variables nicely together in the address space.
// Storage space for the Killscreen messages. 0x1100 - 0x1200 . Reused for the popup.
constexpr uint16_t VP_MSGSTR1 = 0xf010+3;
constexpr uint8_t VP_MSGSTR1_LEN = 0x20;  // might be more place for it...
constexpr uint16_t VP_MSGSTR2 = 0xf030+3;
constexpr uint8_t VP_MSGSTR2_LEN = 0x20;
constexpr uint16_t VP_MSGSTR3 = 0xf050+3;
constexpr uint8_t VP_MSGSTR3_LEN = 0x20;
constexpr uint16_t VP_MSGSTR4 = 0xf070+3;
constexpr uint8_t VP_MSGSTR4_LEN = 0x20;

// Buttons on the SD-Card File listing.

#if 0
constexpr uint16_t VP_SD_ScrollEvent = 0x2020; // Data: 0 for "up a directory", numbers are the amount to scroll, e.g -1 one up, 1 one down
constexpr uint16_t VP_SD_FileSelected = 0x2022; // Number of file field selected.
constexpr uint16_t VP_SD_FileSelectConfirm = 0x2024; // (This is a virtual VP and emulated by the Confirm Screen when a file has been confirmed)
#else
constexpr uint16_t VP_SD_ScrollEvent = 0x1009; // Data: 0 for "up a directory", numbers are the amount to scroll, e.g -1 one up, 1 one down
constexpr uint16_t VP_SD_FileSelected = 0x1005; // Number of file field selected.
constexpr uint16_t VP_SD_FileSelectConfirm = 0x1006; // (This is a virtual VP and emulated by the Confirm Screen when a file has been confirmed)
constexpr uint16_t VP_SD_FilePrint_AutoLeve = 0x1007; // 
constexpr uint16_t VP_SD_FilePrint_FilamentRunout = 0x1008; // 
constexpr uint16_t VP_SD_FilePrint_Filament_Jams = 0x100a; // 
//constexpr uint16_t VP_SD_AbortPrintConfirmed = 0x1101; // Abort print confirmation (virtual, will be injected by the confirm dialog)
constexpr uint16_t VP_SD_FileName_LEN = 32; // LEN is shared for all entries.
constexpr uint16_t DGUS_SD_FILESPERSCREEN = 4; // FIXME move that info to the display and read it from there.
#endif

