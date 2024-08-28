#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidSendData(u8 Copy_u8Data);

void LCD_voidInit(void);

void LCD_voidSendString(char *str);

void LCD_voidGoToRowColumn(unsigned char Row, unsigned char Column);

void LCD_voidPrintNumber(int num);

struct Extra_Character
{
    u8 *copy_u8Pattern;
    u8 copy_u8PatternNumber;
    u8 copy_u8Row;
    u8 copy_u8Column;
};
void LCD_voidSendExtraChar(struct Extra_Character copy_character);

void LCD_voidReadData(u8 *data);

void LCD_voidDeleteLastCharacter(void);

void LCD_voidClearScreen();

#endif
