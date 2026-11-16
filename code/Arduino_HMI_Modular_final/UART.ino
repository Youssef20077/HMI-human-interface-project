#include <avr/io.h>
#include "UART.h"

void UART_Init(void)
{
    UBRR0H = 0b00000000;
    UBRR0L = 103;
    UCSR0A = 0b00000000;
    UCSR0B = 0b00001000;
    UCSR0C = 0b00000110;
}

void UART_Char(char character)
{
    while ((UCSR0A & 0b00100000) == 0)
    {
    }
    UDR0 = character;
}

void UART_String(const char *message)
{
    while (*message != 0)
    {
        UART_Char(*message);
        message++;
    }
}
