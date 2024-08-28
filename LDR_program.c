#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "DIO_interface.h"
#include "LDR_interface.h"

#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL 
#endif


void AutoLightIntensity()
{
    u16 value = ADC_u16ReadChannelSyn(channel1); 
    u8 percentage = 100 - (((float)value / 1024) * 100); 

    if (percentage > 50)
    {
        light_state = 1;
        DIO_VidSetPinValue(Port_B, Pin2, PinHigh); 
    }
    else
    {
        light_state = 0;
        DIO_VidSetPinValue(Port_B, Pin2, PinLow); 
    }
}