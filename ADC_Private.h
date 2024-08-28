#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

#define ADMUX *((volatile u8 *)0x27)

#define ADCSRA *((volatile u8 *)0x26)

#define ADCL_H *((volatile u16 *)0x24)

#endif
