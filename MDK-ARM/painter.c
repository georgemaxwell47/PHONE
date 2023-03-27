#include "clk.h"
#include "ssd1306.h"
#include "stdio.h"

void painter__ (int SET_X,int SET_Y,char * BUFF,FontDef font){
	ssd1306_SetCursor(SET_X,SET_Y);
	ssd1306_WriteString(BUFF,font,White);
	
}
void rasm_string_with_char(int len,char* INPUT){
	for(int i=0;i<=len;i++){
			ssd1306_SetCursor(i*6,20);
			ssd1306_WriteChar(INPUT[i],Font_6x8,White);
		}
}
