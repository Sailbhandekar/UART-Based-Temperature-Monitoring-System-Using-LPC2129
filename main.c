#include <lpc21xx.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"

// Function declarations
void adc_init(void);
unsigned int read_adc(void);
void delay_ms(unsigned int ms);
float adc_to_celsius(unsigned int adc_val);
void send_float(float val);

void adc_init(void) {
    PINSEL1 &= ~(3 << 22);     // Clear bits for P0.27
    PINSEL1 |=  (1 << 22);     // Set bit for AD0.0 function

    ADCR = 0;
    ADCR |= (1 << 0);          // Select AD0.0 channel
    ADCR |= (13 << 8);         // Clock divider
    ADCR |= (1 << 21);         // Enable ADC
}

unsigned int read_adc(void) {
    ADCR |= (1U << 24);                  // Start conversion
    while (!(ADDR & (1U << 31)));        // Wait for DONE bit
    return ((ADDR >> 6) & 0x3FF);        // Extract 10-bit result
}

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 6000; j++);
}

float adc_to_celsius(unsigned int adc_val) {
    return (adc_val * 3.3 / 1023.0) * 100;
}

// Function to send float as string via UART without buffer
void send_float(float val) {
    int int_part = (int)val;
    int frac_part = (int)((val - int_part) * 100);  // Two decimal places
    char str[10];

    sprintf(str, "%d.", int_part);
    uart0_sendstring(str);
    sprintf(str, "%02d", frac_part);
    uart0_sendstring(str);
}

int main(void) {
    float temp_c, temp_f;
    unsigned int adc_val;
    float min_temp = 100.0, max_temp = 0.0;
    float last_temp = -1.0;
    char cmd[16];
    int cmd_index = 0;

    uart0_init();
    adc_init();

    uart0_sendstring("UART Temperature Monitor\r\n");

    while (1) {
        adc_val = read_adc();
        temp_c = adc_to_celsius(adc_val);
        temp_f = temp_c * 1.7 + 32;

        if (temp_c < min_temp) min_temp = temp_c;
        if (temp_c > max_temp) max_temp = temp_c;

        if (temp_c - last_temp > 0.1 || last_temp - temp_c > 0.1) {
            last_temp = temp_c;

            uart0_sendstring("Temp: ");
            send_float(temp_c);
            uart0_sendstring(" C / ");
            send_float(temp_f);
            uart0_sendstring(" F | Min: ");
            send_float(min_temp);
            uart0_sendstring(" C | Max: ");
            send_float(max_temp);
            uart0_sendstring(" C\r\n");

            if (temp_c > 40.0) {
                uart0_sendstring("WARNING: High Temperature!\r\n");
            }
        }

        if (uart0_available()) {
            char c = uart0_getchar();
            if (c == '\r' || c == '\n') {
                cmd[cmd_index] = '\0';
                if (strcmp(cmd, "RESET") == 0) {
                    min_temp = 100.0;
                    max_temp = 0.0;
                    uart0_sendstring("Min/Max reset.\r\n");
                } else {
                    uart0_sendstring("Unknown command.\r\n");
                }
                cmd_index = 0;
            } else if (cmd_index < sizeof(cmd) - 1) {
                cmd[cmd_index++] = c;
            }
        }

        delay_ms(500);
    }
}
