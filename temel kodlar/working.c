/*
 * working.c
 *
 *  Created on: Dec 8, 2022
 *      Author: murat
 */

#include "working.h"

void buttonLedRun(){
	GPIO_PinState x;
	GPIO_PinState z;
	x = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
	if(x == GPIO_PIN_SET){
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else{
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	}

	z = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
	if(z == GPIO_PIN_SET){
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	}
	else{
	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	}
}

void goForward(){
	  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 1000);
	  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
}

void goBackward(){
	  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 1000);
}

void stop(){
	  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, 0);
	  __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_2, 0);
}

