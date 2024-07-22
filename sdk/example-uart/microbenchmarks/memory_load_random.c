/*
 * Copyright (C) 2014  Marco Antonio Zanata Alves (mazalves at inf.ufrgs.br)
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
 */
/// Linear Feedback Shift Register using 32 bits and XNOR. Details at:
/// http://www.xilinx.com/support/documentation/application_notes/xapp052.pdf
/// http://www.ece.cmu.edu/~koopman/lfsr/index.html

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>


#include "../Interfaces/uart.h"
#include "../Interfaces/plic.h"
// =============================================================================
// Function to read CSR (Control and Status Register)
static inline uint32_t read_csr_mcycle(void) {
    volatile uint32_t value;
    asm volatile ("csrr %0, mcycle" : "=r"(value) : :);
    return value;
}

static inline uint32_t read_csr_minstret(void) {
    volatile uint32_t value;
    asm volatile ("csrr %0, minstret" : "=r"(value) : :);
    return value;
}
void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        // Swap characters at start and end
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        
        // Move towards the center
        start++;
        end--;
    }
}

char* intToString(int num, char str[]) {
    int i = 0;
    int isNegative = 0;

    // Handle negative numbers
    if (num < 0) {
        isNegative = 1;
        num = -num;
    }

    // Process individual digits
    while (num != 0) {
        int digit = num % 10;
        str[i++] = digit + '0';
        num = num / 10;
    }

    // Add minus sign for negative numbers
    if (isNegative) {
        str[i++] = '-';
    }

    // Null-terminate the string
    str[i] = '\0';

    // Reverse the string to get the correct order
    reverse(str, i);

    return str;
}

// =============================================================================
uint64_t string_to_uint64(char *string) {
    uint64_t result = 0;
    char c;

    for (  ; (c = *string ^ '0') <= 9 && c >= 0; ++string) {
        result = result * 10 + c;
    }
    return result;
};
// =============================================================================

struct list {
    uint32_t value;
    uint32_t pad[7];
};
typedef struct list element;
// =============================================================================
int main (void) {
    Uetrv32_Uart_Init(UART_BAUD_DIV);
    int ct=0;
   const char done[8] = {'D','o','n','e','!', '\n', '\r'};
   const char mcycl[8] = {'C','y','c','l','e', '=', '\r'};
   const char minst[9] = {'\r','I','n','s','t','r', '=', '\r'};
         // Read cycle count
    volatile uint32_t cycles_start = read_csr_mcycle(); // mcycle CSR
     uint32_t size=1024;
    uint32_t repetitions=10000;


    uint32_t i = 0, j = 0;
    uint32_t jump = 1;
    uint32_t print = 0;
    uint32_t count[32];
    for (i = 0; i < 32; i++) {
        count[i] = 0;
    }

    unsigned int lfsr = 0x80000000;
    unsigned bit;

    element ptr_vector[size];

    for (i = 0; i < size; i++) {
        ptr_vector[i].value = i;
    }

    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    for (i = 0; i < repetitions; i++) {
        for (j = 0; j < size; j += 32) {
            /// Linear Feedback Shift Register
            bit  = ~((lfsr >> 0) ^ (lfsr >> 10) ^ (lfsr >> 11) ^ (lfsr >> 30) ) & 1;
            lfsr =  (lfsr >> 1) | (bit << 31);

            jump = lfsr % (size - 32);
            count[0] += ptr_vector[jump + 0].value;
            count[1] += ptr_vector[jump + 1].value;
            count[2] += ptr_vector[jump + 2].value;
            count[3] += ptr_vector[jump + 3].value;
            count[4] += ptr_vector[jump + 4].value;
            count[5] += ptr_vector[jump + 5].value;
            count[6] += ptr_vector[jump + 6].value;
            count[7] += ptr_vector[jump + 7].value;

            count[8] += ptr_vector[jump + 8].value;
            count[9] += ptr_vector[jump + 9].value;
            count[10] += ptr_vector[jump + 10].value;
            count[11] += ptr_vector[jump + 11].value;
            count[12] += ptr_vector[jump + 12].value;
            count[13] += ptr_vector[jump + 13].value;
            count[14] += ptr_vector[jump + 14].value;
            count[15] += ptr_vector[jump + 15].value;

            count[16] += ptr_vector[jump + 16].value;
            count[17] += ptr_vector[jump + 17].value;
            count[18] += ptr_vector[jump + 18].value;
            count[19] += ptr_vector[jump + 19].value;
            count[20] += ptr_vector[jump + 20].value;
            count[21] += ptr_vector[jump + 21].value;
            count[22] += ptr_vector[jump + 22].value;
            count[23] += ptr_vector[jump + 23].value;

            count[24] += ptr_vector[jump + 24].value;
            count[25] += ptr_vector[jump + 25].value;
            count[26] += ptr_vector[jump + 26].value;
            count[27] += ptr_vector[jump + 27].value;
            count[28] += ptr_vector[jump + 28].value;
            count[29] += ptr_vector[jump + 29].value;
            count[30] += ptr_vector[jump + 30].value;
            count[31] += ptr_vector[jump + 31].value;
        }
    }
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");

    for (i = 0; i < 8; i++) {
        print += count[i];
    }
    (void) print;
// Read instruction count
    volatile uint32_t instrs_end = read_csr_minstret(); // minstret CSR
    // Calculate IPC
    volatile uint32_t cycles_end = read_csr_mcycle(); // mcycle CSR
    uint32_t cycles = cycles_end - cycles_start;
    uint32_t instrs = instrs_end; // Assuming no interrupts
    char buffer[28];
    intToString(cycles, buffer);
	for(ct = 0; ct < 8; ct++) {
    	  Uetrv32_Uart_Tx((mcycl[ct])); 
  	}  
	for(ct = 0; ct < 12; ct++) {
    	  Uetrv32_Uart_Tx((buffer[ct])); 
  	}  
    intToString(instrs, buffer);
	for(ct = 0; ct < 9; ct++) {
    	  Uetrv32_Uart_Tx((minst[ct])); 
  	}  
	for(ct = 0; ct < 12; ct++) {
    	  Uetrv32_Uart_Tx((buffer[ct])); 
  	}  

	return 0;

}