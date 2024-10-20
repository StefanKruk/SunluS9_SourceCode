#line 1 "/mnt/hgfs/SVN/Marlin-2.0.x/Marlin/src/HAL/TEENSY40_41/Servo.cpp"
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
 * HAL Servo for Teensy 4.0 (IMXRT1062DVL6A) / 4.1 (IMXRT1062DVJ6A)
 */

#ifdef __IMXRT1062__

#include "../../inc/MarlinConfig.h"

#if HAS_SERVOS

#include "Servo.h"

int8_t libServo::attach(const int inPin) {
  if (inPin > 0) servoPin = inPin;
  return super::attach(servoPin);
}

int8_t libServo::attach(const int inPin, const int inMin, const int inMax) {
  if (inPin > 0) servoPin = inPin;
  return super::attach(servoPin, inMin, inMax);
}

void libServo::move(const int value) {
  constexpr uint16_t servo_delay[] = SERVO_DELAY;
  static_assert(COUNT(servo_delay) == NUM_SERVOS, "SERVO_DELAY must be an array NUM_SERVOS long.");
  if (attach(0) >= 0) {
    write(value);
    safe_delay(servo_delay[servoIndex]);
    TERN_(DEACTIVATE_SERVOS_AFTER_MOVE, detach());
  }
}

void libServo::detach() {
  // PWMServo library does not have detach() function
  //super::detach();
}

#endif // HAS_SERVOS
#endif // __IMXRT1062__
