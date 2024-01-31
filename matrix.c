/*
Copyright 2014 Ralf Schmitt <ralf@bunkertor.net>
Modified by Ryan Skidmore <rskeys@ryanskidmore.co.uk> (@ryanskidmore)
to support the rskeys100.

Copyright 2024
Modified by BFB Workshop to support the Compaq'ed G80-11800 ortho.

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

#include <stdbool.h>
#include "matrix.h"
//#include <util/delay.h> TODO: not available for STM
#include "quantum.h"

static const uint32_t col_values[24] = COL_SR_COLS;

static uint8_t read_rows(void);
static void    select_col(uint8_t col);

static void    shift_out_single(uint8_t value);
static void    shift_out(uint32_t value);

void matrix_init_custom(void) {
  setPinOutput(LED_SR_SER);
  setPinOutput(LED_SR_RCLK);
  setPinOutput(LED_SR_SRCLK);

  setPinInput(ROW_0);
  setPinInput(ROW_1);
  setPinInput(ROW_2);
  setPinInput(ROW_3);
  setPinInput(ROW_4);
  setPinInput(ROW_5);
  setPinInput(ROW_6);

  setPinOutput(COL_SR_SER);
  setPinOutput(COL_SR_RCLK);
  setPinOutput(COL_SR_SRCLK);
}

// This function updates current_matrix, returning true, if there are any changes.
//
// 1. Select a column
// 2. Read all rows
// 3. Go through rows, checking if current_matrix[row] has the selected column set:
//
//  "state changed"
//      pressed:   saved state = 0, column = 1, row = 1 => saved state = 1 (0 ^ 1 = 1)
//      unpressed: saved state = 1, column = 1, row = 0 => saved state = 0 (1 ^ 1 = 0)
//
//  "state not changed"
//      idle:      saved state = 0, column = 1, row = 0
//      held:      saved state = 1, column = 1, row = 1
//
// bool matrix_scan_custom(matrix_row_t current_matrix[]) {
//     static bool changed = false;
//     //static bool saved_col_state = 0;
//     //static bool row_selected = 0;

//     static uint32_t mask_col = 0;
//     static uint8_t  mask_row = 0;

//     mask_col = 1;

//     for (uint8_t col = 0; col < MATRIX_COLS; col++) {   // 24 (suspicious)
//         select_col(col);                                        // puts 1 on one of the columns
//         //_delay_us(1);
//         wait_us(1);
//         uint8_t rows = read_rows();                             // compiles row states into one 8 bit value

//         mask_row = 1;

//         for (uint8_t row = 0; row < MATRIX_ROWS; row++) {

//             // bitwise AND operation ("&"): 1 & 1 = 1 | 1 & 0 = 0 | 0 & 0 = 0.

//             bool saved_col_state = (current_matrix[row] & mask_col) ? 1 : 0;
//             bool row_selected = (rows & mask_row) ? 1 : 0;

//             if (saved_col_state != row_selected) {
//                 //printf("[%d:%d] (%d:%d)\n", col, row, saved_col_state, row_selected); // gets constantly printed, it seems
//                 // bitwise XOR operation ("^"): 1 ^ 1 = 0 | 1 ^ 0 = 1 | 0 ^ 0 = 0

//                 current_matrix[row] ^= mask_col;
//                 changed = true;
//             }
//             else
//             {
//                 //printf("not changed\n");
//             }

//             mask_row <<= 1;
//         }

//         mask_col <<= 1;
//     }

//     return changed;
// }

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        wait_us(1);
        uint8_t rows = read_rows();
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = ((uint32_t)(current_matrix[row]) & (matrix_row_t)(1UL << col)) ? 1 : 0;
            bool curr_bit = ((uint32_t)rows & (uint32_t)(1UL << row)) ? 1 : 0;
            if (prev_bit != curr_bit) {
                current_matrix[row] = (uint32_t)(current_matrix[row]) ^ (uint32_t)(1UL << col);
                changed = true;
            }
        }
    }

    return changed;
}

static uint8_t read_rows(void) {
  return   (readPin(ROW_6) << 6)    // 0100 0000
  		 | (readPin(ROW_5) << 5)    // 0010 0000
         | (readPin(ROW_4) << 4)    // 0001 0000
         | (readPin(ROW_3) << 3)    // 0000 1000
         | (readPin(ROW_2) << 2)    // 0000 0100
         | (readPin(ROW_1) << 1)    // 0000 0010
         | (readPin(ROW_0) );       // 0000 0001
}

static void select_col(uint8_t col) {
    shift_out(col_values[col]);
}

static void shift_out(uint32_t value) {
  uint8_t first_byte  = (value >> 16) & 0xFF;
  uint8_t second_byte = (value >> 8) & 0xFF;
  uint8_t third_byte  = (uint8_t)(value & 0xFF);
  // wait_us(100000);
  // printf("shift_out [%ld]", value);
  // printf("[%d][%d][%d]\n", first_byte, second_byte, third_byte);

  // shift_out [1]        [0]     [0]     [1]   // 00000000 00000000 00000001
  // shift_out [2]        [0]     [0]     [2]   // 00000000 00000000 00000010
  // shift_out [4]        [0]     [0]     [4]   // 00000000 00000000 00000100
  // shift_out [8]        [0]     [0]     [8]   // 00000000 00000000 00001000
  // shift_out [16]       [0]     [0]     [16]  // 00000000 00000000 00010000
  // shift_out [32]       [0]     [0]     [32]  // 00000000 00000000 00100000
  // shift_out [64]       [0]     [0]     [64]  // 00000000 00000000 01000000
  // shift_out [128]      [0]     [0]     [128] // 00000000 00000000 10000000
  // shift_out [256]      [0]     [1]     [0]   // 00000000 00000001 00000000
  // shift_out [512]      [0]     [2]     [0]   // 00000000 00000010 00000000
  // shift_out [1024]     [0]     [4]     [0]   // 00000000 00000100 00000000
  // shift_out [2048]     [0]     [8]     [0]   // 00000000 00001000 00000000
  // shift_out [4096]     [0]     [16]    [0]   // 00000000 00010000 00000000
  // shift_out [8192]     [0]     [32]    [0]   // 00000000 00100000 00000000
  // shift_out [16384]    [0]     [64]    [0]   // 00000000 01000000 00000000
  // shift_out [32768]    [0]     [128]   [0]   // 00000000 10000000 00000000
  // shift_out [65536]    [1]     [0]     [0]   // 00000001 00000000 00000000
  // shift_out [131072]   [2]     [0]     [0]   // 00000010 00000000 00000000
  // shift_out [262144]   [4]     [0]     [0]   // 00000100 00000000 00000000
  // shift_out [524288]   [8]     [0]     [0]   // 00001000 00000000 00000000
  // shift_out [1048576]  [16]    [0]     [0]   // 00010000 00000000 00000000
  // shift_out [2097152]  [32]    [0]     [0]   // 00100000 00000000 00000000
  // shift_out [4194304]  [64]    [0]     [0]   // 01000000 00000000 00000000
  // shift_out [8388608]  [128]   [0]     [0]   // 10000000 00000000 00000000

  writePinLow(COL_SR_RCLK);     // do not change the output, shift internal registers only
  wait_us(10);
  shift_out_single(first_byte);
  shift_out_single(second_byte);
  shift_out_single(third_byte);
  wait_us(10);
  writePinHigh(COL_SR_RCLK);    // change the output
  /* We delay here to prevent multiple consecutive keys being triggered with a single switch press */
  //_delay_us(10);
  wait_us(10);
  // 100(1) not registering
  // 10(10) all columns, sensitive
  // 20(10) all columns, seems less sensitive
  // 20(20) still all columns, skipping presses
  // 20(10)(10) all columns, skipping presses
  // 30(10) all columns, skipping some presses
  // (10)(10) all columns, no skipping
  // (10)(30) all columns
}

static void shift_out_single(uint8_t value) {
    for (uint8_t i = 0; i < 8; i++) {
        if (value & 0b10000000) {
            writePinHigh(COL_SR_SER);
        } else {
            writePinLow(COL_SR_SER);
        }

        // rising edge on SRCLK triggers the shift
        writePinHigh(COL_SR_SRCLK);
        writePinLow(COL_SR_SRCLK);        

        value = value << 1;
    }
}