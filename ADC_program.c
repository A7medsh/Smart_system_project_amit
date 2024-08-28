#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ADC_interface.h"
#include "ADC_Private.h"
#include "ADC_config.h"

#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL
#endif

void ADC_VidInit()
{
    Set_bit(ADMUX, ADMUX_REFS0);
    Clear_bit(ADMUX, ADMUX_REFS1);


    Clear_bit(ADMUX, ADMUX_ADLAR);

    
    Set_bit(ADCSRA, ADCSRA_ADPS0);
    Set_bit(ADCSRA, ADCSRA_ADPS1);
    Set_bit(ADCSRA, ADCSRA_ADPS2);

    /* Enable ADC */
    Set_bit(ADCSRA, ADCSRA_ADEN);
}

u16 ADC_u16ReadChannelSyn(u8 Copy_u8Channel)
{
    ADMUX &= 0b11100000; // Clear MUX bits

    /* Set the channel */
    ADMUX |= Copy_u8Channel;

    
    Set_bit(ADCSRA, ADCSRA_ADSC);

    
    while (Get_bit(ADCSRA, ADCSRA_ADIF) == 0)
        ;

    
    Set_bit(ADCSRA, ADCSRA_ADIF);

    return ADCL_H;
}
