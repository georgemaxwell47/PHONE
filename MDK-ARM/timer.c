#include "timer.h"
#include "gpio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "ssd1306.h"
#include "stdio.h"
#include "clk.h"
#include "painter.h"
#include "keypad_satr.h"
#include "snake.h"
uint8_t EDIT_TIME_RESULTHOUR = 0;
uint8_t EDIT_TIME_RESULTMIN = 0;
void pishzamine(uint16_t CURRENT_TIME_MIN ,uint16_t CURRENT_TIME_HOUR,uint16_t CURRENT_TIME_SECEND,uint16_t ALARM_ALARMHOUR,uint16_t ALARM_ALARMMIN,int ALARM_ALARMSEC){
	clk_menu(CURRENT_TIME_MIN,CURRENT_TIME_HOUR,CURRENT_TIME_SECEND,ALARM_ALARMHOUR,ALARM_ALARMMIN,ALARM_ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		clk_TIM(CURRENT_TIME_MIN,CURRENT_TIME_HOUR,CURRENT_TIME_SECEND);
}
int Mosleh(uint16_t m,uint8_t keypad_adad,uint8_t BUFF1,uint8_t BUFF2){
	//uint8_t BUFF1=0,BUFF2=0;
	
	if(keypad_adad<=9 && m == 0){
			BUFF1 = keypad_adad;
			keypad_adad = 16;
			m = 1;
		}
		else if(keypad_adad<=9 &&m == 1){
			BUFF2 = keypad_adad;
			keypad_adad = 16;
			m = 0;
		}
		return 10*BUFF1 + BUFF2;
}
