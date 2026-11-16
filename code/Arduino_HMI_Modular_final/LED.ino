#include <avr/io.h>
#include <stdint.h>
#include "LED.h"
#include "Sensors.h"
void LED_Init(void)
{
    DDRB |= 0b00000100;
    PORTB &= 0b11111011;
}
void LED_Update(void)
{
    uint8_t alarm = 0;
    for (uint8_t i = 0; i < 3; i++)
        if (Sensors_Alarm(i)) alarm = 1;
    if (alarm) PORTB |= 0b00000100;
    else PORTB &= 0b11111011;
}
