#include "calender.h"
#include "painter.h"
#include "ssd1306.h"
#include "stdio.h"
#include "string.h"
#include "stdbool.h"

void namayesh (int day,int mounth,int year,int weekday){
	char BUFF[30];
//	if(day == 31){
//		mounth++;
//		day=1;
//		weekday ++;
//	}
//	if(weekday == 8){
//		weekday =1;
//	}
//	if(mounth == 13){
//		mounth =1;
//		year ++;
//	}
	painter__(0,50,"M",Font_6x8);
	sprintf (BUFF,"%d / %d / %d",day,mounth,year);
	painter__(10,20,BUFF,Font_6x8);
	if(weekday == 1){
		strcpy(BUFF,"SUN");
	}
	else if(weekday == 2){
		strcpy(BUFF,"MON");
	}
	else if(weekday == 3){
		strcpy(BUFF,"TUES");
	}
	else if(weekday == 4){
		strcpy(BUFF,"WED");
	}
	else if(weekday == 5){
		strcpy(BUFF,"THURS");
	}
	else if(weekday == 6){
		strcpy(BUFF,"FRI");
	}
	else if(weekday == 7){
		strcpy(BUFF,"SAT");
	}
	painter__(10,30,BUFF,Font_6x8);
}
