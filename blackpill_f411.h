#pragma once

#include "quantum.h"

// LED indicators-related stuff ===========================

// There are 3 indicators with 3 states each:
// 	* RED
// 	* OFF
// 	* GREEN
//
// The use cases are as follows:
// 	* System indicator LEDs
// 	* Layer indication
// 	* Short animation
//
// System indicator states are taken from host, while layer
// indication is determined by the keyboard itself. Layer 
// indication is done with a color that differs from the
// one used for system indication.
//
// With an orhtolinear layout, system indicators are not as
// useful, as with the standard one. Most of the time LEDs
// will remain OFF. Therefore, the indication should not
// be much constrained by its terms and events.

// The state of the indicators can be stored in 6 bits. We
// use bits [1..6] of uint8_t to select the state of each 
// cathode (they correspond to pins 1..6 of SR):

#define LED_LEFT_R	0x02
#define LED_LEFT_G	0x04

#define LED_CNTR_R  0x08
#define LED_CNTR_G  0x10

#define LED_RGHT_R	0x20
#define LED_RGHT_G	0x40

// The two remaining bits 0, 7 can be reused:
//  * Reversing the colors (R-G)
//  * Mirroring the indication (Left-Right)

#define LED_REVERSE	0x80
#define LED_MIRROR  0x01

// For the sake of conveniency, we define combinations:
//  * All leds red
//  * All leds green
//  * All leds off

#define LED_ALL_R	0x2A
#define LED_ALL_G	0x54
#define LED_ALL_OFF 0x00

// The previously described use-cases can be reproduced
// using a number of functions:

// returns the state of LED indicators (all 8 bits)
uint8_t getIndicatorsState(void);

// sets new state of the LED indicators (all 8 bits)
void setIndicatorsState(uint8_t state);

// shows the indicators 
// RED is shown when both colors are selected
void showIndicators(void);

// sets layer I or II with NUM, CAPS, SCROLL indicators
// TODO: void setSystemIndicators(uint8_t layer);