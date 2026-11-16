#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#include "ADC.h"
#include "DHT11.h"
#include "Sensors.h"
#include "LED.h"
#include "Buttons.h"
#include "UART.h"

unsigned char current_sensor = 0;
unsigned int elapsed_ms = 0;

void Display_Sensor(unsigned char sensor)
{
    LCD_ClearLine(0);

    if (sensor == 0)
    {
        LCD_String("Temp:");
    }
    else if (sensor == 1)
    {
        LCD_String("Hum:");
    }
    else
    {
        LCD_String("LDR:");
    }

    if (valid[sensor])
    {
        LCD_Number(readings[sensor]);

        if (sensor == 0)
        {
            LCD_Char('C');
        }

        if (sensor == 1)
        {
            LCD_Char('%');
        }
    }
    else
    {
        LCD_String("ERR");
    }

    LCD_Position(0, 12);

    if (!valid[sensor])
    {
        LCD_String("ERR");
    }
    else if (Sensors_Alarm(sensor))
    {
        LCD_String("NOK");
    }
    else
    {
        LCD_String("OK");
    }

    LCD_ClearLine(1);
    LCD_String("LL:");
    LCD_Number(low_limit[sensor]);

    LCD_Position(1, 9);
    LCD_String("LH:");
    LCD_Number(high_limit[sensor]);
}

void setup()
{
    DDRD = (DDRD & 0b00001111) | 0b11110000;
    DDRB |= 0b00011100;
    PORTB &= 0b11111011;
    PORTD |= 0b00001000;

    LCD_Init();
    ADC_Init();
    Sensors_Init();
    LED_Init();
    UART_Init();
    Buttons_Init();

    LCD_Clear();
    LCD_String("System Starting");
    _delay_ms(1000);

    Sensors_UpdateAnalog();
    Sensors_UpdateHumidity();
    LED_Update();
    Display_Sensor(current_sensor);
}

void loop()
{
    Sensors_UpdateAnalog();
    Buttons_Update(current_sensor);
    LED_Update();

    if (elapsed_ms >= 3000)
    {
        elapsed_ms = 0;
        current_sensor++;

        if (current_sensor >= 3)
        {
            current_sensor = 0;
        }

        Sensors_UpdateHumidity();
        LED_Update();
    }

    Display_Sensor(current_sensor);
    _delay_ms(100);
    elapsed_ms += 100;
}

