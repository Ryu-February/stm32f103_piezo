/*
 * ap_isr.c
 *
 *  Created on: Aug 11, 2025
 *      Author: RCY
 */


#include "ap_isr.h"
#include "buzzer.h"
#include "pitches.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

extern volatile uint32_t buz_cycles_left;  // 남은 주기 수

extern volatile bool buzzer_start;

volatile uint32_t buz_ms = 0;

volatile bool sw_check = false;

extern volatile bool pb5_pressed;

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

		buz_ms++;

//		if(buz_ms > 8000)
//		{
//			buz_ms = 0;
//			buzzer_start = false;
//		}


	}

	static uint32_t sw_check_cnt = 0;
	if(++sw_check_cnt < 100)
	{
		return;
	}
	else
	{
		sw_check_cnt = 0;
		sw_check = true;
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
		if(buz_ms < 1500)
		{
			buzzer_op(BUZZER_TOGGLE);
		}
		else
		{
			buzzer_op(BUZZER_OFF);
			buzzer_start = false;
		}

		if(!pb5_pressed)
		{
			if(buz_ms < 300)
			{
				pitches_to_period(C_6);
			}
			else if(buz_ms < 600)
			{
				pitches_to_period(D_6);
			}
			else if(buz_ms < 900)
			{
				pitches_to_period(DS_6);
			}
			else if(buz_ms < 1200)
			{
				pitches_to_period(G_6);
			}
			else if(buz_ms < 1500)
			{
				pitches_to_period(C_7);
			}
		}
		else
		{
			if(buz_ms < 300)
			{
				pitches_to_period(D_7);
			}
			else if(buz_ms < 600)
			{
				pitches_to_period(F_7);
			}
			else if(buz_ms < 900)
			{
				pitches_to_period(A_7);
			}
			else if(buz_ms < 1200)
			{
				pitches_to_period(C_8);
			}
			else if(buz_ms < 1500)
			{
				pitches_to_period(E_8);
			}
		}

		/*
		if(buz_ms < 200)
		{
			pitches_to_period(G_5);
		}
		else if(buz_ms < 400)
		{
			pitches_to_period(A_5);
		}
		else if(buz_ms < 600)
		{
			pitches_to_period(B_5);
		}
		else if(buz_ms < 800)
		{
			pitches_to_period(G_5);
		}
		else if(buz_ms < 1000)
		{
			pitches_to_period(A_5);
		}
		else if(buz_ms < 1200)
		{
			pitches_to_period(B_5);
		}
		else if(buz_ms < 1500)
		{
			pitches_to_period(E_6);
		}
		else if(buz_ms < 1800)
		{
			pitches_to_period(E_7);
		}
		*/
		/*
		if(buz_ms < 500)
		{
			pitches_to_period(B_4);
		}
		else if(buz_ms < 1000 && buz_ms >= 500)
		{
			pitches_to_period(FS_5);
		}
		else if(buz_ms < 1500 && buz_ms >= 1000)
		{
			pitches_to_period(B_5);
		}
		else if(buz_ms < 2000 && buz_ms >= 1500)
		{
			pitches_to_period(FS_5);
		}
		else if(buz_ms < 2500 && buz_ms >= 2000)
		{
			pitches_to_period(G_4);
		}
		else if(buz_ms < 3000 && buz_ms >= 2500)
		{
			pitches_to_period(D_5);
		}
		else if(buz_ms < 3500 && buz_ms >= 3000)
		{
			pitches_to_period(G_5);
		}
		else if(buz_ms < 4000 && buz_ms >= 3500)
		{
			pitches_to_period(D_5);
		}
		else if(buz_ms < 4500 && buz_ms >= 4000)
		{
			pitches_to_period(A_4);
		}
		else if(buz_ms < 5000 && buz_ms >= 4500)
		{
			pitches_to_period(E_5);
		}
		else if(buz_ms < 5500 && buz_ms >= 5000)
		{
			pitches_to_period(A_5);
		}
		else if(buz_ms < 6000 && buz_ms >= 5500)
		{
			pitches_to_period(E_5);
		}
		else if(buz_ms < 6500 && buz_ms >= 6000)
		{
			pitches_to_period(D_5);
		}
		else if(buz_ms < 7000 && buz_ms >= 6500)
		{
		  pitches_to_period(A_5);
		}
		else if(buz_ms < 7500 && buz_ms >= 7000)
		{
			pitches_to_period(D_6);
		}
		else if(buz_ms < 8000 && buz_ms >= 7500)
		{
			pitches_to_period(A_5);
		}
		*/
	}
}


void ap_tim4_callback(void)
{

}
