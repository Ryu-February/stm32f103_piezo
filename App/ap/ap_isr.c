/*
 * ap_isr.c
 *
 *  Created on: Aug 11, 2025
 *      Author: RCY
 */


#include "ap_isr.h"
#include "buzzer.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern volatile uint32_t buz_cycles_left;  // 남은 주기 수

extern volatile bool buzzer_start;

/*1ms irq handler*/
void ap_tim1_callback(void)
{
//	static uint32_t millis = 0;

//	if(++millis >= 500)
//	{
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
//		millis = 0;
//	}

	if(buzzer_start)
	{
		static uint32_t buz_ms = 0;
		buz_ms++;

		if(buz_ms > 500)
		{
			buz_ms = 0;
			buzzer_start = false;
		}
	}
}

/*100us irq handler*/
void ap_tim2_callback(void)
{
//	static uint32_t millis = 0;
//
//	if(++millis >= 5000)
//	{
//		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
//		millis = 0;
//	}
}

void ap_tim3_callback(void)
{
//	if (__HAL_TIM_GET_FLAG(&htim3, TIM_FLAG_UPDATE) != RESET)
//	{
//		if (__HAL_TIM_GET_IT_SOURCE(&htim3, TIM_IT_UPDATE) != RESET)
//		{
//			__HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
//
//			if (buz_cycles_left)
//			{
//				buz_cycles_left--;
//				if (buz_cycles_left == 0)
//				{
//					// 멈춰!
//					__HAL_TIM_DISABLE_IT(&htim3, TIM_IT_UPDATE);
//					HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
//					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // BZ_ON=0
//				}
//			}
//			else
//			{
//				// 비상 보호
//				__HAL_TIM_DISABLE_IT(&htim3, TIM_IT_UPDATE);
//			}
//		}
//	}
	if(buzzer_start)
	{
		buzzer_op(BUZZER_TOGGLE);
	}
}


void ap_tim4_callback(void)
{

}
