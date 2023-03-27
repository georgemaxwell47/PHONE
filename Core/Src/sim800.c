#include "sim800.h"
#include "gpio.h"
#include "usart.h"
struct Urt2{
	uint8_t counter;
	int cntlz;
	int enter;
	char CHAR_BUFF;
	char BUFF[30];
};struct Urt2 UART2={0,0x1a,0x0d};
void sms_ferest(void){
	HAL_UART_Transmit(&huart1,(uint8_t *)&"AT+CSMP=49,167,0,8",18,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)(UART2.enter),1,800);
	
	HAL_Delay(1000);
	HAL_UART_Transmit(&huart1,(uint8_t *)&"AT+CMGF=1",9,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)(UART2.enter),1,800);
	HAL_Delay(1000);

	HAL_UART_Transmit(&huart1,(uint8_t *)&"AT+CMGS=\"09104204196\"",21,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)(UART2.enter),1,800);
	HAL_Delay(1000);

	HAL_UART_Transmit(&huart1,(uint8_t *)&"SLM",3,100);
	HAL_UART_Transmit(&huart1,(uint8_t*)(UART2.enter),1,800);
	HAL_Delay(1000);

	HAL_UART_Transmit(&huart1,(uint8_t*)(UART2.cntlz),1,800);

	HAL_Delay(1000);
}
