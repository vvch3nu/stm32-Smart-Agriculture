#ifndef __FLASH_H
#define __FLASH_H 			   

#include "stm32f10x.h"                  // Device header
 

void FLASH_W(u32 add,u16 dat,u16 dat2,u16 dat3,u16 dat4,u16 dat5,u16 dat6);

u16 FLASH_R(u32 add);

#endif





























