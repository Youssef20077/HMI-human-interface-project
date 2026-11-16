#include <avr/io.h>
#include "ADC.h"
#include <util/delay.h>
void ADC_Init(void)
{
    ADMUX = 0b01000000;
    ADCSRA = 0b10000111;
}
uint16_t ADC_Read(uint8_t channel)
{
    ADMUX = 0b01000000 | (channel & 0b00001111);
    _delay_us(15);
    ADCSRA |= 0b01000000;
    while (ADCSRA & 0b01000000) {}
    return ADC;
}
uint16_t ADC_Average(uint8_t channel)
{
    uint32_t sum = 0;
    ADC_Read(channel);
    for (uint8_t i = 0; i < 16; i++) sum += ADC_Read(channel);
    return (uint16_t)(sum / 16);
}
