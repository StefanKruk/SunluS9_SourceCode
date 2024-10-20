#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/DUE/Tone.cpp"
/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * SAMD51 HAL developed by Giuliano Zaro (AKA GMagician)
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
 * Description: Tone function for Arduino Due and compatible (SAM3X8E)
 * Derived from https://forum.arduino.cc/index.php?topic=136500.msg2903012#msg2903012
 */

#ifdef ARDUINO_ARCH_SAM

#include "../../inc/MarlinConfig.h"
#include "HAL.h"

static pin_t tone_pin;
volatile static int32_t toggles;

void tone(const pin_t _pin, const unsigned int frequency, const unsigned long duration) {
  tone_pin = _pin;
  toggles = 2 * frequency * duration / 1000;
  HAL_timer_start(TONE_TIMER_NUM, 2 * frequency);
}

void noTone(const pin_t _pin) {
  HAL_timer_disable_interrupt(TONE_TIMER_NUM);
  extDigitalWrite(_pin, LOW);
}

HAL_TONE_TIMER_ISR() {
  static uint8_t pin_state = 0;
  HAL_timer_isr_prologue(TONE_TIMER_NUM);

  if (toggles) {
    toggles--;
    extDigitalWrite(tone_pin, (pin_state ^= 1));
  }
  else noTone(tone_pin);                         // turn off interrupt
}

#endif // ARDUINO_ARCH_SAM
