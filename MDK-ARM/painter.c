#include "clk.h"
#include "ssd1306.h"
#include "stdio.h"

void painter__ (int SET_X,int SET_Y,char * BUFF,FontDef font){
	ssd1306_SetCursor(SET_X,SET_Y);
	ssd1306_WriteString(BUFF,font,White);
}
