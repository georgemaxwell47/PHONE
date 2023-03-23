#include "gpio.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "stdlib.h"
#include "stdio.h"
#include "snake.h"

#define max_tol_mar 111
#define x_avali 0
#define y_avali 8
#define tedad_avali 1
#define n 1

void i2c_send(void);
void header(void);
void gameover(void);
void khoshamad(void);

int tedad=n;
uint8_t eep_cntr=10;
char score=0;
char buf ;
struct randomm{
	uint8_t x;
	uint8_t y;
}random;

struct flag {
	int state;
	int step;
	uint8_t rec_snake_app;
	int dly;
	uint8_t jahat;
	uint8_t gameover;
};
struct flag flg ={0,0,0,1000,0,0};

struct makanm {
	int x;
	int y;
}makan[max_tol_mar];

struct jayeize{
	int x;
	int y;
};
struct jayeize makan_qarch_jadid = {0,8};

struct jayeize_fli{
	int x;
	int y;
};
struct jayeize makan_qarch_feli = {0,0};

int makan_qarch_jadid_140 (int makan_qarch_jadid_x){
	makan_qarch_jadid_x+=6;
		if(makan_qarch_jadid_x>=121){
			makan_qarch_jadid_x = 0;
		}
		return makan_qarch_jadid_x;
}

int makan_qarch_jadid_146 (int makan_qarch_jadid_y){
	makan_qarch_jadid.y+=8;
		if(makan_qarch_jadid.y>=53){
			makan_qarch_jadid.y = 0;
		}
}
int HAL_GPIO_EXTI_Callback_155 (uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_6 && flg.jahat != 1){ // & flg.state == 
		flg.state = 4;
	}
	if(GPIO_Pin == GPIO_PIN_7 && flg.jahat != 3){
		flg.state = 2;
	}
	if(GPIO_Pin == GPIO_PIN_1 && flg.jahat != 2){
		flg.state = 3;
	}
	if(GPIO_Pin == GPIO_PIN_0 && flg.jahat != 4){
		flg.state = 1;
	}
}

void main_176(void){
	makan_qarch_feli.x = (rand()%20)*6;
	makan_qarch_feli.y = (rand()%6)*8;
	makan[0].x=x_avali;
	makan[0].y=y_avali;
	ssd1306_Init();
	i2c_send();
}
void header(void){
	ssd1306_Fill(Black);
	if(flg.state==1 || flg.state==2 || flg.state ==3 || flg.state==4){
		for(int i=tedad;i>0;--i){
				makan[i].x=makan[i-1].x;
				makan[i].y=makan[i-1].y;
			}
		if (flg.state==1){
			makan[0].x=makan[0].x+6;
			flg.jahat=1;
		}
		if (flg.state==2){
			makan[0].y=makan[0].y-8;
			flg.jahat=2;
		}
		if (flg.state==3){
			makan[0].y=makan[0].y+8;
			flg.jahat=3;
		}
		if (flg.state==4){
			makan[0].x=makan[0].x-6;
			flg.jahat=4;
		}
		
		for(int i=1;i<=tedad;i++){
			if(makan[i].x == makan[0].x && makan[i].y == makan[0].y){
				gameover();
			}
		}
	}
	
		if(makan[0].x == makan_qarch_feli.x && makan[0].y == makan_qarch_feli.y){
			score++;
			random.x = makan_qarch_jadid.x;
			random.y = makan_qarch_jadid.y;
			for(int i=1;i<=tedad;i++){
				if(makan[i].x == random.x && makan[i].y == random.y){
					i=1;
					random.x = (rand()%20)*6;
					random.y = (rand()%6)*8;
				}
			}
			makan_qarch_feli.x = random.x;
			makan_qarch_feli.y = random.y;
			tedad ++;
		}
		
		for(int i=0;i<tedad;i++){
			ssd1306_SetCursor(makan[i].x,makan[i].y);
			ssd1306_WriteString(".",Font_6x8 ,White);
		}
		
		ssd1306_SetCursor(makan_qarch_feli.x,makan_qarch_feli.y);
		ssd1306_WriteString(".",Font_6x8,White);
		
		
		ssd1306_UpdateScreen();
		
		HAL_Delay(flg.dly);
		
		if(makan[0].x >119 || makan[0].x <0 || makan[0].y>53 || makan[0].y<0){
			gameover();
		}
}
void i2c_send(void){
	if(flg.step == 0){
		khoshamad();
	}
	if(flg.step == 1){
		header();
	}
//		ssd1306_UpdateScreen();
//		HAL_Delay(1000);
}
void khoshamad(void){
		ssd1306_Fill(Black);
		flg.state=0;
		ssd1306_SetCursor(0,0);
		HAL_Delay(1);
		ssd1306_WriteString("Easy -> Down",Font_6x8 ,White);
		ssd1306_SetCursor(0,40);
		ssd1306_WriteString("Hard -> Up",Font_6x8 ,White);
		ssd1306_UpdateScreen();
		if(flg.state==2 || flg.state==3){
			if (flg.state==2){
				flg.dly = 100;
			}
			if (flg.state==3){
				flg.dly = 500;
			}
			flg.step=1;
			flg.state=0;
		}
		
}
void gameover(void){
	for(int i=0;i<=4;i++){
		ssd1306_Fill(Black);
		HAL_Delay(350);
		ssd1306_SetCursor(0,0);
		HAL_Delay(1);
		ssd1306_WriteString("Game Over",Font_6x8  ,White);
//		sprintf(buf,"score = %d",score);
		
		buf = score/100 + '0';
		ssd1306_SetCursor(0,40);
		ssd1306_WriteString("Your Score",Font_6x8  ,White);
		ssd1306_SetCursor(73,40);
		ssd1306_WriteChar(buf, Font_6x8 , White);
		
		buf = (score%100)/10 + '0';
		ssd1306_SetCursor(80,40);
		ssd1306_WriteChar(buf, Font_6x8 , White);
		
		buf = (score%10) + '0';
		ssd1306_SetCursor(87,40);
		ssd1306_WriteChar(buf, Font_6x8 , White);
		
		ssd1306_UpdateScreen();
		
	}
	tedad=1;
	makan[0].x=0;
	makan[0].y=8;
	flg.state =0;
	flg.step =0;
	flg.jahat=0;
	score=0;
	i2c_send();
}