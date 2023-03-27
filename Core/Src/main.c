/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "string.h"
#include "stdlib.h"
#include "ssd1306.h"
#include "stdio.h"
#include "clk.h"
#include "painter.h"
#include "keypad_satr.h"
#include "snake.h"
#include "timer.h"
#include "calender.h"
#include "call.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define max_tol_mar 111
#define x_avali 0
#define y_avali 8
#define tedad_avali 1
#define n 0

#define LEDRED_OFF HAL_GPIO_WritePin(GPIOA,LEDRED_Pin,GPIO_PIN_RESET);
#define LEDRED_ON HAL_GPIO_WritePin(GPIOA,LEDRED_Pin,GPIO_PIN_SET);

#define PREVIEW_L 0
#define MENU_L 1
#define SNAKE_L 2
#define MENU_TIM_L 3
#define TIME_L 4
#define MENU_CALENDER_L 5
#define CALENDER_L 6
#define MENU_CALL_L 7
#define CALL_L 8
#define RING 9
#define SMS_L 10
#define F_SMS_L 11
#define NOTE_SMS_L 12
#define MY_RING_L 13
#define R_SMS_L 14
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
struct sms_r{
	uint8_t mohtava_counter;
	char number[11];
	char tarikh[8];
	char mohtava[10];
	char time[5];
};struct sms_r RING_SMS={0};
struct sm{
	uint8_t i;
	char elhaq[21];
	char sarehambandi[13];
	char CBUFF;
	uint8_t arr[10];
	char BUFF [11];
};struct sm SMSS={0,"AT+CMGS=","\""};
struct Urt{
	uint8_t counter;
	uint8_t cntlz;
	uint8_t enter;
	char CHAR_BUFF;
	char BUFF[200];
};struct Urt UART={0,0x1a,0x0d};
struct cal{
	uint8_t i;
	char elhaq[15];
	char sarehambandi;
	char CBUFF;
	int arr[10];
	char BUFF [10];
	};struct cal CAL={0,"ATD",';'};
struct date{
	uint8_t mounth;
	uint8_t day;
	int year;
	uint8_t weekday;
};struct date DATE = {12,30,2000,1};

struct keypad{
	uint8_t Satr_Peyma;
	uint8_t adad;
	bool SOTON_1_ON;
	bool SOTON_2_ON;
	bool SOTON_3_ON;
	bool SOTON_4_ON;
	bool CHANGE_SATR_ALLOW;
	uint8_t negahdari_shomar;
	char namayesh;
	uint8_t set_x;
	uint8_t set_y;
	int counter[10];
	char negahdari[60];
};struct keypad key_pad = {1,0,false,false,false,false,true,0,NULL,0,20};

struct flag {
	bool nimsec;
	bool nimsec2;
	bool shishnimsec;
	bool ring;
	bool keypad_tim;
	bool m;
	bool sabt;
	bool allow_namayesh;
	bool test_bar1;
};struct flag flg = {false,false,false,false,false,false,false,false,true};

struct CURRENT_TIM {
	uint16_t SECEND;
	uint16_t MIN;
	uint16_t HOUR;
};struct CURRENT_TIM CURRENT_TIME = {50,59,23};

struct ED_TIM {
	uint8_t HOUR1;
	uint8_t HOUR2;
	uint8_t MIN1;
	uint8_t MIN2;
	uint8_t SEC1;
	uint8_t SEC2;
	uint8_t RESULTHOUR;
	uint8_t RESULTMIN;
	uint8_t RESULTSEC;
	uint8_t M;
	uint8_t ALOOWCHANGE;
	bool ALARMMODE;
};struct ED_TIM EDIT_TIME ={0,0,0,0,0,0,0,0,0,false} ;
struct ALAR {
	uint8_t ALARMHOUR;
	uint8_t ALARMMIN;
	uint8_t ALARMSEC;
};struct ALAR ALARM = {26,0,0};
// SNAKE //
int tedad=n;
uint8_t eep_cntr=10;
char score=0;
char buf ;
struct randomm{
	uint8_t x;
	uint8_t y;
}random;

struct flag2 {
	int state;
	int step;
	uint8_t rec_snake_app;
	int dly;
	uint8_t jahat;
	uint8_t gameover;
};struct flag2 flg2 ={0,0,0,1000,0,0}; //ESM FLG AVAZ SHOD
struct makanm {
	int x;
	int y;
}makan[max_tol_mar];

struct jayeize{
	int x;
	int y;
};struct jayeize makan_qarch_jadid = {0,8};
struct jayeize_fli{
	int x;
	int y;
};struct jayeize makan_qarch_feli = {0,0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void PREVIEW (void);
void MENU (void);
void SNAKE (void);
void MENU1 (void);
void TIME (void);
void MENU2 (void);
void CALENDER (void);
void MENU3(void);
void CALL (void);
void FRING (void);
void IRING (void);
void menu4 (void);
void sms_ersal(char *bufer);
void sms (void);
void note_sms(void);
void my_ring(void);
void r_sms(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint16_t leyer = 0;
int timer_shomar = 0;
///////////////////////////
//////// INTRUPT /////////
//////////////////////////
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		makan_qarch_jadid.y+=8;
		if(makan_qarch_jadid.y>=53){
			makan_qarch_jadid.y = 0;
		}
	}
	
	if(htim->Instance == TIM1){
		flg.nimsec = true;
		flg.nimsec2 = true;
		flg.keypad_tim = true;
		if(timer_shomar == 1){
			timer_shomar = 0;
		}
		else if(timer_shomar == 0){
			timer_shomar = 1;
			if(CURRENT_TIME.SECEND == 59){
			CURRENT_TIME.SECEND = 0;
			CURRENT_TIME.MIN ++;
		}else{
			CURRENT_TIME.SECEND++;
		}
		if(CURRENT_TIME.MIN == 60){
			CURRENT_TIME.MIN = 0;
			CURRENT_TIME.HOUR ++;
		}
		if(CURRENT_TIME.HOUR == 24){
			CURRENT_TIME.HOUR = 0;
			DATE.day++;
		}
		if(DATE.day == 31){
			DATE.day = 1;
			DATE.mounth++;
			DATE.weekday++;
		}
		if(DATE.mounth ==13){
			DATE.mounth=1;
			DATE.year++;
		}
		}
	}
	if(htim->Instance == TIM3){
		makan_qarch_jadid.x+=6;
		if(makan_qarch_jadid.x>=121){
			makan_qarch_jadid.x = 0;
		}
		if(key_pad.CHANGE_SATR_ALLOW){
			if(key_pad.Satr_Peyma == 1){
			}else{
			}
			if(key_pad.Satr_Peyma >= 5){
				key_pad.Satr_Peyma =1;
			}else{
				key_pad.Satr_Peyma++;
		}
	}
}
	if(htim->Instance == TIM4){
		flg.sabt = true;
	}
}	

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == KEY_RIGHT_EX_Pin || GPIO_Pin == KEY_LEFT_EX_Pin){
		if(GPIO_Pin == KEY_RIGHT_EX_Pin){
			if(leyer == PREVIEW_L){
				leyer = MENU_L;
			}
			else if(leyer == MENU_L){
				leyer = MENU_TIM_L;
			}
			else if(leyer == MENU_TIM_L){
				leyer = MENU_CALENDER_L;
			}
			else if(leyer == MENU_CALENDER_L){
				leyer = MENU_CALL_L;
			}
			else if(leyer == MENU_CALL_L){
				leyer = SMS_L;
			}
		}
		if(GPIO_Pin == KEY_LEFT_EX_Pin){
			if(leyer == MENU_L){
				leyer = PREVIEW_L;
			}
			else if(leyer == PREVIEW_L){
				leyer = CALL_L;
			}
			else if(leyer == SNAKE_L){
			leyer = MENU_L;
			}
			else if(leyer == MENU_TIM_L){
				leyer = MENU_L;
			}
			else if(leyer == TIME_L){
				leyer = MENU_L;
				key_pad.adad = 16;
			}
			else if(leyer == MENU_CALENDER_L){
				leyer = MENU_L;
			}
			else if(leyer == CALENDER_L){
				leyer = MENU_L;
			}
			else if(leyer == MENU_CALL_L){
				leyer = MENU_L;
			}
			else if(leyer == CALL_L){
				leyer = MENU_L;
			}
			else if(leyer == RING){
				leyer = MENU_L;
			}
			else if(leyer == SMS_L){
				leyer = MENU_L;
			}
			else if(leyer == F_SMS_L){
				leyer = MENU_L;
			}
			else if(leyer == NOTE_SMS_L){
				leyer = SMS_L;
			}
			else if(leyer == R_SMS_L){
				leyer = MENU_L;
				if(flg.test_bar1){
					flg.test_bar1 = false;
					memset(RING_SMS.mohtava,0,sizeof(RING_SMS.mohtava));
					memset(RING_SMS.number,0,sizeof(RING_SMS.number));
					memset(RING_SMS.tarikh,0,sizeof(RING_SMS.tarikh));
					memset(RING_SMS.time,0,sizeof(RING_SMS.time));
					
				}
			}
		}
}else{
	if(GPIO_Pin == SOTON_1_EX_Pin){
		if(HAL_GPIO_ReadPin(GPIOB,SOTON_1_EX_Pin)){
			key_pad.CHANGE_SATR_ALLOW = false;
			if(key_pad.Satr_Peyma == 1){
				key_pad.adad = 1;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 2){
				key_pad.adad = 4;
				flg2.state = 4;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 3){
				key_pad.adad = 7;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 4){
				key_pad.adad = 10;
				flg.m = true;
			}
		}else
			key_pad.CHANGE_SATR_ALLOW = true;
	}
	
	else if(GPIO_Pin == SOTON_2_EX_Pin){
			if(HAL_GPIO_ReadPin(GPIOB,SOTON_2_EX_Pin)){
			key_pad.CHANGE_SATR_ALLOW = false;
			if(key_pad.Satr_Peyma == 1){
				key_pad.adad = 2;
				flg2.state = 2;
				flg.m = true;	
				}
			else if(key_pad.Satr_Peyma == 2){
				key_pad.adad = 5;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 3){
				key_pad.adad = 8;
				flg2.state = 3;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 4){
				key_pad.adad = 0;
				flg.m = true;
			}
		}else
			key_pad.CHANGE_SATR_ALLOW = true;
		
	}
	
	else if(GPIO_Pin == SOTON_3_EX_Pin){
			if(HAL_GPIO_ReadPin(GPIOB,SOTON_3_EX_Pin)){
			key_pad.CHANGE_SATR_ALLOW = false;
			if(key_pad.Satr_Peyma == 1){
				key_pad.adad = 3;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 2){
				key_pad.adad = 6;
				flg2.state = 1;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 3){
				key_pad.adad = 9;
				flg.m = true;
			}
			else if(key_pad.Satr_Peyma == 4){
				key_pad.adad = 11;
				flg.m = true;
			}
		}else
			key_pad.CHANGE_SATR_ALLOW = true;
		
	}
	
	else if(GPIO_Pin == SOTON_4_EX_Pin){
		if(HAL_GPIO_ReadPin(GPIOB,SOTON_4_EX_Pin)){
			key_pad.CHANGE_SATR_ALLOW = false;
			if(key_pad.Satr_Peyma == 1)
				key_pad.adad = 12;
			else if(key_pad.Satr_Peyma == 2)
				key_pad.adad = 13;
			else if(key_pad.Satr_Peyma == 3)
				key_pad.adad = 14;
			else if(key_pad.Satr_Peyma == 4){
				key_pad.adad = 15;
				LEDRED_OFF
			}
		}else
			key_pad.CHANGE_SATR_ALLOW = true;
	}
	
}
}
void HAL_UART_RxCpltCallback (UART_HandleTypeDef *huart){
	//HAL_UART_Transmit(&huart1,(uint8_t *)&UART.CHAR_BUFF,sizeof(UART.CHAR_BUFF),100);
	if(huart->Instance == USART1){
		flg.ring = true;
		UART.BUFF[UART.counter] = UART.CHAR_BUFF;
		UART.counter++;
		if(UART.counter > 200){
			UART.counter = 0;
			memset(UART.BUFF,0,sizeof(UART.BUFF));
		}
		
}
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART.CHAR_BUFF,sizeof(UART.CHAR_BUFF));
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	
	HAL_TIM_Base_Start_IT(&htim4);
	
	HAL_GPIO_WritePin(GREN_LED_GPIO_Port,GREN_LED_Pin,GPIO_PIN_SET);
	ssd1306_Init();
	OffKeyPad();
	HAL_UART_Receive_IT(&huart1,(uint8_t *)&UART.CHAR_BUFF,sizeof(UART.CHAR_BUFF));
	HAL_Delay(5);
	HAL_UART_Transmit(&huart1,(unsigned char*)&("AT"),2,800);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	HAL_Delay(50);
	HAL_UART_Transmit(&huart1,(uint8_t *)&"AT+CMGF=1",9,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	HAL_Delay(50);
	HAL_UART_Transmit(&huart1,(unsigned char*)&"AT+CNMI=1,2,0,0,0",17,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	HAL_Delay(50);
	//sms_ersal("\"09382035121\"");
  while (1)
  {
		// KEYPAD
		keypad_refresh(key_pad.Satr_Peyma);
		//INTRUPT RING
		if(flg.ring == true){
			IRING();
		}
		// PREVIEW
		if(leyer == PREVIEW_L){
			PREVIEW();
		}
		// MENU
		else if(leyer == MENU_L){
			MENU();
		}
		//SNAKE
		else if(leyer == SNAKE_L){
			SNAKE();	
		}
		//MENU_TIM
		else if(leyer == MENU_TIM_L){
			MENU1();
		}
		//TIME
		else if(leyer == TIME_L){
			TIME();
		}
		//MENU_CALENDER
		else if(leyer == MENU_CALENDER_L){
			MENU2();
		}
		//CALENDER
		else if(leyer == CALENDER_L){
			CALENDER();
		}
		//MENU CALL 
		else if(leyer == MENU_CALL_L){
			MENU3();
		}
		//CALL
		else if(leyer == CALL_L){
			CALL();
		}
		//RING
		else if(leyer == RING){
			FRING();
		}

		//MENU SMS
		else if(leyer == SMS_L){
			menu4();
		}
		//enter number sms
		else if(leyer == F_SMS_L){
			sms();
		}
		else if(leyer == NOTE_SMS_L){
			note_sms();
		}
		else if(leyer == MY_RING_L){
			my_ring();
		}
		else if(leyer == R_SMS_L){
			r_sms();
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void CALL (void){
	if(flg.nimsec)
	{
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		painter__(0,20,"ENTER THE NUMBER",Font_6x8);
		if(key_pad.adad <= 9 && CAL.i<=10){
			CAL.CBUFF = yabesh(key_pad.adad,CAL.i);
			CAL.BUFF[CAL.i] = CAL.CBUFF; 
			CAL.i++;
			key_pad.adad = 16;
		}
		else if(key_pad.adad == 11){
			CAL.i = 0;
		for(int i=0;i<=10;i++){
			CAL.BUFF[i] = 0;
		}
			key_pad.adad = 16;
		}
		else if(key_pad.adad == 15){
			CAL.BUFF[CAL.i-1]=0;
			CAL.i--;
			key_pad.adad = 16;
		}
		if(key_pad.adad == 10 && CAL.i == 11){
			//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			key_pad.adad =16;
			strcat(CAL.elhaq,CAL.BUFF);
			CAL.elhaq [14] = ';';
			HAL_Delay(50);
			HAL_UART_Transmit(&huart1,(uint8_t *)&(CAL.elhaq),15,100);
			HAL_Delay(50);
			HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
			leyer = MY_RING_L;
		}
		painter__(0,35,CAL.BUFF,Font_6x8);
		
		ssd1306_UpdateScreen();
	}
}
void MENU3(void){
	if(flg.nimsec)
	{
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		painter__(120,50,"N",Font_6x8);
		painter__(40,20,"CALL",Font_11x18);
		ssd1306_UpdateScreen();
		if(key_pad.adad == 10){
			leyer = CALL_L;
			key_pad.adad = 16;
		}
		
	}
}
void CALENDER (void){
	if(flg.nimsec){
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		namayesh(DATE.day,DATE.mounth,DATE.year,DATE.weekday);
		ssd1306_UpdateScreen();
	}
}
void MENU2 (void){
	if(flg.nimsec)
	{
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		painter__(120,50,"N",Font_6x8);
		painter__(20,20,"CALENDER",Font_11x18);
		ssd1306_UpdateScreen();
		if(key_pad.adad == 10){
			leyer = CALENDER_L;
			key_pad.adad = 16;
		}
		
	}
}
void PREVIEW (void){
	if(flg.nimsec){
				flg.nimsec = false;
				ssd1306_Fill(Black);
				clk_preveiw(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
				painter__(0,50,"C",Font_6x8);
				painter__(120,50,"M",Font_6x8);
				ssd1306_UpdateScreen();
	}
}

void MENU (void){
	if(flg.nimsec){
				flg.nimsec = false;
				if(key_pad.adad != 10){
					ssd1306_Fill(Black);
					clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
					painter__(0,50,"H",Font_6x8);
					painter__(30,20,"Snake",Font_11x18);
					painter__(120,50,"N",Font_6x8);
					ssd1306_UpdateScreen();
				}else{
					key_pad.adad = 16;
					leyer = SNAKE_L;
		}
}
}

void MENU1 (void){
	if(flg.nimsec){
				flg.nimsec = false;
				if(key_pad.adad != 10){
					ssd1306_Fill(Black);
					clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
					painter__(0,50,"H",Font_6x8);
					painter__(30,20,"TIME",Font_11x18);
					painter__(120,50,"N",Font_6x8);
					ssd1306_UpdateScreen();
				}else{
					key_pad.adad = 16;
					leyer = TIME_L;
		}
}
}
void TIME (void){
	if(flg.nimsec){
		flg.nimsec = false;
		if(key_pad.adad == 12){
			EDIT_TIME.ALOOWCHANGE =1; // HOUR ALLOW
			key_pad.adad = 16;
		}
		else if(key_pad.adad == 13){
			EDIT_TIME.ALOOWCHANGE =2; // MIN ALLOW
			key_pad.adad = 16;
		}
		else if(key_pad.adad == 14){
			EDIT_TIME.ALOOWCHANGE =3; // SEC ALLOW
			key_pad.adad = 16;
		}
		else if(key_pad.adad == 15){
			EDIT_TIME.ALARMMODE = true; // ALARM ALLOW
			key_pad.adad = 16;
			//painter__(0,0,"F4 ALRAM",Font_6x8);
			EDIT_TIME.ALOOWCHANGE =1; 
			//LEDRED_ON
		}
	ssd1306_Fill(Black);
	pishzamine(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
	clk_edit(EDIT_TIME.RESULTMIN,EDIT_TIME.RESULTHOUR,EDIT_TIME.RESULTSEC);
	if(EDIT_TIME.ALOOWCHANGE == 0){
		painter__(80,20,"F1 HOUR",Font_6x8);
		painter__(80,30,"F2 MIN",Font_6x8);
		painter__(80,40,"F3 SEC",Font_6x8);
		painter__(75,9,"F4 ALRAM",Font_6x8); //ESHTEBAH TYPEI	
	}
	if(EDIT_TIME.ALOOWCHANGE == 1){
		painter__(0,40,"HOUR",Font_6x8);
		if(key_pad.adad<=9 && EDIT_TIME.M == 0){
			EDIT_TIME.HOUR1 = key_pad.adad;
			key_pad.adad = 16;
			EDIT_TIME.M = 1;
		}
		else if(key_pad.adad<=9 && EDIT_TIME.M == 1){
			EDIT_TIME.HOUR2 = key_pad.adad;
			key_pad.adad = 16;
			EDIT_TIME.M = 0;
		}
		EDIT_TIME.RESULTHOUR = 10*EDIT_TIME.HOUR1 + EDIT_TIME.HOUR2;
		
		if(EDIT_TIME.RESULTHOUR<=23)
		clk_edit(EDIT_TIME.RESULTMIN,EDIT_TIME.RESULTHOUR,EDIT_TIME.RESULTSEC);
		else {
			EDIT_TIME.HOUR1 = 0;
			EDIT_TIME.HOUR2 = 0;
		}
			if(key_pad.adad == 10){
				if(!EDIT_TIME.ALARMMODE){
					CURRENT_TIME.HOUR = EDIT_TIME.RESULTHOUR;
					CURRENT_TIME.MIN = EDIT_TIME.RESULTMIN;
					CURRENT_TIME.SECEND = EDIT_TIME.RESULTSEC;
				}
				if(EDIT_TIME.ALARMMODE){
					ALARM.ALARMHOUR = EDIT_TIME.RESULTHOUR;
					ALARM.ALARMMIN = EDIT_TIME.RESULTMIN;
					ALARM.ALARMSEC = EDIT_TIME.RESULTSEC;
					EDIT_TIME.ALARMMODE = false;
				}
				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.HOUR2 = 0;
				EDIT_TIME.MIN1 = 0;
				EDIT_TIME.MIN2 = 0;
				EDIT_TIME.SEC1 = 0;
				EDIT_TIME.SEC2 = 0;
				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.ALOOWCHANGE = 0;
				EDIT_TIME.M = 0;
				
			}
			else if(key_pad.adad == 11){
				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.HOUR2 = 0;
			}
		key_pad.adad = 16;
		}
	
		if(EDIT_TIME.ALOOWCHANGE == 2){
			painter__(0,40,"MIN",Font_6x8);
		if(key_pad.adad<=9 && EDIT_TIME.M == 0){
			EDIT_TIME.MIN1 = key_pad.adad;
			key_pad.adad = 16;
			EDIT_TIME.M = 1;
		}
		else if(key_pad.adad<=9 && EDIT_TIME.M == 1){
			EDIT_TIME.MIN2 = key_pad.adad;
			key_pad.adad = 16;
			EDIT_TIME.M = 0;
		}
		EDIT_TIME.RESULTMIN = 10*EDIT_TIME.MIN1 + EDIT_TIME.MIN2;
		
		if(EDIT_TIME.RESULTMIN<=59)
		clk_edit(EDIT_TIME.RESULTMIN,EDIT_TIME.RESULTHOUR,EDIT_TIME.RESULTSEC);
		else {
			EDIT_TIME.MIN1 = 0;
			EDIT_TIME.MIN2 = 0;
		}
			if(key_pad.adad == 10){
				if(!EDIT_TIME.ALARMMODE){
					CURRENT_TIME.HOUR = EDIT_TIME.RESULTHOUR;
					CURRENT_TIME.MIN = EDIT_TIME.RESULTMIN;
					CURRENT_TIME.SECEND = EDIT_TIME.RESULTSEC;
				}
				if(EDIT_TIME.ALARMMODE){
					ALARM.ALARMHOUR = EDIT_TIME.RESULTHOUR;
					ALARM.ALARMMIN = EDIT_TIME.RESULTMIN;
					ALARM.ALARMSEC = EDIT_TIME.RESULTSEC;
					EDIT_TIME.ALARMMODE = false;
				}

				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.HOUR2 = 0;
				EDIT_TIME.MIN1 = 0;
				EDIT_TIME.MIN2 = 0;
				EDIT_TIME.SEC1 = 0;
				EDIT_TIME.SEC2 = 0;
				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.ALOOWCHANGE = 0;
				EDIT_TIME.M = 0;
			}
			else if(key_pad.adad == 11){
				EDIT_TIME.MIN1 = 0;
				EDIT_TIME.MIN2 = 0;
			}
		key_pad.adad = 16;
		}
		
		if(EDIT_TIME.ALOOWCHANGE == 3){
			painter__(0,40,"SEC",Font_6x8);
		if(key_pad.adad<=9 && EDIT_TIME.M == 0){
			EDIT_TIME.SEC1 = key_pad.adad;
			key_pad.adad = 16;
			EDIT_TIME.M = 1;
		}
		else if(key_pad.adad<=9 && EDIT_TIME.M == 1){
			EDIT_TIME.SEC2 = key_pad.adad;
			key_pad.adad = 16;
			EDIT_TIME.M = 0;
		}
		EDIT_TIME.RESULTSEC = 10*EDIT_TIME.SEC1 + EDIT_TIME.SEC2;
		
		if(EDIT_TIME.RESULTSEC<=59)
		clk_edit(EDIT_TIME.RESULTMIN,EDIT_TIME.RESULTHOUR,EDIT_TIME.RESULTSEC);
		else {
			EDIT_TIME.SEC1 = 0;
			EDIT_TIME.SEC2 = 0;
		}
			if(key_pad.adad == 10){
				if(!EDIT_TIME.ALARMMODE){
					CURRENT_TIME.HOUR = EDIT_TIME.RESULTHOUR;
					CURRENT_TIME.MIN = EDIT_TIME.RESULTMIN;
					CURRENT_TIME.SECEND = EDIT_TIME.RESULTSEC;
				}
				if(EDIT_TIME.ALARMMODE){
					ALARM.ALARMHOUR = EDIT_TIME.RESULTHOUR;
					ALARM.ALARMMIN = EDIT_TIME.RESULTMIN;
					ALARM.ALARMSEC = EDIT_TIME.RESULTSEC;
					EDIT_TIME.ALARMMODE = false;
				}
				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.HOUR2 = 0;
				EDIT_TIME.MIN1 = 0;
				EDIT_TIME.MIN2 = 0;
				EDIT_TIME.SEC1 = 0;
				EDIT_TIME.SEC2 = 0;
				EDIT_TIME.HOUR1 = 0;
				EDIT_TIME.ALOOWCHANGE = 0;
				EDIT_TIME.M = 0;
				
			}
			else if(key_pad.adad == 11){
				EDIT_TIME.SEC1 = 0;
				EDIT_TIME.SEC2 = 0;
			}
		key_pad.adad = 16;
		}
		ssd1306_UpdateScreen();
}
}
void header(void){
	if(flg.nimsec2){
	flg.nimsec2=false;
	ssd1306_Fill(Black);
	if(flg2.state==1 || flg2.state==2 || flg2.state ==3 || flg2.state==4){
		for(int i=tedad;i>0;--i){
				makan[i].x=makan[i-1].x;
				makan[i].y=makan[i-1].y;
			}
		if (flg2.state==1){
			makan[0].x=makan[0].x+6;
			flg2.jahat=1;
		}
		if (flg2.state==2){
			makan[0].y=makan[0].y-8;
			flg2.jahat=2;
		}
		if (flg2.state==3){
			makan[0].y=makan[0].y+8;
			flg2.jahat=3;
		}
		if (flg2.state==4){
			makan[0].x=makan[0].x-6;
			flg2.jahat=4;
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
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		for(int i=0;i<tedad;i++){
			ssd1306_SetCursor(makan[i].x,makan[i].y);
			ssd1306_WriteString(".",Font_6x8 ,White);
		}
		
		ssd1306_SetCursor(makan_qarch_feli.x,makan_qarch_feli.y);
		ssd1306_WriteString(".",Font_6x8,White);
		
		
		ssd1306_UpdateScreen();
		
		if(makan[0].x >119 || makan[0].x <0 || makan[0].y>53 || makan[0].y<0){
			gameover();
		}
}
	}
void SNAKE (void){
	if(flg2.step == 0){
		khoshamad();
	}
	if(flg2.step == 1){
		header();
	}
}
void khoshamad(void){
	if(flg.nimsec){
		key_pad.adad = 16;
		flg.nimsec = false;
		ssd1306_Fill(Black);
		flg2.state=0;
		ssd1306_SetCursor(0,20);
		ssd1306_WriteString("Prees Start",Font_11x18 ,White);
		painter__(0,50,"M",Font_6x8);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		ssd1306_UpdateScreen();
		if(key_pad.adad == 10){
				flg2.step =1;
		}
		
}
	}
void gameover(void){
	for(int i=0;i<=4;i++){

		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		ssd1306_SetCursor(0,20);
		ssd1306_WriteString("Game Over",Font_6x8  ,White);
		
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
		HAL_Delay(350);
		ssd1306_UpdateScreen();
	
	}
	tedad=1;
	makan[0].x=0;
	makan[0].y=8;
	flg2.state =0;
	flg2.step =0;
	flg2.jahat=0;
	score=0;
	SNAKE();
}
void FRING (void){

		if(flg.nimsec){
			flg.nimsec = false;
			ssd1306_Fill(Black);
			
			painter__(30,20,"RING",Font_11x18);
			painter__(0,20,"R",Font_6x8);
			painter__(120,20,"A",Font_6x8);
			painter__(0,50,"B",Font_6x8);
			if(key_pad.adad == 10){
				HAL_UART_Transmit(&huart1,(uint8_t *)&"ATA",3,100);
				HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
				HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.cntlz),1,800);
				memset(UART.BUFF,0,sizeof(UART.BUFF));
				key_pad.adad =16;
			}
			else if(key_pad.adad == 11){
				HAL_UART_Transmit(&huart1,(uint8_t *)&"ATH",3,100);
				HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
				HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.cntlz),1,800);
				leyer = PREVIEW_L;
				memset(UART.BUFF,0,sizeof(UART.BUFF));
				key_pad.adad =16;
			}
			ssd1306_UpdateScreen();
}
}
void IRING (void){
	flg.ring = false;
	//HAL_UART_Transmit(&huart2,(uint8_t *)&UART.BUFF,sizeof(UART.BUFF),1000);
	//HAL_Delay(100);
	
	for(int i=0;i<=60;i++){
		
		if(UART.BUFF[i] == 'R' && UART.BUFF[i+1] == 'I' && UART.BUFF[i+2] == 'N' && UART.BUFF[i+3] == 'G'){
			HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
			memset(UART.BUFF,0,sizeof(UART.BUFF));
			leyer = RING;
			UART.counter = 0;
		}
		else if(UART.BUFF[i] == '+' && UART.BUFF[i+1] == 'C' && UART.BUFF[i+2] == 'M' && UART.BUFF[i+3] == 'T'){
			RING_SMS.number [0] = '0';

			for(int x=0;x<=7;x++){
				RING_SMS.tarikh[x] = UART.BUFF[i+26+x];
			}
			
			for(int x=1;x<=10;x++){
				RING_SMS.number[x] = UART.BUFF[i+x+9];
			}
			for(int x=0;x<=4;x++){
				RING_SMS.time[x] = UART.BUFF[i+x+35];
			}
			for(int x=0;UART.BUFF[i+x+49] !=0 ;x++){
				if(UART.BUFF[i+x+49] >= 32 && UART.BUFF[i+x+49] <= 126)
					RING_SMS.mohtava[x] = UART.BUFF[i+x+49];
			}
			
			//HAL_UART_Transmit(&huart1,(unsigned char*)&"AT+CNMI=1,2,0,0,0",17,100);
			leyer = R_SMS_L;
			RING_SMS.mohtava_counter =0;
//			memset(RING_SMS.mohtava,0,sizeof(RING_SMS.mohtava));
//			memset(RING_SMS.number,0,sizeof(RING_SMS.number));
//			memset(RING_SMS.tarikh,0,sizeof(RING_SMS.tarikh));
//			memset(RING_SMS.time,0,sizeof(RING_SMS.time));
		}
	}
}
void menu4 (void){
	if(flg.nimsec)
	{
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		painter__(120,50,"N",Font_6x8);
		painter__(40,20,"SMS",Font_11x18);
		ssd1306_UpdateScreen();
	}
	if(key_pad.adad == 10){
		key_pad.adad =16;
		leyer = F_SMS_L;
	}
}
void sms_ersal(char *bufer){
	strcat(SMSS.sarehambandi,bufer);
	strcat(SMSS.sarehambandi,"\"");
	strcat(SMSS.elhaq,SMSS.sarehambandi);
	HAL_UART_Transmit(&huart1,(uint8_t *)&"AT+CSMP=49,167,0,8",18,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	
	HAL_Delay(50);
	HAL_UART_Transmit(&huart1,(uint8_t *)&"AT+CMGF=1",9,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	HAL_Delay(50);

	HAL_UART_Transmit(&huart1,(uint8_t *)&SMSS.elhaq,21,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	HAL_Delay(50);

	HAL_UART_Transmit(&huart1,(uint8_t *)&key_pad.negahdari,key_pad.negahdari_shomar,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
	HAL_Delay(50);

	HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.cntlz),1,800);

	HAL_Delay(50);
	strcpy(SMSS.sarehambandi,"\"");
	strcpy(SMSS.elhaq,"AT+CMGS=");
}
void sms (void){
	if(flg.nimsec)
	{
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		painter__(0,20,"ENTER THE NUMBER",Font_6x8);
		if(key_pad.adad <= 9 && SMSS.i<=10){
			SMSS.CBUFF = yabesh(key_pad.adad,SMSS.i);
			SMSS.BUFF[SMSS.i] = SMSS.CBUFF; 
			SMSS.i++;
			key_pad.adad = 16;
		}
		else if(key_pad.adad == 11){
			SMSS.i = 0;
		for(int i=0;i<=10;i++){
			SMSS.BUFF[i] = 0;
		}
			key_pad.adad = 16;
		}
		if(key_pad.adad == 15){
			SMSS.i--;
			SMSS.BUFF[SMSS.i] = 0;
			key_pad.adad =16;
		}
		if(key_pad.adad == 10 && SMSS.i == 11){
			leyer = NOTE_SMS_L;
			key_pad.adad =11;
		}
		painter__(0,35,SMSS.BUFF,Font_6x8);
		ssd1306_UpdateScreen();
	}
}
void note_sms(void){
	if(flg.keypad_tim == false){
		for(int i=0;i<=9;i++){
			if(key_pad.adad==i ){
				
				key_pad.counter[i]++;
				if(key_pad.counter[i] == 5){
					key_pad.counter[i] =1;
				}
			}else if(key_pad.adad!=i ){
				key_pad.counter[i] =0;
			}
		}
		if(flg.m){
			flg.m = false;
			key_pad.namayesh = Hrof(key_pad.counter);
		}
	}
	else if(flg.keypad_tim){
		flg.keypad_tim = false;
		for(int i=1;i<=9;i++){
			key_pad.counter[i]=0;
		}
	}
	if(key_pad.adad == 12){
		key_pad.negahdari[key_pad.negahdari_shomar] = key_pad.namayesh;
		key_pad.negahdari_shomar++;
		key_pad.adad = 16;
	}
	else if(key_pad.adad == 11){
		key_pad.adad = 16;
		key_pad.namayesh = NULL;
		for(int i=0;i<=59;i++){
			key_pad.negahdari[i] = NULL;
		}
		key_pad.negahdari_shomar=0;
	}
	else if(key_pad.adad == 15){
		key_pad.adad = 16;
		key_pad.namayesh = NULL;
		key_pad.negahdari[key_pad.negahdari_shomar-1]=NULL;
		key_pad.negahdari_shomar--;
		
	}
	else if(key_pad.adad == 10){
		key_pad.adad =16;
		sms_ersal(SMSS.BUFF);
		key_pad.namayesh = NULL;
		for(int i=0;i<=59;i++){
			key_pad.negahdari[i] = NULL;
		}
		key_pad.negahdari_shomar=0;
		HAL_GPIO_WritePin(GREN_LED_GPIO_Port,GREN_LED_Pin,GPIO_PIN_RESET);
		HAL_Delay(100);
		HAL_GPIO_WritePin(GREN_LED_GPIO_Port,GREN_LED_Pin,GPIO_PIN_SET);
	}
	if(flg.nimsec){
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,50,"M",Font_6x8);
		//painter__(120,50,"N",Font_6x8);
		ssd1306_SetCursor(120,0);
		ssd1306_WriteChar(key_pad.namayesh,Font_6x8,White);
		
		ssd1306_SetCursor(key_pad.set_x,key_pad.set_y);
		ssd1306_WriteString(key_pad.negahdari,Font_6x8,White);
		
		ssd1306_UpdateScreen();
	}
}
void my_ring (void){
	if(key_pad.adad == 11){
		HAL_UART_Transmit(&huart1,(uint8_t *)&"ATH",3,100);
		HAL_Delay(50);
		HAL_UART_Transmit(&huart1,(uint8_t*)&(UART.enter),1,800);
		leyer = MENU_L;
	}
	if(flg.nimsec){
		flg.nimsec=false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		painter__(0,20,"R",Font_6x8);
		painter__(40,20,CAL.BUFF,Font_6x8);
		
		ssd1306_UpdateScreen();
	}
}
void r_sms(void){
	if(flg.nimsec){
		flg.nimsec = false;
		ssd1306_Fill(Black);
		clk_menu(CURRENT_TIME.MIN,CURRENT_TIME.HOUR,CURRENT_TIME.SECEND,ALARM.ALARMHOUR,ALARM.ALARMMIN,ALARM.ALARMSEC);
		ssd1306_SetCursor(20,40);
		rasm_string_with_char(10,RING_SMS.number);
		
		ssd1306_SetCursor(75,0);
		ssd1306_WriteString(RING_SMS.tarikh,Font_6x8,White);
		
		painter__(90,50,RING_SMS.time,Font_6x8);
		painter__(0,30,RING_SMS.mohtava,Font_6x8);
		painter__(0,50,"B",Font_6x8);
		ssd1306_UpdateScreen();
	}
	if(key_pad.adad == 11){
			leyer = MENU_L;
			
		}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
