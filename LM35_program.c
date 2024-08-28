#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "LCD_interface.h"
#include "DIO_interface.h"
#include "TIMER_INTERFACE.h"
#include "LM35_ADC.h"
#include "LDR_interface.h"
#include <util/delay.h>

#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL 
#endif

int LM35_ADC_Get_Temp()
{
    u16 Digital_data;
    int temp;
    f32 voltage_step_size;

    Digital_data = ADC_u16ReadChannelSyn(channel0);

    voltage_step_size = 5.0 / 1024 * 1000; 
    temp = Digital_data * voltage_step_size; 
    temp = temp / 10;

    return temp;
}

void Buzzer_init()
{
    DIO_VidSetPinDirection(Port_B, Pin0, Output); 
}

void LM35_Motor_Buzzer()
{
    if (LM35_ADC_Get_Temp() >= 30)
    {
        DIO_VidSetPinValue(Port_B, Pin1, PinHigh); 
    }
    else
    {
        DIO_VidSetPinValue(Port_B, Pin1, PinLow); 
    }

    if (LM35_ADC_Get_Temp() < 60)
    {
        DIO_VidSetPinValue(Port_B, Pin0, PinLow); 
    }

    if (LM35_ADC_Get_Temp() >= 30 && LM35_ADC_Get_Temp() < 35)
    {
        DIO_VidSetPinValue(Port_B, Pin1, PinHigh); 

        TIMER0_Vid_SetCompMatchValue(64);
    }
    else if (LM35_ADC_Get_Temp() >= 35 && LM35_ADC_Get_Temp() < 40)
    {
        DIO_VidSetPinValue(Port_B, Pin1, PinHigh); 

        TIMER0_Vid_SetCompMatchValue(128);
    }
    else if (LM35_ADC_Get_Temp() >= 40 && LM35_ADC_Get_Temp() < 60)
    {
        DIO_VidSetPinValue(Port_B, Pin1, PinHigh); 

        TIMER0_Vid_SetCompMatchValue(255);
    }
    else if (LM35_ADC_Get_Temp() >= 60)
    {
        DIO_VidSetPinValue(Port_B, Pin0, PinHigh); 
    }

    if (Auto_Light_flag == 1)
    {
        AutoLightIntensity();
    }
}
