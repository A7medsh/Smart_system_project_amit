#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL 
#endif

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "Keypad_config.h"
#include "Keypad_interface.h"
#include "ADC_interface.h"
#include "LM35_ADC.h"
#include "LDR_interface.h"
#include "TIMER_INTERFACE.h"
#include "House_System.h"

#include <util/delay.h> 
#include <string.h>     

int pinEntered = 0, pinCorrect = 0, Door_state = 0, light_state = 0, failed_count = 0;
int Auto_Light_flag = 0;

void houseSystem(void)
{
    char enteredPin[5];

    while (1)
    {

        if (!pinEntered)
        {

            LCD_voidClearScreen();
            LCD_voidGoToRowColumn(0, 0);
            LCD_voidSendString("PIN:");

            for (int i = 0; i < 4; i++)
            {
                u8 key;

                do
                {
                    key = KPD_VidGetPressedKey();
                } while (key == KPD_NOT_Pressed); 
                enteredPin[i] = key;
                LCD_voidSendData('*'); 
            }

            enteredPin[4] = '\0'; 

            
            pinEntered = 1;
        }

        if (strcmp(enteredPin, "1234") == 0 || pinCorrect == 1)
        {
            LM35_Motor_Buzzer();

            pinCorrect = 1;
            DIO_VidSetPinValue(Port_B, Pin5, PinHigh); 

            LCD_voidClearScreen();

            LCD_voidSendString("1-Temp 2-Lock");
            LCD_voidGoToRowColumn(1, 0);
            LCD_voidSendString("3-Lights 4-more.");

            u8 selectedOption, second_screen_option;

            while (1)
            {

                do
                {
                    LM35_Motor_Buzzer();
                    selectedOption = KPD_VidGetPressedKey();
                } while (selectedOption == KPD_NOT_Pressed);

                switch (selectedOption)
                {
                case '1':
                    LCD_voidClearScreen();
                    LCD_voidSendString("Temprature : ");
                    LCD_voidPrintNumber(LM35_ADC_Get_Temp());
                    LCD_voidSendString(" C");
                    _delay_ms(1000);
                    LCD_voidClearScreen();
                    houseSystem();
                    break;

                case '2':
                    LCD_voidClearScreen();
                    if (Door_state == 0)
                    {
                        Door_state = 1;
                        DIO_VidSetPinValue(Port_B, Pin4, PinHigh);
                        LCD_voidSendString("Door opened. ");
                        _delay_ms(500);
                        houseSystem();
                    }
                    else
                    {
                        Door_state = 0;
                        DIO_VidSetPinValue(Port_B, Pin4, PinLow);
                        LCD_voidSendString("Door Closed. ");
                        _delay_ms(500);
                        houseSystem();
                    }
                    break;

                case '3':

                    LCD_voidClearScreen();

                    if (light_state == 0)
                    {
                        light_state = 1;
                        DIO_VidSetPinValue(Port_B, Pin2, PinHigh);
                        LCD_voidSendString("Lights ON.");
                        _delay_ms(500);
                        houseSystem();
                    }
                    else
                    {
                        light_state = 0;
                        DIO_VidSetPinValue(Port_B, Pin2, PinLow);
                        LCD_voidSendString("Lights Off.");
                        _delay_ms(500);
                        houseSystem();
                    }
                    break;

                case '4':

                    while (1)
                    {
                        LCD_voidClearScreen();

                        LCD_voidSendString("1-AutoLight 2-Lo");
                        LCD_voidGoToRowColumn(1, 0);
                        LCD_voidSendString("gout 3-back.");

                        do
                        {
                            LM35_Motor_Buzzer();
                            second_screen_option = KPD_VidGetPressedKey();
                        } while (second_screen_option == KPD_NOT_Pressed);

                        switch (second_screen_option)
                        {
                        case '1':

                            LCD_voidClearScreen();

                            if (Auto_Light_flag == 0)
                            {
                                Auto_Light_flag = 1;
                                LCD_voidSendString("Auto Lights ON.");
                                _delay_ms(500);
                            }
                            else
                            {
                                Auto_Light_flag = 0;
                                LCD_voidSendString("Auto Lights Off.");
                                _delay_ms(500);
                            }
                            break;

                        case '2':
                            pinCorrect = 0;
                            pinEntered = 0;
                            LCD_voidClearScreen();
                            LCD_voidSendString("Logging out.");
                            DIO_VidSetPinValue(Port_B, Pin5, PinLow); 
                            _delay_ms(500);
                            houseSystem();

                        case '3':
                            houseSystem();
                            break;

                        default:
                            LCD_voidClearScreen();
                            LCD_voidSendString("Invalid option");
                            _delay_ms(500);
                            LCD_voidClearScreen();
                            break;
                        }
                    }

                default:
                    LCD_voidClearScreen();
                    LCD_voidSendString("Invalid option");
                    _delay_ms(500);
                    LCD_voidClearScreen();
                    houseSystem();
                    break;
                }
            }
        }
        else
        {
            if (failed_count == 2)
            {
                LCD_voidClearScreen();
                LCD_voidSendString("You have been");
                LCD_voidGoToRowColumn(1, 0);
                LCD_voidSendString("blocked for 30s");
                _delay_ms(30000);
                pinEntered = 0;
                failed_count = 0;
                houseSystem();
            }
            else
            {
                LCD_voidClearScreen();
                LCD_voidSendString("Invalid PIN");
                _delay_ms(500);
                pinEntered = 0;
                failed_count++;
            }
        }
    }
}

void House_init()
{
    LCD_voidInit();
    KPD_VidInit();
    ADC_VidInit();
    FAST_PWM_NON_INVERTED_INIT();
    Buzzer_init();

    DIO_VidSetPinDirection(Port_B, Pin2, Output); 
    DIO_VidSetPinDirection(Port_B, Pin4, Output); 
    DIO_VidSetPinDirection(Port_B, Pin5, Output); 
}