#ifndef NVIC_H
#define NVIC_H
#include "includes.h"

//º¯Êý¶¨Òå
void MY_NVIC_PriorityGroupConfig(u8 NVIC_Group);
void MY_NVIC_Init(u8 NVIC_PreemptionPriority, u8 NVIC_SubPriority, u8 NVIC_Channel, u8 NVIC_Group);
void Ex_NVIC_Config(u8 GPIOx, u8 BITx, u8 TRIM);
#endif
