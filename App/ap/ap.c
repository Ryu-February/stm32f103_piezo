/*
 * ap.c
 *
 *  Created on: Aug 11, 2025
 *      Author: RCY
 */


#include "ap.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern volatile bool buzzer_start;

extern volatile uint32_t buz_ms;

void ap_init(void)
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}


void ap_main(void)
{
	while(1)
	{
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
//		HAL_Delay(1000);
		static bool buzzer_busy = false;

		if(!buzzer_busy)
		{
//			pitches_to_period(B_5);
			buzzer_start = true;
			buzzer_busy = true;

		}

//		if(!buzzer_busy)
//		{
//			buz_beep_ms(B_5, 500);
//			buzzer_busy = true;
//			HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
//		}


	}
}
