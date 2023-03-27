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
char Hrof(int * keypad ){
	for(int i=0;i<=9;i++){
		if(keypad[i]!=0)
			if(i == 1){
				if(keypad[i] == 1){
					return 'A';
				}
				else if(keypad[i] == 2){
					return 'B';
				}
				else if(keypad[i] == 3){
					return 'C';
				}
				else if(keypad[i] == 4){
					return '1';
				}
	}
			else if(i == 2){
				if(keypad[i] == 1){
					return 'D';
				}
				else if(keypad[i] == 2){
					return 'E';
				}
				else if(keypad[i] == 3){
					return 'F';
				}
				else if(keypad[i] == 4){
					return '2';
				}
	}
			else if(i == 3){
				if(keypad[i] == 1){
					return 'G';
				}
				else if(keypad[i] == 2){
					return 'H';
				}
				else if(keypad[i] == 3){
					return 'I';
				}
				else if(keypad[i] == 4){
					return '3';
				}
	}
			else if(i == 4){
				if(keypad[i] == 1){
					return 'J';
				}
				else if(keypad[i] == 2){
					return 'K';
				}
				else if(keypad[i] == 3){
					return 'L';
				}
				else if(keypad[i] == 4){
					return '4';
				}
	}
			else if(i == 5){
				if(keypad[i] == 1){
					return 'M';
				}
				else if(keypad[i] == 2){
					return 'N';
				}
				else if(keypad[i] == 3){
					return 'O';
				}
				else if(keypad[i] == 4){
					return '5';
				}
	}
			else if(i == 6){
				if(keypad[i] == 1){
					return 'P';
				}
				else if(keypad[i] == 2){
					return 'Q';
				}
				else if(keypad[i] == 3){
					return 'R';
				}
				else if(keypad[i] == 4){
					return '6';
				}
	}
			else if(i == 7){
				if(keypad[i] == 1){
					return 'S';
				}
				else if(keypad[i] == 2){
					return 'T';
				}
				else if(keypad[i] == 3){
					return 'U';
				}
				else if(keypad[i] == 4){
					return '7';
				}
	}
			else if(i == 8){
				if(keypad[i] == 1){
					return 'V';
				}
				else if(keypad[i] == 2){
					return 'W';
				}
				else if(keypad[i] == 3){
					return 'X';
				}
				else if(keypad[i] == 4){
					return '8';
				}
	}
			else if(i == 9){
				if(keypad[i] == 1){
					return 'Y';
				}
				else if(keypad[i] == 2){
					return 'Z';
				}
				else if(keypad[i] == 3){
					return '"';
				}
				else if(keypad[i] == 4){
					return '9';
				}
	}
			else if(i == 0){
				if(keypad[i]%2 == 0){
					return ' ';
				}
				else{
					return '0';
				}
			}
}
	}