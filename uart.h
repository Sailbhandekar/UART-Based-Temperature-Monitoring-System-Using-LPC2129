#ifndef UART_H
#define UART_H

void uart0_init(void);
void uart0_sendchar(char c);
void uart0_sendstring( char* str);
char uart0_getchar(void);
unsigned char uart0_available(void);

#endif
