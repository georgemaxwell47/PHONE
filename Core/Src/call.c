#include "call.h"
#include "string.h"
#include "painter.h"
#include "gpio.h"

char moredcpy [10];
char khodecpy [10];
char yabesh(int adad,int i){
	//HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
		if(adad == 0){
			moredcpy[i] = '0';
		}
		if(adad == 1){
			moredcpy[i] = '1'; 
		}
		else if(adad == 2){
			moredcpy[i] = '2'; 
		}
		else if(adad == 3){
			moredcpy[i] = '3'; 
		}
		else if(adad == 4){
			moredcpy[i] = '4'; 
		}
		else if(adad == 5){
			moredcpy[i] = '5'; 
		}
		else if(adad == 6){
			moredcpy[i] = '6'; 
		}
		else if(adad == 7){
			moredcpy[i] = '7'; 
		}
		else if(adad == 8){
			moredcpy[i] = '8'; 
		}
		else if(adad == 9){
			moredcpy[i] = '9'; 
		}
		return moredcpy[i];
}