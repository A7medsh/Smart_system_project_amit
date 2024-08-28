#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_PRIVATE.h"
#include "DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <util/delay.h>

#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL 
#endif

u8 Cursor_Postion = 0;

void LCD_voidSendCommand(u8 Copy_u8Command)
{
    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, PinLow); 
    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, PinLow); 

    DIO_VidSetPortValue(LCD_DATA_PORT, Copy_u8Command); 

    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, PinHigh); 
    _delay_ms(2);                                          
    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, PinLow);  
}

void LCD_voidSendData(u8 Copy_u8Data)
{
    if (Cursor_Postion == 16)
    {
        LCD_voidGoToRowColumn(1, 0);
    }

    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, PinHigh); 
    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, PinLow);  

    DIO_VidSetPortValue(LCD_DATA_PORT, Copy_u8Data); 

    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, PinHigh); 
    _delay_ms(2);                                          
    DIO_VidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, PinLow);  

    Cursor_Postion++;
}

void LCD_voidInit(void)
{
    DIO_VidSetPortDirection(LCD_DATA_PORT, Output);
    DIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RS_PIN, Output);
    DIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_RW_PIN, Output);
    DIO_VidSetPinDirection(LCD_CTRL_PORT, LCD_E_PIN, Output);

    _delay_ms(15); 

    LCD_voidSendCommand(0x38); 
    LCD_voidSendCommand(0x0C);

    LCD_voidSendCommand(0x01); 

    _delay_ms(2);
}

void LCD_voidSendString(char *str)
{
    while (*str)
    {
        LCD_voidSendData(*str++);
    }
}

void LCD_voidGoToRowColumn(unsigned char Row, unsigned char Column)
{
    unsigned char addr = (0x40 * Row) + Column;

    LCD_voidSendCommand(0x80 | addr);
    Cursor_Postion = Row * 16 + Column;
}

void LCD_voidPrintNumber(int num)
{
    char str[16];
    int i = 0;

    if (num < 0)
    {
        str[i] = '-';
        i++;
        num = -num; 
    }

    do
    {
        str[i] = (num % 10) + 48; 
        i++;
        num /= 10;
    } while (num);

    int j = i - 1;
    for (int k = 0; k < i / 2; k++)
    {
        char temp = str[k];
        str[k] = str[j];
        str[j] = temp;
        j--;
    }

    LCD_voidSendString(str);
}

void LCD_voidSendExtraChar(struct Extra_Character copy_character)
{
    u8 CGRAM_address = 0, Iterator = 0;

    CGRAM_address = copy_character.copy_u8PatternNumber * 8;


    LCD_voidSendCommand(CGRAM_address | 0b01000000);

    for (Iterator = 0; Iterator < 8; Iterator++)
    {
        LCD_voidSendData(copy_character.copy_u8Pattern[Iterator]);
    }

    LCD_voidGoToRowColumn(copy_character.copy_u8Row, copy_character.copy_u8Column);

    LCD_voidSendData(copy_character.copy_u8PatternNumber);
}

void LCD_voidDeleteLastCharacter(void)
{
    if (Cursor_Postion > 0)
    {
        Cursor_Postion--;
        LCD_voidGoToRowColumn(Cursor_Postion / 16, Cursor_Postion % 16);

        LCD_voidSendData(' ');

        Cursor_Postion--;
        LCD_voidGoToRowColumn(Cursor_Postion / 16, Cursor_Postion % 16);
    }
}

void LCD_voidClearScreen()
{
    LCD_voidSendCommand(0x01);
    Cursor_Postion = 0;
}
