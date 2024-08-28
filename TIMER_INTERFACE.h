#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

typedef enum
{
	TIMER0_NORMAL_MODE = 0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
} et_TIMER0MODE;

typedef enum
{
	No_clock_source = 0,
	No_prescaling,
	clk_8_prescaler,
	clk_64_prescaler,
	clk_256_prescaler,
	clk_1024_prescaler,
	External_clock_fallingedge,
	External_clock_risingedge
} et_TIMER0PRESSCAELER;

typedef enum
{
	inverted,
	non_inverted
} et_TIMER0FPWM;

void TIMER0_Vid_Init(et_TIMER0MODE mode, et_TIMER0PRESSCAELER presscaler);

void TIMER0_Vid_SetCompMatchValue(u8 value);

void TIMER0_Vid_SetFpwm_Mode(et_TIMER0FPWM mode);

void TIMER0_Interrupt_Enable();

void TIMER0_Interrupt_Disable();

void FAST_PWM_NON_INVERTED_INIT();

#endif
