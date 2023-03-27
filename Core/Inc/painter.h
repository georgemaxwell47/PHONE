#ifndef __painter__
#define __painter_H__
#include "ssd1306.h"
#include "stdio.h"
void painter__ (int SET_X,int SET_Y,char * BUFF,FontDef font);
void rasm_string_with_char(int len,char* INPUT);
#endif 
