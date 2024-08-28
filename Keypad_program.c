#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Keypad_config.h"
#include "Keypad_interface.h"

#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL 
#endif

void KPD_VidInit()
{
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL1PIN, Output);
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL2PIN, Output);
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL3PIN, Output);
    DIO_VidSetPinDirection(KPD_PORT, KPD_COL4PIN, Output);

    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW1PIN, Input);
    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW2PIN, Input);
    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW3PIN, Input);
    DIO_VidSetPinDirection(KPD_PORT, KPD_ROW4PIN, Input);

    // Set the initial value of the port to all high
    DIO_VidSetPortValue(KPD_PORT, 0xFF);
}

u8 KPD_VidGetPressedKey()
{
    u8 Key_Pressed_Value = KPD_NOT_Pressed; 
    u8 Key_Pressed_State;                   
    static u8 Column_arr[] = {KPD_COL1PIN, KPD_COL2PIN, KPD_COL3PIN, KPD_COL4PIN};
    static u8 Row_arr[] = {KPD_ROW1PIN, KPD_ROW2PIN, KPD_ROW3PIN, KPD_ROW4PIN};
    static u8 Local_Keypad_arr[KPD_Row_Number][KPD_Column_Number] = KPD_Arr;

    for (u8 Column = 0; Column < KPD_Column_Number; Column++)
    {
        DIO_VidSetPinValue(KPD_PORT, Column_arr[Column], PinLow);

        for (u8 Row = 0; Row < KPD_Row_Number; Row++)
        {
            DIO_VidGetPinValue(KPD_PORT, Row_arr[Row], &Key_Pressed_State);

            if (Key_Pressed_State == PinLow) 
            {
                Key_Pressed_Value = Local_Keypad_arr[Row][Column];

                while (Key_Pressed_State == PinLow) 
                {
                    DIO_VidGetPinValue(KPD_PORT, Row_arr[Row], &Key_Pressed_State);
                }
                return Key_Pressed_Value;
            }
        }
        DIO_VidSetPinValue(KPD_PORT, Column_arr[Column], PinHigh);
    }

    return Key_Pressed_Value;
}
