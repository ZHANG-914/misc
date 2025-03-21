#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H

#include "includes.h"

void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch );
void USARTSendString(USART_TypeDef * pUSARTx,char* String);
void ShortTo0xString(char *str, short x);

#endif
