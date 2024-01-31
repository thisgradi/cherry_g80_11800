// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "blackpill_f411.h"

static uint8_t indicators_state;

// void matrix_init_kb(void)
// {
// 	printf("matrix_init_kb");
// 	setPinOutput(LED_SR_SER);
// 	setPinOutput(LED_SR_RCLK);
// 	setPinOutput(LED_SR_SRCLK);
// 	matrix_init_user();
// }

// LED related ============================================

uint8_t getIndicatorsState(void) { 
	return indicators_state; 
}

void setIndicatorsState(uint8_t state) {
	//uprintf("setIndicatorsState: [%d]\n", state);
	indicators_state = state;
}

// 0111 1110
void showIndicators(void) {
	uint8_t buffer = indicators_state;
	//uprintf("showIndicators: [%d]\n", buffer);

	writePinLow(LED_SR_RCLK);
	for (uint8_t i = 0; i < 8; ++i) {
		if (buffer & 128) {	// 0010 0000
			writePinHigh(LED_SR_SER);
		} else {
			writePinLow(LED_SR_SER);
		}
		writePinHigh(LED_SR_SRCLK);
		writePinLow(LED_SR_SRCLK);
		buffer = buffer << 1;
	}
	writePinHigh(LED_SR_RCLK);
}