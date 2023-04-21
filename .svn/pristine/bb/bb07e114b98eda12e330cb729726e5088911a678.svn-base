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

// R25 = 100 kOhm, beta25 = 4092 K, 4.7 kOhm pull-up, bed thermistor
const temp_entry_t temptable_1[] PROGMEM = {
  { OV(  23), 300 },
  { OV(  25), 295 },
  { OV(  27), 290 },
  { OV(  28), 285 },
  { OV(  31), 280 },
  { OV(  33), 275 },
  { OV(  35), 270 },
  { OV(  38), 265 },
  { OV(  41), 260 },
  { OV(  44), 255 },
  { OV(  48), 250 },
  { OV(  52), 245 },
  { OV(  56), 240 },
  { OV(  61), 235 },
  { OV(  66), 230 },
  { OV(  71), 225 },
  { OV(  78), 220 },
  { OV(  84), 215 },
  { OV(  92), 210 },
  { OV( 100), 205 },
  { OV( 109), 200 },
  { OV( 120), 195 },
  { OV( 131), 190 },
  { OV( 143), 185 },
  { OV( 156), 180 },
  { OV( 171), 175 },
  { OV( 187), 170 },
  { OV( 205), 165 },
  { OV( 224), 160 },
  { OV( 245), 155 },
  { OV( 268), 150 },
  { OV( 293), 145 },
  { OV( 320), 140 },
  { OV( 348), 135 },
  { OV( 379), 130 },
  { OV( 411), 125 },
  { OV( 445), 120 },
  { OV( 480), 115 },
  { OV( 516), 110 },
  { OV( 553), 105 },
  { OV( 591), 100 },
  { OV( 628),  95 },
  { OV( 665),  90 },
  { OV( 702),  85 },
  { OV( 737),  80 },
  { OV( 770),  75 },
  { OV( 801),  70 },
  { OV( 830),  65 },
  { OV( 857),  60 },
  { OV( 881),  55 },
  { OV( 903),  50 },
  { OV( 922),  45 },
  { OV( 939),  40 },
  { OV( 954),  35 },
  { OV( 966),  30 },
  { OV( 977),  25 },
  { OV( 985),  20 },
  { OV( 993),  15 },
  { OV( 999),  10 },
  { OV(1004),   5 },
  { OV(1008),   0 },
  { OV(1012),  -5 },
  { OV(1016), -10 },
  { OV(1020), -15 }
};
#if 0
const uint16_t temptable_ph[] PROGMEM = {//25℃环境下 湿度20%RH~95%RH的阻抗表
	196,218,243,270,300,332,368,408,451,498,550,606,666,731,802,877,957,1042,1131,1226, 
	1326,1427,1534,1645,1758,1853,1950,2048,2141,2238,2334,2429,2522,2612,2702,2773,2844,2913,2979,3043, 
	3103,3163,3218,3272,3322,3374,3425,3471,3513,3556,3593,3628,3664,3693,3724,3747,3768,3788,3807,3826, 
	3842,3858,3873,3888,3901,3912,3923,3932,3942,3951,3959,3967,3974,3982,3988,3995, 
};
#else
const uint16_t temptable_ph[] PROGMEM = {//25℃环境下 湿度20%RH~95%RH的阻抗表
	49,55,61,67,75,83,92,102,113,128,137,152,167,183,200,219,239,261,283,307, 
	331,357,384,411,439,463,488,512,535,560,583,607,631,653,675,693,711,728,745,761, 
	776,791,804,818,830,843,856,868,878,889,898,907,916,923,931,937,942,947,952,956, 
	961,965,968,972,975,978,981,983,985,988,990,992,994,995,997,999, 
};



#endif
