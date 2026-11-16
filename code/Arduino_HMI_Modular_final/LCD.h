#ifndef LCD_H
#define LCD_H
#include <stdint.h>
void LCD_Init(void);
void LCD_Clear(void);
void LCD_Command(uint8_t command);
void LCD_Char(uint8_t value);
void LCD_String(const char *text);
void LCD_Number(uint16_t number);
void LCD_Position(uint8_t row, uint8_t column);
void LCD_ClearLine(uint8_t row);
#endif
