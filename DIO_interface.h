#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

typedef enum
{
    Port_A,
    Port_B,
    Port_C,
    Port_D
} et_Port;

typedef enum
{
    Pin0,
    Pin1,
    Pin2,
    Pin3,
    Pin4,
    Pin5,
    Pin6,
    Pin7
} et_Pin;

typedef enum
{
    Input,
    Output
} et_Direction;

typedef enum
{
    PinLow,
    PinHigh
} et_Status;

void DIO_VidSetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);

void DIO_VidSetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);

void DIO_VidGetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 *pu8Data);

void DIO_VidSetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);

void DIO_VidSetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);

void DIO_VidGetPortValue(u8 Copy_u8Port, u8 *pu8Data);

#endif