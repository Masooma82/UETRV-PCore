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
int main (void) {
   Uetrv32_Uart_Init(UART_BAUD_DIV);
    
   const char done[8] = {'D','o','n','e','!', '\n', '\r'};
   const char mcycl[8] = {'C','y','c','l','e', '=', '\r'};
   const char minst[9] = {'\r','I','n','s','t','r', '=', '\r'};  
    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
    // Read cycle count
    volatile uint32_t cycles_start = read_csr_mcycle(); // mcycle CSR
    uint32_t repetitions = 10000;
    int count=0;
    uint32_t inner_repetitions;
    inner_repetitions = repetitions / 10;

    uint32_t i = 0;
    uint32_t jump = 1;
    uint32_t print = 1;

    uint32_t jump_1 = inner_repetitions * 1;
    uint32_t jump_2 = inner_repetitions * 2;
    uint32_t jump_3 = inner_repetitions * 3;
    uint32_t jump_4 = inner_repetitions * 4;
    uint32_t jump_5 = inner_repetitions * 5;
    uint32_t jump_6 = inner_repetitions * 6;
    uint32_t jump_7 = inner_repetitions * 7;
    uint32_t jump_8 = inner_repetitions * 8;
    uint32_t jump_9 = inner_repetitions * 9;
    uint32_t jump_10 = inner_repetitions * 10;

    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");

    for (i = 0; i < repetitions; i++) {
        switch (jump) {
            case 1:
                if (i > jump_1)
                    jump++;
                    print += 1;
            break;

            case 2:
                if (i > jump_2)
                    jump++;
                    print += 2;
            break;

            case 3:
                if (i > jump_3)
                    jump++;
                    print += 3;
            break;

            case 4:
                if (i > jump_4)
                    jump++;
                    print += 4;
            break;

            case 5:
                if (i > jump_5)
                    jump++;
                    print += 5;
            break;

            case 6:
                if (i > jump_6)
                    jump++;
                    print += 6;
            break;

            case 7:
                if (i > jump_7)
                    jump++;
                    print += 7;
            break;

            case 8:
                if (i > jump_8)
                    jump++;
                    print += 8;
            break;

            case 9:
                if (i > jump_9)
                    jump++;
                    print += 9;
            break;

            case 10:
                if (i > jump_10)
                    jump++;
                    print += 10;
            break;
        }
    }

    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");

    (void) print;

    // Read instruction count
    volatile uint32_t instrs_end = read_csr_minstret(); // minstret CSR
    // Calculate IPC
    volatile uint32_t cycles_end = read_csr_mcycle(); // mcycle CSR
    uint32_t cycles = cycles_end - cycles_start;
    uint32_t instrs = instrs_end; // Assuming no interrupts
    char buffer[20];
    intToString(cycles, buffer);
	for(count = 0; count < 8; count++) {
    	  Uetrv32_Uart_Tx((mcycl[count])); 
  	}  
	for(count = 0; count < 8; count++) {
    	  Uetrv32_Uart_Tx((buffer[count])); 
  	}  
    intToString(instrs, buffer);
	for(count = 0; count < 9; count++) {
    	  Uetrv32_Uart_Tx((minst[count])); 
  	}  
	for(count = 0; count < 8; count++) {
    	  Uetrv32_Uart_Tx((buffer[count])); 
  	}  

	return 0;
}
