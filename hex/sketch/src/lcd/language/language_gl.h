#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/lcd/language/language_gl.h"
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

/**
 * Galician language (ISO "gl")
 *
 * LCD Menu Messages
 * See also https://marlinfw.org/docs/development/lcd_language.html
 */

#define DISPLAY_CHARSET_ISO10646_1

namespace Language_gl {
  using namespace Language_en; // Inherit undefined strings from English

  constexpr uint8_t    CHARSIZE                            = 1;
  PROGMEM Language_Str LANGUAGE                            = _UxGT("Galician");

  PROGMEM Language_Str WELCOME_MSG                         = MACHINE_NAME _UxGT(" lista.");
  PROGMEM Language_Str MSG_MARLIN                          = _UxGT("Marlin");
  PROGMEM Language_Str MSG_YES                             = _UxGT("SI");
  PROGMEM Language_Str MSG_NO                              = _UxGT("NON");
  PROGMEM Language_Str MSG_BACK                            = _UxGT("Atrás");
  PROGMEM Language_Str MSG_MEDIA_ABORTING                  = _UxGT("Cancelando...");
  PROGMEM Language_Str MSG_MEDIA_INSERTED                  = _UxGT("Tarxeta inserida");
  PROGMEM Language_Str MSG_MEDIA_REMOVED                   = _UxGT("Tarxeta retirada");
  PROGMEM Language_Str MSG_MEDIA_WAITING                   = _UxGT("Agardando ao SD/USB");
  PROGMEM Language_Str MSG_MEDIA_READ_ERROR                = _UxGT("Erro lectura SD/USB");
  PROGMEM Language_Str MSG_MEDIA_USB_REMOVED               = _UxGT("Disp. USB retirado");
  PROGMEM Language_Str MSG_MEDIA_USB_FAILED                = _UxGT("Inicio USB fallido");
  PROGMEM Language_Str MSG_KILL_SUBCALL_OVERFLOW           = _UxGT("Desbord. Subch.");
  PROGMEM Language_Str MSG_LCD_ENDSTOPS                    = _UxGT("FinCarro");
  PROGMEM Language_Str MSG_LCD_SOFT_ENDSTOPS               = _UxGT("FinCarro SW");
  PROGMEM Language_Str MSG_MAIN                            = _UxGT("Menú principal");
  PROGMEM Language_Str MSG_ADVANCED_SETTINGS               = _UxGT("Axustes avanzados");
  PROGMEM Language_Str MSG_CONFIGURATION                   = _UxGT("Configuración");
  PROGMEM Language_Str MSG_RUN_AUTO_FILES                  = _UxGT("Autoarranque");
  PROGMEM Language_Str MSG_DISABLE_STEPPERS                = _UxGT("Apagar motores");
  PROGMEM Language_Str MSG_DEBUG_MENU                      = _UxGT("Menú depuración");
  PROGMEM Language_Str MSG_PROGRESS_BAR_TEST               = _UxGT("Test barra progreso");
  PROGMEM Language_Str MSG_AUTO_HOME                       = _UxGT("Ir a orixe");
  PROGMEM Language_Str MSG_AUTO_HOME_X                     = _UxGT("Ir orixe X");
  PROGMEM Language_Str MSG_AUTO_HOME_Y                     = _UxGT("Ir orixe Y");
  PROGMEM Language_Str MSG_AUTO_HOME_Z                     = _UxGT("Ir orixe Z");
  PROGMEM Language_Str MSG_AUTO_Z_ALIGN                    = _UxGT("Autoaliñar Z");
  PROGMEM Language_Str MSG_LEVEL_BED_HOMING                = _UxGT("Ir orixes XYZ");
  PROGMEM Language_Str MSG_LEVEL_BED_WAITING               = _UxGT("Prema pulsador");
  PROGMEM Language_Str MSG_LEVEL_BED_NEXT_POINT            = _UxGT("Seguinte punto");
  PROGMEM Language_Str MSG_LEVEL_BED_DONE                  = _UxGT("Fin Nivelación!");
  PROGMEM Language_Str MSG_Z_FADE_HEIGHT                   = _UxGT("Compensación Altura");
  PROGMEM Language_Str MSG_SET_HOME_OFFSETS                = _UxGT("Axustar Desfases");
  PROGMEM Language_Str MSG_HOME_OFFSETS_APPLIED            = _UxGT("Desfases aplicados");
  PROGMEM Language_Str MSG_SET_ORIGIN                      = _UxGT("Fixar orixe");
  #if PREHEAT_COUNT
    PROGMEM Language_Str MSG_PREHEAT_1                     = _UxGT("Prequentar ") PREHEAT_1_LABEL;
    PROGMEM Language_Str MSG_PREHEAT_1_H                   = _UxGT("Prequentar ") PREHEAT_1_LABEL " ~";
    PROGMEM Language_Str MSG_PREHEAT_1_END                 = _UxGT("Preque. ") PREHEAT_1_LABEL _UxGT(" Bico");
    PROGMEM Language_Str MSG_PREHEAT_1_END_E               = _UxGT("Preque. ") PREHEAT_1_LABEL _UxGT(" Bico ~");
    PROGMEM Language_Str MSG_PREHEAT_1_ALL                 = _UxGT("Preque. ") PREHEAT_1_LABEL _UxGT(" Todo");
    PROGMEM Language_Str MSG_PREHEAT_1_BEDONLY             = _UxGT("Preque. ") PREHEAT_1_LABEL _UxGT(" Cama");
    PROGMEM Language_Str MSG_PREHEAT_1_SETTINGS            = _UxGT("Preque. ") PREHEAT_1_LABEL _UxGT(" conf");

    PROGMEM Language_Str MSG_PREHEAT_M                     = _UxGT("Prequentar $");
    PROGMEM Language_Str MSG_PREHEAT_M_H                   = _UxGT("Prequentar $ ~");
    PROGMEM Language_Str MSG_PREHEAT_M_END                 = _UxGT("Preque. $ Bico");
    PROGMEM Language_Str MSG_PREHEAT_M_END_E               = _UxGT("Preque. $ Bico ~");
    PROGMEM Language_Str MSG_PREHEAT_M_ALL                 = _UxGT("Preque. $ Todo");
    PROGMEM Language_Str MSG_PREHEAT_M_BEDONLY             = _UxGT("Preque. $ Cama");
    PROGMEM Language_Str MSG_PREHEAT_M_SETTINGS            = _UxGT("Preque. $ conf");
  #endif
  PROGMEM Language_Str MSG_PREHEAT_CUSTOM                  = _UxGT("Preque. Personali.");
  PROGMEM Language_Str MSG_COOLDOWN                        = _UxGT("Arrefriar");
  PROGMEM Language_Str MSG_CUTTER_FREQUENCY                = _UxGT("Frecuencia");
  PROGMEM Language_Str MSG_LASER_MENU                      = _UxGT("Control Láser");
  PROGMEM Language_Str MSG_LASER_POWER                     = _UxGT("Potencia Láser");
  PROGMEM Language_Str MSG_SPINDLE_MENU                    = _UxGT("Control Fuso");
  PROGMEM Language_Str MSG_SPINDLE_POWER                   = _UxGT("Potencia Fuso");
  PROGMEM Language_Str MSG_SPINDLE_REVERSE                 = _UxGT("Inverter xiro");
  PROGMEM Language_Str MSG_SWITCH_PS_ON                    = _UxGT("Acender");
  PROGMEM Language_Str MSG_SWITCH_PS_OFF                   = _UxGT("Apagar");
  PROGMEM Language_Str MSG_EXTRUDE                         = _UxGT("Extruír");
  PROGMEM Language_Str MSG_RETRACT                         = _UxGT("Retraer");
  PROGMEM Language_Str MSG_MOVE_AXIS                       = _UxGT("Mover eixe");
  PROGMEM Language_Str MSG_BED_LEVELING                    = _UxGT("Nivelando Cama");
  PROGMEM Language_Str MSG_LEVEL_BED                       = _UxGT("Nivelar Cama");
  PROGMEM Language_Str MSG_LEVEL_CORNERS                   = _UxGT("Nivelar Cantos");
  PROGMEM Language_Str MSG_NEXT_CORNER                     = _UxGT("Seguinte Canto");
  PROGMEM Language_Str MSG_MESH_EDITOR                     = _UxGT("Editor Mallado");
  PROGMEM Language_Str MSG_EDIT_MESH                       = _UxGT("Editar Mallado");
  PROGMEM Language_Str MSG_EDITING_STOPPED                 = _UxGT("Ed. Mallado Detida");
  PROGMEM Language_Str MSG_PROBING_MESH                    = _UxGT("Punto de Proba");
  PROGMEM Language_Str MSG_MESH_X                          = _UxGT("Índice X");
  PROGMEM Language_Str MSG_MESH_Y                          = _UxGT("Índice Y");
  PROGMEM Language_Str MSG_MESH_EDIT_Z                     = _UxGT("Valor Z");
  PROGMEM Language_Str MSG_CUSTOM_COMMANDS                 = _UxGT("Comandos Personaliz.");
  PROGMEM Language_Str MSG_M48_TEST                        = _UxGT("M48 Probar Sonda");
  PROGMEM Language_Str MSG_M48_POINT                       = _UxGT("M48 Punto");
  PROGMEM Language_Str MSG_M48_DEVIATION                   = _UxGT("Desviación");
  PROGMEM Language_Str MSG_IDEX_MENU                       = _UxGT("Modo IDEX");
  PROGMEM Language_Str MSG_OFFSETS_MENU                    = _UxGT("Ferramentas Compens");
  PROGMEM Language_Str MSG_IDEX_MODE_AUTOPARK              = _UxGT("Auto-Estacionar");
  PROGMEM Language_Str MSG_IDEX_MODE_DUPLICATE             = _UxGT("Duplicación");
  PROGMEM Language_Str MSG_IDEX_MODE_MIRRORED_COPY         = _UxGT("Copia Espello");
  PROGMEM Language_Str MSG_IDEX_MODE_FULL_CTRL             = _UxGT("Control Total");
  PROGMEM Language_Str MSG_HOTEND_OFFSET_X                 = _UxGT("2º Bico X");
  PROGMEM Language_Str MSG_HOTEND_OFFSET_Y                 = _UxGT("2º Bico Y");
  PROGMEM Language_Str MSG_HOTEND_OFFSET_Z                 = _UxGT("2º Bico Z");
  PROGMEM Language_Str MSG_UBL_DOING_G29                   = _UxGT("Executando G29");
  PROGMEM Language_Str MSG_UBL_TOOLS                       = _UxGT("Ferramentas UBL");
  PROGMEM Language_Str MSG_UBL_LEVEL_BED                   = _UxGT("Unified Bed Leveling");
  PROGMEM Language_Str MSG_LCD_TILTING_MESH                = _UxGT("Punto de inclinación");
  PROGMEM Language_Str MSG_UBL_MANUAL_MESH                 = _UxGT("Facer Malla Manual");
  PROGMEM Language_Str MSG_UBL_BC_INSERT                   = _UxGT("Colocar Calzo e Medir");
  PROGMEM Language_Str MSG_UBL_BC_INSERT2                  = _UxGT("Medir");
  PROGMEM Language_Str MSG_UBL_BC_REMOVE                   = _UxGT("Quitar e Medir Cama");
  PROGMEM Language_Str MSG_UBL_MOVING_TO_NEXT              = _UxGT("Mover ao Seguinte");
  PROGMEM Language_Str MSG_UBL_ACTIVATE_MESH               = _UxGT("Activar UBL");
  PROGMEM Language_Str MSG_UBL_DEACTIVATE_MESH             = _UxGT("Desactivar UBL");
  PROGMEM Language_Str MSG_UBL_SET_TEMP_BED                = _UxGT("Temp Cama");
  PROGMEM Language_Str MSG_UBL_BED_TEMP_CUSTOM             = _UxGT("Temp Cama");
  PROGMEM Language_Str MSG_UBL_SET_TEMP_HOTEND             = _UxGT("Temp Bico");
  PROGMEM Language_Str MSG_UBL_HOTEND_TEMP_CUSTOM          = _UxGT("Temp Bico");
  PROGMEM Language_Str MSG_UBL_MESH_EDIT                   = _UxGT("Editar Malla");
  PROGMEM Language_Str MSG_UBL_EDIT_CUSTOM_MESH            = _UxGT("Edit. Malla Person.");
  PROGMEM Language_Str MSG_UBL_FINE_TUNE_MESH              = _UxGT("Axuste Fino da Malla");
  PROGMEM Language_Str MSG_UBL_DONE_EDITING_MESH           = _UxGT("Fin Edición da Malla");
  PROGMEM Language_Str MSG_UBL_BUILD_CUSTOM_MESH           = _UxGT("Crear Malla Person.");
  PROGMEM Language_Str MSG_UBL_BUILD_MESH_MENU             = _UxGT("Crear Malla");
  #if PREHEAT_COUNT
    PROGMEM Language_Str MSG_UBL_BUILD_MESH_M              = _UxGT("Crear Malla ($)");
    PROGMEM Language_Str MSG_UBL_VALIDATE_MESH_M           = _UxGT("Validar Malla ($)");
  #endif
  PROGMEM Language_Str MSG_UBL_BUILD_COLD_MESH             = _UxGT("Crear Malla Fría");
  PROGMEM Language_Str MSG_UBL_MESH_HEIGHT_ADJUST          = _UxGT("Axustar Altura Malla");
  PROGMEM Language_Str MSG_UBL_MESH_HEIGHT_AMOUNT          = _UxGT("Altura");
  PROGMEM Language_Str MSG_UBL_VALIDATE_MESH_MENU          = _UxGT("Validar Malla");
  PROGMEM Language_Str MSG_UBL_VALIDATE_CUSTOM_MESH        = _UxGT("Validar Malla perso.");
  PROGMEM Language_Str MSG_G26_HEATING_BED                 = _UxGT("G26 Quentando Cama");
  PROGMEM Language_Str MSG_G26_HEATING_NOZZLE              = _UxGT("G26 Quentando Bico");
  PROGMEM Language_Str MSG_G26_MANUAL_PRIME                = _UxGT("Traballo manual...");
  PROGMEM Language_Str MSG_G26_FIXED_LENGTH                = _UxGT("Traballo Lonxit Fixa");
  PROGMEM Language_Str MSG_G26_PRIME_DONE                  = _UxGT("Fin Traballo");
  PROGMEM Language_Str MSG_G26_CANCELED                    = _UxGT("G26 Cancelado");
  PROGMEM Language_Str MSG_G26_LEAVING                     = _UxGT("Saíndo de G26");
  PROGMEM Language_Str MSG_UBL_CONTINUE_MESH               = _UxGT("Continuar Malla");
  PROGMEM Language_Str MSG_UBL_MESH_LEVELING               = _UxGT("Nivelación Malla");
  PROGMEM Language_Str MSG_UBL_3POINT_MESH_LEVELING        = _UxGT("Nivelación 3Puntos");
  PROGMEM Language_Str MSG_UBL_GRID_MESH_LEVELING          = _UxGT("Nivelación Grid");
  PROGMEM Language_Str MSG_UBL_MESH_LEVEL                  = _UxGT("Nivelar Malla");
  PROGMEM Language_Str MSG_UBL_SIDE_POINTS                 = _UxGT("Puntos Laterais");
  PROGMEM Language_Str MSG_UBL_MAP_TYPE                    = _UxGT("Tipo de Mapa ");
  PROGMEM Language_Str MSG_UBL_OUTPUT_MAP                  = _UxGT("Gardar Mapa");
  PROGMEM Language_Str MSG_UBL_OUTPUT_MAP_HOST             = _UxGT("Enviar ao Host");
  PROGMEM Language_Str MSG_UBL_OUTPUT_MAP_CSV              = _UxGT("Gardar en CSV");
  PROGMEM Language_Str MSG_UBL_OUTPUT_MAP_BACKUP           = _UxGT("Backup Externo");
  PROGMEM Language_Str MSG_UBL_INFO_UBL                    = _UxGT("Info do UBL");
  PROGMEM Language_Str MSG_UBL_FILLIN_AMOUNT               = _UxGT("Cantidade de Recheo");
  PROGMEM Language_Str MSG_UBL_MANUAL_FILLIN               = _UxGT("Recheo Manual");
  PROGMEM Language_Str MSG_UBL_SMART_FILLIN                = _UxGT("Recheo Intelixente");
  PROGMEM Language_Str MSG_UBL_FILLIN_MESH                 = _UxGT("Recheo da Malla");
  PROGMEM Language_Str MSG_UBL_INVALIDATE_ALL              = _UxGT("Invalidar todo");
  PROGMEM Language_Str MSG_UBL_INVALIDATE_CLOSEST          = _UxGT("Invalidar cercanos");
  PROGMEM Language_Str MSG_UBL_FINE_TUNE_ALL               = _UxGT("Axustar Fino Todo");
  PROGMEM Language_Str MSG_UBL_FINE_TUNE_CLOSEST           = _UxGT("Axustar Fino Cerc");
  PROGMEM Language_Str MSG_UBL_STORAGE_MESH_MENU           = _UxGT("Almacenamento Malla");
  PROGMEM Language_Str MSG_UBL_STORAGE_SLOT                = _UxGT("Rañura Memoria");
  PROGMEM Language_Str MSG_UBL_LOAD_MESH                   = _UxGT("Cargar Malla Cama");
  PROGMEM Language_Str MSG_UBL_SAVE_MESH                   = _UxGT("Gardar Malla Cama");
  PROGMEM Language_Str MSG_MESH_LOADED                     = _UxGT("Malla %i Cargada");
  PROGMEM Language_Str MSG_MESH_SAVED                      = _UxGT("Malla %i Gardada");
  PROGMEM Language_Str MSG_UBL_NO_STORAGE                  = _UxGT("Sen Gardar");
  PROGMEM Language_Str MSG_UBL_SAVE_ERROR                  = _UxGT("Erro: Gardadado UBL");
  PROGMEM Language_Str MSG_UBL_RESTORE_ERROR               = _UxGT("Erro: Recuperación UBL");
  PROGMEM Language_Str MSG_UBL_Z_OFFSET                    = _UxGT("Desfase de Z: ");
  PROGMEM Language_Str MSG_UBL_Z_OFFSET_STOPPED            = _UxGT("Desfase de Z Detido");
  PROGMEM Language_Str MSG_UBL_STEP_BY_STEP_MENU           = _UxGT("UBL Paso a Paso");
  PROGMEM Language_Str MSG_UBL_1_BUILD_COLD_MESH           = _UxGT("1. Crear Malla Fría");
  PROGMEM Language_Str MSG_UBL_2_SMART_FILLIN              = _UxGT("2. Recheo Intelixente");
  PROGMEM Language_Str MSG_UBL_3_VALIDATE_MESH_MENU        = _UxGT("3. Validar Malla");
  PROGMEM Language_Str MSG_UBL_4_FINE_TUNE_ALL             = _UxGT("4. Axustar Fino Todo");
  PROGMEM Language_Str MSG_UBL_5_VALIDATE_MESH_MENU        = _UxGT("5. Validar Malla");
  PROGMEM Language_Str MSG_UBL_6_FINE_TUNE_ALL             = _UxGT("6. Axustar Fino Todo");
  PROGMEM Language_Str MSG_UBL_7_SAVE_MESH                 = _UxGT("7. Gardar Malla Cama");

  PROGMEM Language_Str MSG_LED_CONTROL                     = _UxGT("Control LED");
  PROGMEM Language_Str MSG_LEDS                            = _UxGT("Luces");
  PROGMEM Language_Str MSG_LED_PRESETS                     = _UxGT("Axustes Luz");
  PROGMEM Language_Str MSG_SET_LEDS_RED                    = _UxGT("Vermello");
  PROGMEM Language_Str MSG_SET_LEDS_ORANGE                 = _UxGT("Laranxa");
  PROGMEM Language_Str MSG_SET_LEDS_YELLOW                 = _UxGT("Amarelo");
  PROGMEM Language_Str MSG_SET_LEDS_GREEN                  = _UxGT("Verde");
  PROGMEM Language_Str MSG_SET_LEDS_BLUE                   = _UxGT("Azul");
  PROGMEM Language_Str MSG_SET_LEDS_INDIGO                 = _UxGT("Índigo");
  PROGMEM Language_Str MSG_SET_LEDS_VIOLET                 = _UxGT("Violeta");
  PROGMEM Language_Str MSG_SET_LEDS_WHITE                  = _UxGT("Branco");
  PROGMEM Language_Str MSG_SET_LEDS_DEFAULT                = _UxGT("Por defecto");
  PROGMEM Language_Str MSG_CUSTOM_LEDS                     = _UxGT("Luces personalizadas");
  PROGMEM Language_Str MSG_INTENSITY_R                     = _UxGT("Intensidade Vermello");
  PROGMEM Language_Str MSG_INTENSITY_G                     = _UxGT("Intensidade Verde");
  PROGMEM Language_Str MSG_INTENSITY_B                     = _UxGT("Intensidade Azul");
  PROGMEM Language_Str MSG_INTENSITY_W                     = _UxGT("Intensidade Branco");
  PROGMEM Language_Str MSG_LED_BRIGHTNESS                  = _UxGT("Brillo");

  PROGMEM Language_Str MSG_MOVING                          = _UxGT("Movendo...");
  PROGMEM Language_Str MSG_FREE_XY                         = _UxGT("Libre XY");
  PROGMEM Language_Str MSG_MOVE_X                          = _UxGT("Mover X");
  PROGMEM Language_Str MSG_MOVE_Y                          = _UxGT("Mover Y");
  PROGMEM Language_Str MSG_MOVE_Z                          = _UxGT("Mover Z");
  PROGMEM Language_Str MSG_MOVE_E                          = _UxGT("Extrusor");
  PROGMEM Language_Str MSG_MOVE_EN                         = _UxGT("Extrusor *");
  PROGMEM Language_Str MSG_HOTEND_TOO_COLD                 = _UxGT("Bico moi frío");
  PROGMEM Language_Str MSG_MOVE_N_MM                       = _UxGT("Mover %smm");
  PROGMEM Language_Str MSG_MOVE_01MM                       = _UxGT("Mover 0.1mm");
  PROGMEM Language_Str MSG_MOVE_1MM                        = _UxGT("Mover 1mm");
  PROGMEM Language_Str MSG_MOVE_10MM                       = _UxGT("Mover 10mm");
  PROGMEM Language_Str MSG_SPEED                           = _UxGT("Velocidade");
  PROGMEM Language_Str MSG_BED_Z                           = _UxGT("Cama Z");
  PROGMEM Language_Str MSG_NOZZLE                          = _UxGT("Bico");
  PROGMEM Language_Str MSG_NOZZLE_N                        = _UxGT("Bico ~");
  PROGMEM Language_Str MSG_NOZZLE_PARKED                   = _UxGT("Bico Estacionado");
  PROGMEM Language_Str MSG_NOZZLE_STANDBY                  = _UxGT("Bico Standby");
  PROGMEM Language_Str MSG_BED                             = _UxGT("Cama");
  PROGMEM Language_Str MSG_CHAMBER                         = _UxGT("Cámara");
  PROGMEM Language_Str MSG_FAN_SPEED                       = _UxGT("Vel. Ventilador");
  PROGMEM Language_Str MSG_FAN_SPEED_N                     = _UxGT("Vel. Ventilador ~");
  PROGMEM Language_Str MSG_STORED_FAN_N                    = _UxGT("Ventilador Mem. ~");
  PROGMEM Language_Str MSG_EXTRA_FAN_SPEED                 = _UxGT("Vel. Vent. Extra");
  PROGMEM Language_Str MSG_EXTRA_FAN_SPEED_N               = _UxGT("Vel. Vent. Extra ~");
  PROGMEM Language_Str MSG_CONTROLLER_FAN                  = _UxGT("Controlador Vent.");
  PROGMEM Language_Str MSG_CONTROLLER_FAN_IDLE_SPEED       = _UxGT("Velocidade Repouso");
  PROGMEM Language_Str MSG_CONTROLLER_FAN_AUTO_ON          = _UxGT("Modo Auto");
  PROGMEM Language_Str MSG_CONTROLLER_FAN_SPEED            = _UxGT("Velocidade Activa");
  PROGMEM Language_Str MSG_CONTROLLER_FAN_DURATION         = _UxGT("Tempo Repouso");
  PROGMEM Language_Str MSG_FLOW                            = _UxGT("Fluxo");
  PROGMEM Language_Str MSG_FLOW_N                          = _UxGT("Fluxo ~");
  PROGMEM Language_Str MSG_CONTROL                         = _UxGT("Control");
  PROGMEM Language_Str MSG_MIN                             = " " LCD_STR_THERMOMETER _UxGT(" Min");
  PROGMEM Language_Str MSG_MAX                             = " " LCD_STR_THERMOMETER _UxGT(" Max");
  PROGMEM Language_Str MSG_FACTOR                          = " " LCD_STR_THERMOMETER _UxGT(" Fact");
  PROGMEM Language_Str MSG_AUTOTEMP                        = _UxGT("Temperatura Auto.");
  PROGMEM Language_Str MSG_LCD_ON                          = _UxGT("Acender");
  PROGMEM Language_Str MSG_LCD_OFF                         = _UxGT("Apagar");
  PROGMEM Language_Str MSG_PID_AUTOTUNE                    = _UxGT("Auto-Sint. PID");
  PROGMEM Language_Str MSG_PID_AUTOTUNE_E                  = _UxGT("Auto-Sint. PID *");
  PROGMEM Language_Str MSG_PID_AUTOTUNE_DONE               = _UxGT("Fin Auto-Sint PID");
  PROGMEM Language_Str MSG_PID_BAD_EXTRUDER_NUM            = _UxGT("Auto-Sint. fallida. Extrusor danado.");
  PROGMEM Language_Str MSG_PID_TEMP_TOO_HIGH               = _UxGT("Auto-Sint. fallida. Temperatura moi alta.");
  PROGMEM Language_Str MSG_PID_TIMEOUT                     = _UxGT("Auto-Sint. fallida. Tempo excedido.");
  PROGMEM Language_Str MSG_SELECT                          = _UxGT("Escolla");
  PROGMEM Language_Str MSG_SELECT_E                        = _UxGT("Escolla *");
  PROGMEM Language_Str MSG_ACC                             = _UxGT("Acel");
  PROGMEM Language_Str MSG_JERK                            = _UxGT("Jerk");
  PROGMEM Language_Str MSG_VA_JERK                         = _UxGT("V") LCD_STR_A _UxGT("-Jerk");
  PROGMEM Language_Str MSG_VB_JERK                         = _UxGT("V") LCD_STR_B _UxGT("-Jerk");
  PROGMEM Language_Str MSG_VC_JERK                         = _UxGT("V") LCD_STR_C _UxGT("-Jerk");
  PROGMEM Language_Str MSG_VE_JERK                         = _UxGT("Ve-Jerk");
  PROGMEM Language_Str MSG_JUNCTION_DEVIATION              = _UxGT("Desvío Unión");
  PROGMEM Language_Str MSG_VELOCITY                        = _UxGT("Velocidade");
  PROGMEM Language_Str MSG_VMAX_A                          = _UxGT("Vmax ") LCD_STR_A;
  PROGMEM Language_Str MSG_VMAX_B                          = _UxGT("Vmax ") LCD_STR_B;
  PROGMEM Language_Str MSG_VMAX_C                          = _UxGT("Vmax ") LCD_STR_C;
  PROGMEM Language_Str MSG_VMAX_E                          = _UxGT("Vmax ") LCD_STR_E;
  PROGMEM Language_Str MSG_VMAX_EN                         = _UxGT("Vmax *");
  PROGMEM Language_Str MSG_VMIN                            = _UxGT("Vmin");
  PROGMEM Language_Str MSG_VTRAV_MIN                       = _UxGT("V-viaxe min");
  PROGMEM Language_Str MSG_ACCELERATION                    = _UxGT("Aceleración");
  PROGMEM Language_Str MSG_AMAX_A                          = _UxGT("Amax") LCD_STR_A;
  PROGMEM Language_Str MSG_AMAX_B                          = _UxGT("Amax") LCD_STR_B;
  PROGMEM Language_Str MSG_AMAX_C                          = _UxGT("Amax") LCD_STR_C;
  PROGMEM Language_Str MSG_AMAX_E                          = _UxGT("Amax") LCD_STR_E;
  PROGMEM Language_Str MSG_AMAX_EN                         = _UxGT("Amax *");
  PROGMEM Language_Str MSG_A_RETRACT                       = _UxGT("A-retrac.");
  PROGMEM Language_Str MSG_A_TRAVEL                        = _UxGT("A-viaxe");
  PROGMEM Language_Str MSG_XY_FREQUENCY_LIMIT              = _UxGT("Frecuencia max");
  PROGMEM Language_Str MSG_XY_FREQUENCY_FEEDRATE           = _UxGT("Avance min");
  PROGMEM Language_Str MSG_STEPS_PER_MM                    = _UxGT("Pasos/mm");
  PROGMEM Language_Str MSG_A_STEPS                         = LCD_STR_A _UxGT(" pasos/mm");
  PROGMEM Language_Str MSG_B_STEPS                         = LCD_STR_B _UxGT(" pasos/mm");
  PROGMEM Language_Str MSG_C_STEPS                         = LCD_STR_C _UxGT(" pasos/mm");
  PROGMEM Language_Str MSG_E_STEPS                         = _UxGT("E pasos/mm");
  PROGMEM Language_Str MSG_EN_STEPS                        = _UxGT("* pasos/mm");
  PROGMEM Language_Str MSG_TEMPERATURE                     = _UxGT("Temperatura");
  PROGMEM Language_Str MSG_MOTION                          = _UxGT("Movemento");
  PROGMEM Language_Str MSG_FILAMENT                        = _UxGT("Filamento");
  PROGMEM Language_Str MSG_VOLUMETRIC_ENABLED              = _UxGT("E en mm") SUPERSCRIPT_THREE;
  PROGMEM Language_Str MSG_FILAMENT_DIAM                   = _UxGT("Diam. fil.");
  PROGMEM Language_Str MSG_FILAMENT_DIAM_E                 = _UxGT("Diam. fil. *");
  PROGMEM Language_Str MSG_FILAMENT_UNLOAD                 = _UxGT("Descarga mm");
  PROGMEM Language_Str MSG_FILAMENT_LOAD                   = _UxGT("Carga mm");
  PROGMEM Language_Str MSG_ADVANCE_K                       = _UxGT("Avance K");
  PROGMEM Language_Str MSG_ADVANCE_K_E                     = _UxGT("Avance K *");
  PROGMEM Language_Str MSG_CONTRAST                        = _UxGT("Constraste LCD");
  PROGMEM Language_Str MSG_STORE_EEPROM                    = _UxGT("Gardar Configuración");
  PROGMEM Language_Str MSG_LOAD_EEPROM                     = _UxGT("Cargar Configuración");
  PROGMEM Language_Str MSG_RESTORE_DEFAULTS                = _UxGT("Rest. Defecto");
  PROGMEM Language_Str MSG_INIT_EEPROM                     = _UxGT("Inicializar EEPROM");
  PROGMEM Language_Str MSG_ERR_EEPROM_CRC                  = _UxGT("Erro: CRC EEPROM");
  PROGMEM Language_Str MSG_ERR_EEPROM_INDEX                = _UxGT("Erro: Índice EEPROM");
  PROGMEM Language_Str MSG_ERR_EEPROM_VERSION              = _UxGT("Erro: Versión EEPROM");
  PROGMEM Language_Str MSG_SETTINGS_STORED                 = _UxGT("Config Gardada");
  PROGMEM Language_Str MSG_MEDIA_UPDATE                    = _UxGT("Actualizar SD/USB");
  PROGMEM Language_Str MSG_RESET_PRINTER                   = _UxGT("Reiniciar Impresora");
  PROGMEM Language_Str MSG_REFRESH                         = LCD_STR_REFRESH  _UxGT("Recargar");
  PROGMEM Language_Str MSG_INFO_SCREEN                     = _UxGT("Información");
  PROGMEM Language_Str MSG_PREPARE                         = _UxGT("Preparar");
  PROGMEM Language_Str MSG_TUNE                            = _UxGT("Axustar");
  PROGMEM Language_Str MSG_START_PRINT                     = _UxGT("Comezar impresión");
  PROGMEM Language_Str MSG_BUTTON_NEXT                     = _UxGT("Seguinte");
  PROGMEM Language_Str MSG_BUTTON_INIT                     = _UxGT("Comezar");
  PROGMEM Language_Str MSG_BUTTON_STOP                     = _UxGT("Deter");
  PROGMEM Language_Str MSG_BUTTON_PRINT                    = _UxGT("Imprimir");
  PROGMEM Language_Str MSG_BUTTON_RESET                    = _UxGT("Reiniciar");
  PROGMEM Language_Str MSG_BUTTON_CANCEL                   = _UxGT("Cancelar");
  PROGMEM Language_Str MSG_BUTTON_DONE                     = _UxGT("Listo");
  PROGMEM Language_Str MSG_BUTTON_BACK                     = _UxGT("Atrás");
  PROGMEM Language_Str MSG_BUTTON_PROCEED                  = _UxGT("Proceder");
  PROGMEM Language_Str MSG_PAUSING                         = _UxGT("Pausando...");
  PROGMEM Language_Str MSG_PAUSE_PRINT                     = _UxGT("Pausar impresión");
  PROGMEM Language_Str MSG_RESUME_PRINT                    = _UxGT("Retomar impresión");
  PROGMEM Language_Str MSG_STOP_PRINT                      = _UxGT("Deter impresión");
  PROGMEM Language_Str MSG_PRINTING_OBJECT                 = _UxGT("Imprimindo Obxecto");
  PROGMEM Language_Str MSG_CANCEL_OBJECT                   = _UxGT("Cancelar Obxecto");
  PROGMEM Language_Str MSG_CANCEL_OBJECT_N                 = _UxGT("Cancelar Obxecto =");
  PROGMEM Language_Str MSG_OUTAGE_RECOVERY                 = _UxGT("Recuperar Impresión");
  PROGMEM Language_Str MSG_MEDIA_MENU                      = _UxGT("Tarxeta SD");
  PROGMEM Language_Str MSG_NO_MEDIA                        = _UxGT("Sen tarxeta SD");
  PROGMEM Language_Str MSG_DWELL                           = _UxGT("En repouso...");
  PROGMEM Language_Str MSG_USERWAIT                        = _UxGT("Prema para Retomar..");
  PROGMEM Language_Str MSG_PRINT_PAUSED                    = _UxGT("Impresión Pausada");
  PROGMEM Language_Str MSG_PRINTING                        = _UxGT("Imprimindo...");
  PROGMEM Language_Str MSG_PRINT_ABORTED                   = _UxGT("Impresión Cancelada");
  PROGMEM Language_Str MSG_PRINT_DONE                      = _UxGT("Fin Impresión");
  PROGMEM Language_Str MSG_NO_MOVE                         = _UxGT("Sen movemento.");
  PROGMEM Language_Str MSG_KILLED                          = _UxGT("MORTO.");
  PROGMEM Language_Str MSG_STOPPED                         = _UxGT("DETIDO.");
  PROGMEM Language_Str MSG_CONTROL_RETRACT                 = _UxGT("Retraer mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_SWAP            = _UxGT("Cambio retra. mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACTF                = _UxGT("Retraer V");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_ZHOP            = _UxGT("Alzar Z mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER         = _UxGT("Recup. retra. mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER_SWAP    = _UxGT("Cambio recup. mm");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVERF        = _UxGT("Recuperacion V");
  PROGMEM Language_Str MSG_CONTROL_RETRACT_RECOVER_SWAPF   = _UxGT("S UnRet V");
  PROGMEM Language_Str MSG_AUTORETRACT                     = _UxGT("Auto-Retracción");
  PROGMEM Language_Str MSG_FILAMENT_SWAP_LENGTH            = _UxGT("Lonxitude Retracción");
  PROGMEM Language_Str MSG_FILAMENT_SWAP_EXTRA             = _UxGT("Cambio Extra");
  PROGMEM Language_Str MSG_FILAMENT_PURGE_LENGTH           = _UxGT("Lonxitude de Purga");
  PROGMEM Language_Str MSG_TOOL_CHANGE                     = _UxGT("Cambiar Ferramenta");
  PROGMEM Language_Str MSG_TOOL_CHANGE_ZLIFT               = _UxGT("Levantar Z");
  PROGMEM Language_Str MSG_SINGLENOZZLE_PRIME_SPEED        = _UxGT("Velocidade prim.");
  PROGMEM Language_Str MSG_SINGLENOZZLE_RETRACT_SPEED      = _UxGT("Vel. de Retracción");
  PROGMEM Language_Str MSG_FILAMENT_PARK_ENABLED           = _UxGT("Extrusor Est.");
  PROGMEM Language_Str MSG_SINGLENOZZLE_UNRETRACT_SPEED    = _UxGT("Vel. Recuperación");
  PROGMEM Language_Str MSG_SINGLENOZZLE_FAN_SPEED          = _UxGT("Vel. Ventilador");
  PROGMEM Language_Str MSG_SINGLENOZZLE_FAN_TIME           = _UxGT("Tempo Ventilador");
  PROGMEM Language_Str MSG_TOOL_MIGRATION_ON               = _UxGT("Auto ON");
  PROGMEM Language_Str MSG_TOOL_MIGRATION_OFF              = _UxGT("Auto OFF");
  PROGMEM Language_Str MSG_TOOL_MIGRATION                  = _UxGT("Cambio Ferramenta");
  PROGMEM Language_Str MSG_TOOL_MIGRATION_AUTO             = _UxGT("Cambio Automático");
  PROGMEM Language_Str MSG_TOOL_MIGRATION_END              = _UxGT("Último Extrusor");
  PROGMEM Language_Str MSG_TOOL_MIGRATION_SWAP             = _UxGT("Cambio a *");
  PROGMEM Language_Str MSG_FILAMENTCHANGE                  = _UxGT("Cambiar Filamento");
  PROGMEM Language_Str MSG_FILAMENTCHANGE_E                = _UxGT("Cambiar Filamento *");
  PROGMEM Language_Str MSG_FILAMENTLOAD                    = _UxGT("Cargar Filamento");
  PROGMEM Language_Str MSG_FILAMENTLOAD_E                  = _UxGT("Cargar Filamento *");
  PROGMEM Language_Str MSG_FILAMENTUNLOAD                  = _UxGT("Descargar Filamento");
  PROGMEM Language_Str MSG_FILAMENTUNLOAD_E                = _UxGT("Descargar Filamento *");
  PROGMEM Language_Str MSG_FILAMENTUNLOAD_ALL              = _UxGT("Descargar Todo");
  PROGMEM Language_Str MSG_ATTACH_MEDIA                    = _UxGT("Iniciar SD/USB");
  PROGMEM Language_Str MSG_CHANGE_MEDIA                    = _UxGT("Cambiar SD/USB");
  PROGMEM Language_Str MSG_RELEASE_MEDIA                   = _UxGT("Lanzar SD/USB");
  PROGMEM Language_Str MSG_ZPROBE_OUT                      = _UxGT("Sonda-Z fóra Cama");
  PROGMEM Language_Str MSG_SKEW_FACTOR                     = _UxGT("Factor de Desviación");
  PROGMEM Language_Str MSG_BLTOUCH                         = _UxGT("BLTouch");
  PROGMEM Language_Str MSG_BLTOUCH_SELFTEST                = _UxGT("Auto-Test");
  PROGMEM Language_Str MSG_BLTOUCH_RESET                   = _UxGT("Reiniciar");
  PROGMEM Language_Str MSG_BLTOUCH_STOW                    = _UxGT("Recoller");
  PROGMEM Language_Str MSG_BLTOUCH_DEPLOY                  = _UxGT("Estender");
  PROGMEM Language_Str MSG_BLTOUCH_SW_MODE                 = _UxGT("Modo Software");
  PROGMEM Language_Str MSG_BLTOUCH_5V_MODE                 = _UxGT("Modo 5V");
  PROGMEM Language_Str MSG_BLTOUCH_OD_MODE                 = _UxGT("Modo OD");
  PROGMEM Language_Str MSG_BLTOUCH_MODE_STORE              = _UxGT("Modo Almacenar");
  PROGMEM Language_Str MSG_BLTOUCH_MODE_STORE_5V           = _UxGT("Axustar BLTouch a 5V");
  PROGMEM Language_Str MSG_BLTOUCH_MODE_STORE_OD           = _UxGT("Axustar BLTouch a OD");
  PROGMEM Language_Str MSG_BLTOUCH_MODE_ECHO               = _UxGT("Modo de Informe");
  PROGMEM Language_Str MSG_BLTOUCH_MODE_CHANGE             = _UxGT("PERIGO: Unha mala configuración pode producir daños! Proceder igualmente?");
  PROGMEM Language_Str MSG_TOUCHMI_PROBE                   = _UxGT("TouchMI");
  PROGMEM Language_Str MSG_TOUCHMI_INIT                    = _UxGT("Iniciar TouchMI");
  PROGMEM Language_Str MSG_TOUCHMI_ZTEST                   = _UxGT("Test de Desfase Z");
  PROGMEM Language_Str MSG_TOUCHMI_SAVE                    = _UxGT("Gardar");
  PROGMEM Language_Str MSG_MANUAL_DEPLOY_TOUCHMI           = _UxGT("Estender TouchMI");
  PROGMEM Language_Str MSG_MANUAL_DEPLOY                   = _UxGT("Estender Sonda Z");
  PROGMEM Language_Str MSG_MANUAL_STOW                     = _UxGT("Recoller Sonda Z");
  PROGMEM Language_Str MSG_HOME_FIRST                      = _UxGT("Orixe %s%s%s Primeiro");
  PROGMEM Language_Str MSG_ZPROBE_OFFSETS                  = _UxGT("Desfases Sonda");
  PROGMEM Language_Str MSG_ZPROBE_XOFFSET                  = _UxGT("Desfase Sonda X");
  PROGMEM Language_Str MSG_ZPROBE_YOFFSET                  = _UxGT("Desfase Sonda Y");
  PROGMEM Language_Str MSG_ZPROBE_ZOFFSET                  = _UxGT("Desfase Z");
  PROGMEM Language_Str MSG_BABYSTEP_X                      = _UxGT("Micropaso X");
  PROGMEM Language_Str MSG_BABYSTEP_Y                      = _UxGT("Micropaso Y");
  PROGMEM Language_Str MSG_BABYSTEP_Z                      = _UxGT("Micropaso Z");
  PROGMEM Language_Str MSG_BABYSTEP_TOTAL                  = _UxGT("Total");
  PROGMEM Language_Str MSG_ENDSTOP_ABORT                   = _UxGT("Erro FinCarro");
  PROGMEM Language_Str MSG_HEATING_FAILED_LCD              = _UxGT("Fallo Quentando");
  PROGMEM Language_Str MSG_ERR_REDUNDANT_TEMP              = _UxGT("Erro:Temp Redundante");
  PROGMEM Language_Str MSG_THERMAL_RUNAWAY                 = _UxGT("FUGA TÉRMICA");
  PROGMEM Language_Str MSG_THERMAL_RUNAWAY_BED             = _UxGT("FUGA TÉRMICA CAMA");
  PROGMEM Language_Str MSG_THERMAL_RUNAWAY_CHAMBER         = _UxGT("FUGA TÉRMICA CÁMARA");
  PROGMEM Language_Str MSG_ERR_MAXTEMP                     = _UxGT("Erro:TEMP MÁX");
  PROGMEM Language_Str MSG_ERR_MINTEMP                     = _UxGT("Erro:TEMP MÍN");
  PROGMEM Language_Str MSG_HALTED                          = _UxGT("IMPRESORA DETIDA");
  PROGMEM Language_Str MSG_PLEASE_RESET                    = _UxGT("Debe reiniciar!");
  PROGMEM Language_Str MSG_SHORT_DAY                       = _UxGT("d"); // One character only
  PROGMEM Language_Str MSG_SHORT_HOUR                      = _UxGT("h"); // One character only
  PROGMEM Language_Str MSG_SHORT_MINUTE                    = _UxGT("m"); // One character only
  PROGMEM Language_Str MSG_HEATING                         = _UxGT("Quentando...");
  PROGMEM Language_Str MSG_COOLING                         = _UxGT("Arrefriando...");
  PROGMEM Language_Str MSG_BED_HEATING                     = _UxGT("Quentando cama...");
  PROGMEM Language_Str MSG_BED_COOLING                     = _UxGT("Enfriando Cama...");
  PROGMEM Language_Str MSG_CHAMBER_HEATING                 = _UxGT("Quentando Cámara...");
  PROGMEM Language_Str MSG_CHAMBER_COOLING                 = _UxGT("Arrefriando Cámara...");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE                 = _UxGT("Calibracion Delta");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_X               = _UxGT("Calibrar X");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_Y               = _UxGT("Calibrar Y");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_Z               = _UxGT("Calibrar Z");
  PROGMEM Language_Str MSG_DELTA_CALIBRATE_CENTER          = _UxGT("Calibrar Centro");
  PROGMEM Language_Str MSG_DELTA_SETTINGS                  = _UxGT("Configuración Delta");
  PROGMEM Language_Str MSG_DELTA_AUTO_CALIBRATE            = _UxGT("Auto Calibración");
  PROGMEM Language_Str MSG_DELTA_HEIGHT_CALIBRATE          = _UxGT("Ax. Altura Delta");
  PROGMEM Language_Str MSG_DELTA_Z_OFFSET_CALIBRATE        = _UxGT("Axustar Sonda Z");
  PROGMEM Language_Str MSG_DELTA_DIAG_ROD                  = _UxGT("Barra Diagonal");
  PROGMEM Language_Str MSG_DELTA_HEIGHT                    = _UxGT("Altura");
  PROGMEM Language_Str MSG_DELTA_RADIUS                    = _UxGT("Radio");
  PROGMEM Language_Str MSG_INFO_MENU                       = _UxGT("Acerca de...");
  PROGMEM Language_Str MSG_INFO_PRINTER_MENU               = _UxGT("Información");
  PROGMEM Language_Str MSG_3POINT_LEVELING                 = _UxGT("Nivelación 3puntos");
  PROGMEM Language_Str MSG_LINEAR_LEVELING                 = _UxGT("Nivelación Lineal");
  PROGMEM Language_Str MSG_BILINEAR_LEVELING               = _UxGT("Nivelación Bilineal");
  PROGMEM Language_Str MSG_UBL_LEVELING                    = _UxGT("Nivelación UBL");
  PROGMEM Language_Str MSG_MESH_LEVELING                   = _UxGT("Nivelación en Malla");
  PROGMEM Language_Str MSG_INFO_STATS_MENU                 = _UxGT("Estatísticas");
  PROGMEM Language_Str MSG_INFO_BOARD_MENU                 = _UxGT("Placa nai");
  PROGMEM Language_Str MSG_INFO_THERMISTOR_MENU            = _UxGT("Termistores");
  PROGMEM Language_Str MSG_INFO_EXTRUDERS                  = _UxGT("Extrusores");
  PROGMEM Language_Str MSG_INFO_BAUDRATE                   = _UxGT("Baudios");
  PROGMEM Language_Str MSG_INFO_PROTOCOL                   = _UxGT("Protocolo");
  PROGMEM Language_Str MSG_INFO_RUNAWAY_OFF                = _UxGT("Reloxo Traballo: OFF");
  PROGMEM Language_Str MSG_INFO_RUNAWAY_ON                 = _UxGT("Reloxo Traballo: ON");

  PROGMEM Language_Str MSG_CASE_LIGHT                      = _UxGT("Luz da Caixa");
  PROGMEM Language_Str MSG_CASE_LIGHT_BRIGHTNESS           = _UxGT("Brillo Luces");
  PROGMEM Language_Str MSG_KILL_EXPECTED_PRINTER           = _UxGT("IMPRESORA INCORRECTA");

  #if LCD_WIDTH >= 20
    PROGMEM Language_Str MSG_INFO_PRINT_COUNT              = _UxGT("Total Impresións");
    PROGMEM Language_Str MSG_INFO_COMPLETED_PRINTS         = _UxGT("Completadas");
    PROGMEM Language_Str MSG_INFO_PRINT_TIME               = _UxGT("Tempo Total Imp.");
    PROGMEM Language_Str MSG_INFO_PRINT_LONGEST            = _UxGT("Impresión máis longa");
    PROGMEM Language_Str MSG_INFO_PRINT_FILAMENT           = _UxGT("Total Extruído");
  #else
    PROGMEM Language_Str MSG_INFO_PRINT_COUNT              = _UxGT("Impresións");
    PROGMEM Language_Str MSG_INFO_COMPLETED_PRINTS         = _UxGT("Completadas");
    PROGMEM Language_Str MSG_INFO_PRINT_TIME               = _UxGT("Total");
    PROGMEM Language_Str MSG_INFO_PRINT_LONGEST            = _UxGT("Máis Longa");
    PROGMEM Language_Str MSG_INFO_PRINT_FILAMENT           = _UxGT("Extruido");
  #endif

  PROGMEM Language_Str MSG_INFO_MIN_TEMP                   = _UxGT("Temp Mín");
  PROGMEM Language_Str MSG_INFO_MAX_TEMP                   = _UxGT("Temp Máx");
  PROGMEM Language_Str MSG_INFO_PSU                        = _UxGT("Fonte Alimentación");
  PROGMEM Language_Str MSG_DRIVE_STRENGTH                  = _UxGT("Forza do Motor");
  PROGMEM Language_Str MSG_DAC_PERCENT_X                   = _UxGT("X Driver %");
  PROGMEM Language_Str MSG_DAC_PERCENT_Y                   = _UxGT("Y Driver %");
  PROGMEM Language_Str MSG_DAC_PERCENT_Z                   = _UxGT("Z Driver %");
  PROGMEM Language_Str MSG_DAC_PERCENT_E                   = _UxGT("E Driver %");
  PROGMEM Language_Str MSG_ERROR_TMC                       = _UxGT("ERRO CONEX. TMC");
  PROGMEM Language_Str MSG_DAC_EEPROM_WRITE                = _UxGT("Escribe DAC EEPROM");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEADER          = _UxGT("CAMBIAR FILAMENTO");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEADER_PAUSE    = _UxGT("IMPRESIÓN PAUSADA");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEADER_LOAD     = _UxGT("CARGAR FILAMENTO");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEADER_UNLOAD   = _UxGT("DESCARGAR FILAMENTO");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_OPTION_HEADER   = _UxGT("OPCIÓN DE RETOMAR:");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_OPTION_PURGE    = _UxGT("Purgar máis");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_OPTION_RESUME   = _UxGT("Retomar traballo");
  PROGMEM Language_Str MSG_FILAMENT_CHANGE_NOZZLE          = _UxGT("  Bico: ");
  PROGMEM Language_Str MSG_RUNOUT_SENSOR                   = _UxGT("Sensor Filamento");
  PROGMEM Language_Str MSG_RUNOUT_DISTANCE_MM              = _UxGT("Dist mm Sensor Fil");
  PROGMEM Language_Str MSG_KILL_HOMING_FAILED              = _UxGT("Fallo ao ir á Orixe");
  PROGMEM Language_Str MSG_LCD_PROBING_FAILED              = _UxGT("Fallo ao Sondar");

  PROGMEM Language_Str MSG_MMU2_CHOOSE_FILAMENT_HEADER     = _UxGT("ESCOLLE FILAMENTO");
  PROGMEM Language_Str MSG_MMU2_MENU                       = _UxGT("MMU");
  PROGMEM Language_Str MSG_KILL_MMU2_FIRMWARE              = _UxGT("Actualizar FW MMU!");
  PROGMEM Language_Str MSG_MMU2_NOT_RESPONDING             = _UxGT("MMU Precisa Atención.");
  PROGMEM Language_Str MSG_MMU2_RESUME                     = _UxGT("Retomar impr.");
  PROGMEM Language_Str MSG_MMU2_RESUMING                   = _UxGT("Retomando...");
  PROGMEM Language_Str MSG_MMU2_LOAD_FILAMENT              = _UxGT("Cargar Filamento");
  PROGMEM Language_Str MSG_MMU2_LOAD_ALL                   = _UxGT("Cargar Todo");
  PROGMEM Language_Str MSG_MMU2_LOAD_TO_NOZZLE             = _UxGT("Cargar até bico");
  PROGMEM Language_Str MSG_MMU2_EJECT_FILAMENT             = _UxGT("Expulsar Filamento");
  PROGMEM Language_Str MSG_MMU2_EJECT_FILAMENT_N           = _UxGT("Expulsar Filamento ~");
  PROGMEM Language_Str MSG_MMU2_UNLOAD_FILAMENT            = _UxGT("Descargar Filamento");
  PROGMEM Language_Str MSG_MMU2_LOADING_FILAMENT           = _UxGT("Cargando Fil. %i...");
  PROGMEM Language_Str MSG_MMU2_EJECTING_FILAMENT          = _UxGT("Expulsando Fil. ...");
  PROGMEM Language_Str MSG_MMU2_UNLOADING_FILAMENT         = _UxGT("Descargando Fil...");
  PROGMEM Language_Str MSG_MMU2_ALL                        = _UxGT("Todo");
  PROGMEM Language_Str MSG_MMU2_FILAMENT_N                 = _UxGT("Filamento ~");
  PROGMEM Language_Str MSG_MMU2_RESET                      = _UxGT("Reiniciar MMU");
  PROGMEM Language_Str MSG_MMU2_RESETTING                  = _UxGT("Reiniciando MMU...");
  PROGMEM Language_Str MSG_MMU2_EJECT_RECOVER              = _UxGT("Expulsar, premer");

  PROGMEM Language_Str MSG_MIX                             = _UxGT("Mestura");
  PROGMEM Language_Str MSG_MIX_COMPONENT_N                 = _UxGT("Compoñente =");
  PROGMEM Language_Str MSG_MIXER                           = _UxGT("Mesturadora");
  PROGMEM Language_Str MSG_GRADIENT                        = _UxGT("Degradado");
  PROGMEM Language_Str MSG_FULL_GRADIENT                   = _UxGT("Degradado Total");
  PROGMEM Language_Str MSG_TOGGLE_MIX                      = _UxGT("Mestura Conmutada");
  PROGMEM Language_Str MSG_CYCLE_MIX                       = _UxGT("Mestura Cíclica");
  PROGMEM Language_Str MSG_GRADIENT_MIX                    = _UxGT("Mestura de Degradado");
  PROGMEM Language_Str MSG_REVERSE_GRADIENT                = _UxGT("Degradado Inverso");
  PROGMEM Language_Str MSG_ACTIVE_VTOOL                    = _UxGT("Activar Ferr-V");
  PROGMEM Language_Str MSG_START_VTOOL                     = _UxGT("Inicio Ferr-V");
  PROGMEM Language_Str MSG_END_VTOOL                       = _UxGT("  Fin Ferr-V");
  PROGMEM Language_Str MSG_GRADIENT_ALIAS                  = _UxGT("Alias Ferr-V");
  PROGMEM Language_Str MSG_RESET_VTOOLS                    = _UxGT("Reiniciar Ferr-V");
  PROGMEM Language_Str MSG_COMMIT_VTOOL                    = _UxGT("Commit mest. Ferr-V");
  PROGMEM Language_Str MSG_VTOOLS_RESET                    = _UxGT("Ferr-V reiniciadas");
  PROGMEM Language_Str MSG_START_Z                         = _UxGT("Inicio Z:");
  PROGMEM Language_Str MSG_END_Z                           = _UxGT("  Fin Z:");

  PROGMEM Language_Str MSG_GAMES                           = _UxGT("Xogos");
  PROGMEM Language_Str MSG_BRICKOUT                        = _UxGT("Brickout");
  PROGMEM Language_Str MSG_INVADERS                        = _UxGT("Invaders");
  PROGMEM Language_Str MSG_SNAKE                           = _UxGT("Sn4k3");
  PROGMEM Language_Str MSG_MAZE                            = _UxGT("Labirinto");

  #if LCD_HEIGHT >= 4
    PROGMEM Language_Str MSG_ADVANCED_PAUSE_WAITING        = _UxGT(MSG_2_LINE("Preme o botón para", "continuar impresión"));
    PROGMEM Language_Str MSG_PAUSE_PRINT_PARKING           = _UxGT(MSG_1_LINE("Estacionando..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_INIT          = _UxGT(MSG_3_LINE("Agarde para", "comezar cambio", "de filamento"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_INSERT        = _UxGT(MSG_3_LINE("Introduza o", "filamento e", "faga click"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEAT          = _UxGT(MSG_2_LINE("Prema o botón para", "quentar o bico"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEATING       = _UxGT(MSG_2_LINE("Quentando bico", "Agarde, por favor..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_UNLOAD        = _UxGT(MSG_3_LINE("Agarde pola", "descarga do", "filamento"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_LOAD          = _UxGT(MSG_3_LINE("Agarde pola", "carga do", "filamento"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_PURGE         = _UxGT(MSG_2_LINE("Agarde para", "purgar o filamento"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_CONT_PURGE    = _UxGT(MSG_2_LINE("Prema para finalizar", "a purga do filamen."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_RESUME        = _UxGT(MSG_3_LINE("Agarde a que", "se retome", "a impresión"));
  #else
    PROGMEM Language_Str MSG_ADVANCED_PAUSE_WAITING        = _UxGT(MSG_1_LINE("Premer para continuar"));
    PROGMEM Language_Str MSG_PAUSE_PRINT_PARKING           = _UxGT(MSG_1_LINE("Estacionando..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_INIT          = _UxGT(MSG_1_LINE("Agarde..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_INSERT        = _UxGT(MSG_1_LINE("Introduza e click"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEAT          = _UxGT(MSG_1_LINE("Prema para quentar"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_HEATING       = _UxGT(MSG_1_LINE("Quentando..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_UNLOAD        = _UxGT(MSG_1_LINE("Descargando..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_LOAD          = _UxGT(MSG_1_LINE("Cargando..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_PURGE         = _UxGT(MSG_1_LINE("Purgando..."));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_CONT_PURGE    = _UxGT(MSG_1_LINE("Prema para finalizar"));
    PROGMEM Language_Str MSG_FILAMENT_CHANGE_RESUME        = _UxGT(MSG_1_LINE("Retomando..."));
  #endif

  PROGMEM Language_Str MSG_TMC_DRIVERS                     = _UxGT("Controladores TMC");
  PROGMEM Language_Str MSG_TMC_CURRENT                     = _UxGT("Controlador Actual");
  PROGMEM Language_Str MSG_TMC_HYBRID_THRS                 = _UxGT("Limiar Hibrido");
  PROGMEM Language_Str MSG_TMC_HOMING_THRS                 = _UxGT("Orixe sen Sensores");
  PROGMEM Language_Str MSG_TMC_STEPPING_MODE               = _UxGT("Modo de pasos");
  PROGMEM Language_Str MSG_TMC_STEALTH_ENABLED             = _UxGT("StealthChop Habilit.");
  PROGMEM Language_Str MSG_SERVICE_RESET                   = _UxGT("Reiniciar");
  PROGMEM Language_Str MSG_SERVICE_IN                      = _UxGT(" dentro:");
  PROGMEM Language_Str MSG_BACKLASH                        = _UxGT("Reacción");
  PROGMEM Language_Str MSG_BACKLASH_A                      = LCD_STR_A;
  PROGMEM Language_Str MSG_BACKLASH_B                      = LCD_STR_B;
  PROGMEM Language_Str MSG_BACKLASH_C                      = LCD_STR_C;
  PROGMEM Language_Str MSG_BACKLASH_CORRECTION             = _UxGT("Corrección");
  PROGMEM Language_Str MSG_BACKLASH_SMOOTHING              = _UxGT("Suavizado");

  PROGMEM Language_Str MSG_LEVEL_X_AXIS                    = _UxGT("Nivel Eixe X");
  PROGMEM Language_Str MSG_AUTO_CALIBRATE                  = _UxGT("Auto Calibrar");
  PROGMEM Language_Str MSG_HEATER_TIMEOUT                  = _UxGT("Tempo exc. Quent.");
  PROGMEM Language_Str MSG_REHEAT                          = _UxGT("Requentar");
  PROGMEM Language_Str MSG_REHEATING                       = _UxGT("Requentando...");
}
