
#include <avr/io.h>
#include <util/delay.h>
#include "Buttons.h"
#include "Sensors.h"
#include "UART.h"

unsigned char button1 = 0;
unsigned char button2 = 0;
unsigned char selected_limit = 0;

void Buttons_Init()
{
    DDRB &= 0b11111100;
    PORTB &= 0b11111100;
}

void Buttons_Update(unsigned char selected_sensor)
{
    unsigned char current1 = 0;
    unsigned char current2 = 0;

    if (PINB & 0b00000001)
    {
        current1 = 1;
    }

    if (PINB & 0b00000010)
    {
        current2 = 1;
    }

    if (current1 && !button1)
    {
        UART_String("Button 1: PRESSED\r\n");
    }
    else if (!current1 && button1)
    {
        UART_String("Button 1: NOT PRESSED\r\n");
    }

    if (current2 && !button2)
    {
        UART_String("Button 2: PRESSED\r\n");
    }
    else if (!current2 && button2)
    {
        UART_String("Button 2: NOT PRESSED\r\n");
    }

    if ((current1 || current2) && !button1 && !button2)
    {
        _delay_ms(50);

        current1 = (PINB & 0b00000001) != 0;
        current2 = (PINB & 0b00000010) != 0;

        if (current1 && current2)
        {
            if (selected_limit == 0)
            {
                selected_limit = 1;
            }
            else
            {
                selected_limit = 0;
            }
        }
        else if (current1)
        {
            if (selected_limit == 0)
            {
                if (high_limit[selected_sensor] < 1023)
                {
                    high_limit[selected_sensor]++;
                }
            }
            else
            {
                if (low_limit[selected_sensor] + 1 < high_limit[selected_sensor])
                {
                    low_limit[selected_sensor]++;
                }
            }
        }
        else if (current2)
        {
            if (selected_limit == 0)
            {
                if (high_limit[selected_sensor] > low_limit[selected_sensor] + 1)
                {
                    high_limit[selected_sensor]--;
                }
            }
            else
            {
                if (low_limit[selected_sensor] > 0)
                {
                    low_limit[selected_sensor]--;
                }
            }
        }
    }

    button1 = current1;
    button2 = current2;
}
