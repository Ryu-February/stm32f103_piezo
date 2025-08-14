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

extern volatile bool sw_check;

volatile bool pb5_pressed = false;

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

		static bool prev_pb5_pressed = false;

		if(sw_check == true)
		{
			sw_check = false;

			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == true)
			{
				pb5_pressed ^= true;
			}

			if(prev_pb5_pressed != pb5_pressed)
			{
				buzzer_start = true;
				buz_ms = 0;
			}

			prev_pb5_pressed = pb5_pressed;
		}

		if(pb5_pressed == true)
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
		}
		else
		{
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
		}
	}
}
