#ifndef __WHEELS_H
#define __WHEELS_H

#include "stm32f10x.h"                  // Device header

void Wheels_Init(void);
void forward(void);
void turn(void);
void stop(void);
void left(void);
void right(void);

#endif
