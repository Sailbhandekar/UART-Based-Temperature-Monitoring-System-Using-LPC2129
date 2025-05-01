#include <lpc21xx.h>
#include "uart.h"

void uart0_init(void) {
    PINSEL0 |= 0x00000005;     // Enable UART0 TxD0 and RxD0 (P0.0 and P0.1)
    U0LCR = 0x83;              // Enable DLAB, 8-bit, 1 stop bit, no parity
    U0DLL = 97;                // Baud rate 9600 (PCLK = 15MHz)
    U0DLM = 0;
    U0LCR = 0x03;              // Disable DLAB
}

void uart0_sendchar(char c) {
    while (!(U0LSR & 0x20));   // Wait until THR is empty
    U0THR = c;
}

void uart0_sendstring (char* str) {
    while (*str) {
        uart0_sendchar(*str++);
    }
}

char uart0_getchar(void) {
    while (!(U0LSR & 0x01));   // Wait for data ready
    return U0RBR;
}

unsigned char uart0_available(void) {
    return (U0LSR & 0x01);
}
