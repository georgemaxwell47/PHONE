#ifndef __TIMER_H__
#define __TIMER_H__
#include "gpio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "ssd1306.h"
#include "stdio.h"
#include "clk.h"
#include "painter.h"
#include "keypad_satr.h"
#include "snake.h"

void pishzamine(uint16_t CURRENT_TIME_MIN ,uint16_t CURRENT_TIME_HOUR,uint16_t CURRENT_TIME_SECEND,uint16_t ALARM_ALARMHOUR,uint16_t ALARM_ALARMMIN,int ALARM_ALARMSEC);
int Mosleh(uint16_t m,uint8_t keypad_adad,uint8_t BUFF1,uint8_t BUFF2);
#endif 

