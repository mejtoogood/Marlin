/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2019 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#pragma once

/**
 * Custom Status Screen bitmap
 *
 * Place this file in the root with your configuration files
 * and enable CUSTOM_STATUS_SCREEN_IMAGE in Configuration.h.
 *
 * Use the Marlin Bitmap Converter to make your own:
 * http://marlinfw.org/tools/u8glib/converter.html
 */

//
// Status Screen Logo bitmap
//
/**
 * Made with Marlin Bitmap Converter
 * http://marlinfw.org/tools/u8glib/converter.html
 *
 * This bitmap from the file 'statusscreen.png'
 */
#define STATUS_LOGO_Y 1
#define STATUS_LOGO_WIDTH 48
const unsigned char status_logo_bmp[] PROGMEM = {
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,
  B10000011,B11111111,B11001111,B10011111,B11111111,B11111111,
  B10000001,B11111111,B11001111,B10011111,B11111111,B11111111,
  B10011001,B00011000,B11000001,B10011000,B11000000,B00111111,
  B10000001,B00010010,B01001001,B10010010,B01001001,B00111111,
  B10000011,B00110010,B01001001,B10010010,B01001001,B00111111,
  B10011111,B00110010,B01001001,B10010000,B01001001,B00111111,
  B10011111,B00110010,B01001001,B10010011,B11001001,B00111111,
  B10011111,B00111000,B11000001,B10011000,B01001001,B00111111,
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,
  B11111111,B11000011,B00111100,B11001111,B00111111,B11111111,
  B11111111,B10000001,B00111111,B11001111,B00111111,B11111111,
  B11111111,B10011001,B00000100,B11001000,B00111111,B11111111,
  B11111111,B10011111,B00100100,B11001001,B00111111,B11111111,
  B11111111,B10011111,B00100100,B11001001,B00111111,B11111111,
  B11111111,B10011001,B00100100,B11001001,B00111111,B11111111,
  B11111111,B10000001,B00100100,B11001001,B00111111,B11111111,
  B11111111,B11000011,B00100100,B11001000,B00111111,B11111111,
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,
  B11111111,B11111111,B11111111,B11111111,B11111111,B11111111
};



//
// Use default bitmaps
//
#define STATUS_HOTEND_ANIM
#define STATUS_BED_ANIM
#define STATUS_HEATERS_XSPACE   20
#if HOTENDS < 2
  #define STATUS_HEATERS_X      48
  #define STATUS_BED_X          72
#else
  #define STATUS_HEATERS_X      40
  #define STATUS_BED_X          80
#endif
