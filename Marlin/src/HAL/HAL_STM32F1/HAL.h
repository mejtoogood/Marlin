/**
 * Marlin 3D Printer Firmware
 *
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 * Copyright (c) 2016 Bob Cousins bobcousins42@googlemail.com
 * Copyright (c) 2015-2016 Nico Tonnhofer wurstnase.reprap@gmail.com
 * Copyright (c) 2017 Victor Perez
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * HAL for stm32duino.com based on Libmaple and compatible (STM32F1)
 */

#define CPU_32_BIT

#include "../../core/macros.h"
#include "../shared/Marduino.h"
#include "../shared/math_32bit.h"
#include "../shared/HAL_SPI.h"

#include "fastio.h"
#include "watchdog.h"

#include "timers.h"

#include <stdint.h>
#include <util/atomic.h>

#include "../../inc/MarlinConfigPre.h"

// ------------------------
// Defines
// ------------------------

#ifdef SERIAL_USB
  #define UsbSerial Serial
  #define MSerial1  Serial1
  #define MSerial2  Serial2
  #define MSerial3  Serial3
  #define MSerial4  Serial4
  #define MSerial5  Serial5
#else
  extern USBSerial SerialUSB;
  #define UsbSerial SerialUSB
  #define MSerial1  Serial
  #define MSerial2  Serial1
  #define MSerial3  Serial2
  #define MSerial4  Serial3
  #define MSerial5  Serial4
#endif

#if !WITHIN(SERIAL_PORT, -1, 5)
  #error "SERIAL_PORT must be from -1 to 5"
#endif
#if SERIAL_PORT == -1
  #define MYSERIAL0 UsbSerial
#elif SERIAL_PORT == 0
  #error "Serial port 0 does not exist"
#elif SERIAL_PORT == 1
  #define MYSERIAL0 MSerial1
#elif SERIAL_PORT == 2
  #define MYSERIAL0 MSerial2
#elif SERIAL_PORT == 3
  #define MYSERIAL0 MSerial3
#elif SERIAL_PORT == 4
  #define MYSERIAL0 MSerial4
#elif SERIAL_PORT == 5
  #define MYSERIAL0 MSerial5
#endif

#ifdef SERIAL_PORT_2
  #if !WITHIN(SERIAL_PORT_2, -1, 5)
    #error "SERIAL_PORT_2 must be from -1 to 5"
  #elif SERIAL_PORT_2 == SERIAL_PORT
    #error "SERIAL_PORT_2 must be different than SERIAL_PORT"
  #endif
  #define NUM_SERIAL 2
  #if SERIAL_PORT_2 == -1
    #define MYSERIAL1 UsbSerial
  #elif SERIAL_PORT_2 == 0
  #error "Serial port 0 does not exist"
  #elif SERIAL_PORT_2 == 1
    #define MYSERIAL1 MSerial1
  #elif SERIAL_PORT_2 == 2
    #define MYSERIAL1 MSerial2
  #elif SERIAL_PORT_2 == 3
    #define MYSERIAL1 MSerial3
  #elif SERIAL_PORT_2 == 4
    #define MYSERIAL1 MSerial4
  #elif SERIAL_PORT_2 == 5
    #define MYSERIAL1 MSerial5
  #endif
#else
  #define NUM_SERIAL 1
#endif

// Set interrupt grouping for this MCU
void HAL_init(void);

/**
 * TODO: review this to return 1 for pins that are not analog input
 */
#ifndef analogInputToDigitalPin
  #define analogInputToDigitalPin(p) (p)
#endif

#ifndef digitalPinHasPWM
  #define digitalPinHasPWM(P) (PIN_MAP[P].timer_device != nullptr)
#endif

#define CRITICAL_SECTION_START  uint32_t primask = __get_primask(); (void)__iCliRetVal()
#define CRITICAL_SECTION_END    if (!primask) (void)__iSeiRetVal()
#define ISRS_ENABLED() (!__get_primask())
#define ENABLE_ISRS()  ((void)__iSeiRetVal())
#define DISABLE_ISRS() ((void)__iCliRetVal())

// On AVR this is in math.h?
#define square(x) ((x)*(x))

#ifndef strncpy_P
  #define strncpy_P(dest, src, num) strncpy((dest), (src), (num))
#endif

// Fix bug in pgm_read_ptr
#undef pgm_read_ptr
#define pgm_read_ptr(addr) (*(addr))

#define RST_POWER_ON   1
#define RST_EXTERNAL   2
#define RST_BROWN_OUT  4
#define RST_WATCHDOG   8
#define RST_JTAG       16
#define RST_SOFTWARE   32
#define RST_BACKUP     64

// ------------------------
// Types
// ------------------------

typedef int8_t pin_t;

// ------------------------
// Public Variables
// ------------------------

// Result of last ADC conversion
extern uint16_t HAL_adc_result;

// ------------------------
// Public functions
// ------------------------

// Disable interrupts
#define cli() noInterrupts()

// Enable interrupts
#define sei() interrupts()

// Memory related
#define __bss_end __bss_end__

// Clear reset reason
void HAL_clear_reset_source(void);

// Reset reason
uint8_t HAL_get_reset_source(void);

void _delay_ms(const int delay);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

/*
extern "C" {
  int freeMemory(void);
}
*/

extern "C" char* _sbrk(int incr);

/*
static int freeMemory() {
  volatile int top;
  top = (int)((char*)&top - reinterpret_cast<char*>(_sbrk(0)));
  return top;
}
*/

static int freeMemory() {
  volatile char top;
  return &top - reinterpret_cast<char*>(_sbrk(0));
}

#pragma GCC diagnostic pop

//
// EEPROM
//

/**
 * TODO: Write all this EEPROM stuff. Can emulate EEPROM in flash as last resort.
 * Wire library should work for i2c EEPROMs.
 */
void eeprom_write_byte(uint8_t *pos, unsigned char value);
uint8_t eeprom_read_byte(uint8_t *pos);
void eeprom_read_block(void *__dst, const void *__src, size_t __n);
void eeprom_update_block(const void *__src, void *__dst, size_t __n);

//
// ADC
//

#define HAL_ANALOG_SELECT(pin) pinMode(pin, INPUT_ANALOG);

void HAL_adc_init(void);

#define HAL_START_ADC(pin)  HAL_adc_start_conversion(pin)
#define HAL_READ_ADC()      HAL_adc_result
#define HAL_ADC_READY()     true

void HAL_adc_start_conversion(const uint8_t adc_pin);
uint16_t HAL_adc_get_result(void);

uint16_t analogRead(pin_t pin); // need HAL_ANALOG_SELECT() first
void analogWrite(pin_t pin, int pwm_val8); // PWM only! mul by 257 in maple!?

#define GET_PIN_MAP_PIN(index) index
#define GET_PIN_MAP_INDEX(pin) pin
#define PARSED_PIN_INDEX(code, dval) parser.intval(code, dval)

#define JTAG_DISABLE() afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY)
#define JTAGSWD_DISABLE() afio_cfg_debug_ports(AFIO_DEBUG_NONE)
