#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"
#define LCD_RS 0b00010000
#define LCD_EN 0b00001000

static void LCD_Pulse(void)
{
    PORTB |= LCD_EN;
    _delay_us(2);
    PORTB &= ~LCD_EN;
    _delay_us(50);
}

static void LCD_Nibble(uint8_t value)
{
    PORTD = (PORTD & 0b00001111) | (value & 0b11110000);
    LCD_Pulse();
}

void LCD_Command(uint8_t command)
{
    PORTB &= ~LCD_RS;
    LCD_Nibble(command);
    LCD_Nibble(command << 4);
    _delay_ms(2);
}

void LCD_Char(uint8_t value)
{
    PORTB |= LCD_RS;
    LCD_Nibble(value);
    LCD_Nibble(value << 4);
}

void LCD_Init(void)
{
    _delay_ms(50);
    PORTB &= ~LCD_RS;
    LCD_Nibble(0b00110000);
    _delay_ms(5);
    LCD_Nibble(0b00110000);
    _delay_us(150);
    LCD_Nibble(0b00110000);
    LCD_Nibble(0b00100000);
    LCD_Command(0b00101000);
    LCD_Command(0b00001100);
    LCD_Command(0b00000110);
    LCD_Clear();
}

void LCD_Clear(void) { LCD_Command(0b00000001); }
void LCD_String(const char *text) { while (*text) LCD_Char(*text++); }

void LCD_Number(uint16_t number)
{
    char digits[6];
    uint8_t count = 0;
    do { digits[count++] = (number % 10) + '0'; number /= 10; } while (number);
    while (count) LCD_Char(digits[--count]);
}

void LCD_Position(uint8_t row, uint8_t column)
{
    LCD_Command((row ? 0b11000000 : 0b10000000) + column);
}

void LCD_ClearLine(uint8_t row)
{
    LCD_Position(row, 0);
    LCD_String("                ");
    LCD_Position(row, 0);
}
