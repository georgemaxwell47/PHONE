#ifndef __CLK_H__
#define __CLK_H__
#include "ssd1306.h"
#include "stdio.h"
void clk_preview (int CURRENT_TIME_MIN,int CURRENT_TIME_HOUR,int CURRENT_TIME_SEC,int ALARM_ALARMHOUR,int ALARM_ALARMMIN,int ALARM_ALARMSEC);
void clk_menu (int CURRENT_TIME_MIN,int CURRENT_TIME_HOUR,int CURRENT_TIME_SEC,int ALARM_ALARMHOUR,int ALARM_ALARMMIN,int ALARM_ALARMSEC);
void clk_TIM (int CURRENT_TIME_MIN,int CURRENT_TIME_HOUR,int CURRENT_TIME_SEC);

void clk_edit (int CURRENT_TIME_MIN,int CURRENT_TIME_HOUR,int CURRENT_TIME_SEC);
#endif 

