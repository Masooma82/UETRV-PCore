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
    int ct=0;
    int repetitions = 10000;
    
    const char done[8] = {'D','o','n','e','!', '\n', '\r'};
    const char mcycl[8] = {'C','y','c','l','e', '=', '\r'};
    const char minst[9] = {'\n','I','n','s','t','r', '=', '\r'};
         // Read cycle count
    volatile uint32_t cycles_start = read_csr_mcycle(); // mcycle CSR
    uint32_t i = 0;
    uint32_t count0 = 0;

    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");

    for (i=0; i<repetitions; i++) {
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0));
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );

        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );

        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );

        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
        asm volatile("add %0, %1, %2" : "=r" (count0) : "r" (count0), "r" (count0) );
    }

    asm volatile ("nop");
    asm volatile ("nop");
    asm volatile ("nop");
 
    // Read instruction count
    volatile uint32_t instrs_end = read_csr_minstret(); // minstret CSR
    // Calculate IPC
    volatile uint32_t cycles_end = read_csr_mcycle(); // mcycle CSR
    uint32_t cycles = cycles_end - cycles_start;
    uint32_t instrs = instrs_end; // Assuming no interrupts
    char buffer[20];
    intToString(cycles, buffer);
	for(ct = 0; ct < 8; ct++) {
    	  Uetrv32_Uart_Tx((mcycl[ct])); 
  	}  
	for(ct = 0; ct < 8; ct++) {
    	  Uetrv32_Uart_Tx((buffer[ct])); 
  	}  
    intToString(instrs, buffer);
	for(ct = 0; ct < 9; ct++) {
    	  Uetrv32_Uart_Tx((minst[ct])); 
  	}  
	for(ct = 0; ct < 8; ct++) {
    	  Uetrv32_Uart_Tx((buffer[ct])); 
  	}  

	return 0;
}
