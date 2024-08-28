#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "TIMER_INTERFACE.h"
#include "TIMER_PRIVATE.h"

#ifdef F_CPU
#undef F_CPU
#define F_CPU 1000000UL 
#endif

void TIMER0_Vid_Init(et_TIMER0MODE mode, et_TIMER0PRESSCAELER prescaler)
{
	switch (mode)
	{
	case TIMER0_NORMAL_MODE:
		Clear_bit(TCCR0, TCCR0_WGM00);
		Clear_bit(TCCR0, TCCR0_WGM01);
		break;

	case TIMER0_CTC_MODE:
		Clear_bit(TCCR0, TCCR0_WGM00);
		Set_bit(TCCR0, TCCR0_WGM01);
		break;

	case TIMER0_FASTPWM_MODE:
		Set_bit(TCCR0, TCCR0_WGM00);
		Set_bit(TCCR0, TCCR0_WGM01);
		break;

	case TIMER0_PHASECORRECT_MODE:
		Set_bit(TCCR0, TCCR0_WGM00);
		Clear_bit(TCCR0, TCCR0_WGM01);
		break;
	}

	TCCR0 = TCCR0 & 0xf8;	   
	TCCR0 = TCCR0 | prescaler;
}

void TIMER0_Vid_SetCompMatchValue(u8 value)
{
	OCR0 = value; 
}

void TIMER0_Vid_SetFpwm_Mode(et_TIMER0FPWM mode)
{
	switch (mode)
	{
	case inverted:
		Set_bit(TCCR0, TCCR0_COM01);
		Set_bit(TCCR0, TCCR0_COM00);
		break;

	case non_inverted:
		Set_bit(TCCR0, TCCR0_COM01);
		Clear_bit(TCCR0, TCCR0_COM00);
		break;
	}
}

void TIMER0_Interrupt_Enable()
{
	Set_bit(TIMSK, TIMSK_TOIE0); 

void TIMER0_Interrupt_Disable()
{
	Clear_bit(TIMSK, TIMSK_TOIE0); 
}

void FAST_PWM_NON_INVERTED_INIT()
{												  
	DIO_VidSetPinDirection(Port_B, Pin1, Output); 
	DIO_VidSetPinDirection(Port_B, Pin3, Output); 

	TIMER0_Vid_Init(TIMER0_FASTPWM_MODE, clk_1024_prescaler);
	TIMER0_Vid_SetFpwm_Mode(non_inverted);
}