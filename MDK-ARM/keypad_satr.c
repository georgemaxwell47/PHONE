#include "main.h"
void keypad_refresh(int Satr_Peyma){
	if(Satr_Peyma == 1){
		HAL_GPIO_WritePin(GPIOA,SATR_1_OUT_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,SATR_4_OUT_Pin,GPIO_PIN_RESET);
	}
	if(Satr_Peyma == 2){
		HAL_GPIO_WritePin(GPIOA,SATR_2_OUT_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,SATR_1_OUT_Pin,GPIO_PIN_RESET);
	}
	if(Satr_Peyma == 3){
		HAL_GPIO_WritePin(GPIOA,SATR_3_OUT_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,SATR_2_OUT_Pin,GPIO_PIN_RESET);
	}
	if(Satr_Peyma == 4){
		HAL_GPIO_WritePin(GPIOA,SATR_4_OUT_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,SATR_3_OUT_Pin,GPIO_PIN_RESET);
	}
}
void OffKeyPad(void){
	HAL_GPIO_WritePin(GPIOA,SATR_1_OUT_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,SATR_2_OUT_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,SATR_3_OUT_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA,SATR_4_OUT_Pin,GPIO_PIN_RESET);
}
