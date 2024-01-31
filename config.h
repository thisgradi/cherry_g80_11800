/*
Copyright 2024 BFB Workshop

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// mouse related ======================================================================

#define DEBOUNCE 5
//#define DEBOUNCE 10 // left and right buttons mostly work
//#define DEBOUNCE 100

//#define PS2_MOUSE_USE_2_1_SCALING

#define PS2_CLOCK_PIN A2
#define PS2_DATA_PIN  A3

#define PS2_MOUSE_X_MULTIPLIER 10
#define PS2_MOUSE_Y_MULTIPLIER 10
//#define PS2_MOUSE_V_MULTIPLIER 1
//#define PS2_MOUSE_SCROLL_DIVISOR_H 3
//#define PS2_MOUSE_SCROLL_DIVISOR_V 3
//#define PS2_MOUSE_INIT_DELAY 1000
//#define PS2_MOUSE_SCROLL_BTN_MASK 0
//#define PS2_MOUSE_SCROLL_BTN_SEND 0
//#define PS2_MOUSE_INVERT_BUTTONS

// this makes it have at least some good packets
// (on test build only)
#define PS2_MOUSE_USE_REMOTE_MODE 

// For some reason, only when this two options are enabled,
// and this is a test build, there is at least some movement.
#define PS2_MOUSE_DEBUG_HID
#define PS2_MOUSE_DEBUG_RAW
#define PS2_MOUSE_INIT_DELAY 1000

// audio related ======================================================================

// #define AUDIO_INIT_DELAY
// #define AUDIO_PIN	  		B9		//uses TIM4_CH4
// #define AUDIO_PWM_DRIVER	PWMD4	//TIM4
// #define AUDIO_PWM_CHANNEL	4		//CH4
// #define AUDIO_PWM_PAL_MODE	1		//first alt function

#define AUDIO_PIN B5
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL 1
#define AUDIO_STATE_TIMER GPTD4

//#define AUDIO_PIN_ALT A5	// secondary speaker
//#define AUDIO_PIN_ALT_AS_NEGATIVE // connecting 1 speaker to two pins for extra push

// indication related =================================================================

// NOTE: SRCLK = CLOCK, RCLK = LATCH/REFRESH

#define LED_SR_SER		B12
#define LED_SR_RCLK		B13
#define LED_SR_SRCLK	B14

// OLED related =======================================================================

#define I2C_DRIVER        I2CD1
#define I2C1_SCL_PIN      B8
#define I2C1_SDA_PIN      B9
#define I2C1_SCL_PAL_MODE 4
#define I2C1_SDA_PAL_MODE 4
#define I2C1_CLOCK_SPEED  400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_16_9

#ifndef OLED_BRIGHTNESS
#define OLED_BRIGHTNESS 150
#endif

// matrix related =====================================================================

#define MATRIX_ROWS 7
#define MATRIX_COLS 24

// NOTE: There are, in fact, 19 columns, but shift registers have 24 pins in total.

#define ROW_0 B6
#define ROW_1 B7
#define ROW_2 B10
#define ROW_3 B1
#define ROW_4 B0
#define ROW_5 A1
#define ROW_6 A0

// NOTE: SRCLK = CLOCK, RCLK = LATCH/REFRESH

#define COL_SR_SER		A15
#define COL_SR_RCLK		B4
#define COL_SR_SRCLK	B3

// NOTE: Following is a hexadecimal representation of singular
//		 bit masks.
//		 
//		 Each two digits after 'x' represent eight outputs of
//       a single shift register. 
//
//		 Each digit represents 4 bits:
//		 1 hex = 0001, 2 hex = 0010, 4 hex = 0100, 8 hex = 1000
//
//		 0x000001 = 00000000 00000000 00000001	// 1st SR
//       0x000010 = 00000000 00000000 00010000	//
//		 ...
//		 0x800000 = 10000000 00000000 00000000  // 3rd SR

#define COL_SR_COLS { 0x000001, 0x000002, 0x000004, 0x000008, 0x000010, 0x000020, 0x000040, 0x000080, \
					  0x000100, 0x000200, 0x000400, 0x000800, 0x001000, 0x002000, 0x004000, 0x008000, \
					  0x010000, 0x020000, 0x040000, 0x080000, 0x100000, 0x200000, 0x400000, 0x800000}

#define DIODE_DIRECTION COL2ROW