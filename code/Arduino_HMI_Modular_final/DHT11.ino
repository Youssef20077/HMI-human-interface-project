#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "DHT11.h"
#define DHT_PIN 0b00001000

static uint8_t DHT11_WaitLevel(uint8_t high, uint16_t timeout_ticks)
{
    TCNT1 = 0;
    while (TCNT1 < timeout_ticks)
    {
        if (((PIND & DHT_PIN) != 0) == high) return 1;
    }
    return 0;
}

uint8_t DHT11_ReadHumidity(uint8_t *humidity)
{
    uint8_t data[5] = {0, 0, 0, 0, 0};
    uint8_t result = 0;
    DDRD |= DHT_PIN;
    PORTD &= ~DHT_PIN;
    _delay_ms(20);
    PORTD |= DHT_PIN;
    _delay_us(30);
    DDRD &= ~DHT_PIN;
    PORTD |= DHT_PIN;

    uint8_t saved_sreg = SREG;
    cli();
    TCCR1A = 0b00000000;
    TCCR1B = 0b00000010;

    if (!DHT11_WaitLevel(0, 400)) goto finish;
    if (!DHT11_WaitLevel(1, 400)) goto finish;
    if (!DHT11_WaitLevel(0, 400)) goto finish;

    for (uint8_t bit = 0; bit < 40; bit++)
    {
        if (!DHT11_WaitLevel(1, 300)) goto finish;
        TCNT1 = 0;
        if (!DHT11_WaitLevel(0, 300)) goto finish;
        if (TCNT1 > 100) data[bit / 8] |= (0b10000000 >> (bit % 8));
    }

    if ((uint8_t)(data[0] + data[1] + data[2] + data[3]) == data[4])
    {
        *humidity = data[0];
        result = 1;
    }
finish:
    TCCR1B = 0b00000000;
    SREG = saved_sreg;
    return result;
}
