#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H


#define TCNT0 *((volatile u8 *)0x52)

#define TCCR0 *((volatile u8 *)0x53)

#define TCCR0_WGM00 6

#define TCCR0_WGM01 3

#define TCCR0_CS00 0

#define TCCR0_CS01 1

#define TCCR0_CS02 2

#define OCR0 *((volatile u8 *)0x5c)

#define TIMSK *((volatile u8 *)0x59)

#define TIMSK_OCIE0 1

#define TIMSK_TOIE0 0

#define TCCR0_COM01 5

#define TCCR0_COM00 4

#endif
