/*
 * buzzer.c
 *
 *  Created on: Jul 29, 2025
 *      Author: RCY
 */

#include "buzzer.h"
#include <stdbool.h>

#define TIM3_IRQ_PERIOD		1000000

extern TIM_HandleTypeDef htim3;
volatile bool buzzer_enabled = false;
volatile bool buzzer_start = false;


volatile uint32_t buz_cycles_left = 0;  // 남은 주기 수


void buzzer_op(buzzer_t op)
{
	if(op == BUZZER_ON)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
	}
	else if(op == BUZZER_OFF)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
	}
	else if(op == BUZZER_TOGGLE)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
//		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_15);
	}
}

void pitches_to_period(uint16_t tone_hz)
{
    // TIM3 업데이트 인터럽트 비활성화
//    TIM3->DIER &= ~TIM_DIER_UIE;

    // PSC=71 → 1 MHz 타이머 tick → ARR = (1e6 / f) - 1
    uint32_t arr = (1000000UL + (tone_hz / 2)) / tone_hz; // 반올림
    if (arr == 0) arr = 1;
    arr -= 1;
    if (arr > 0xFFFF) arr = 0xFFFF;

    // ARR 갱신
    TIM3->ARR = (uint16_t)arr;
//    TIM3->CNT = 0;

    // 듀티 50%로 맞추려면 CCR1도 같이 갱신
//    TIM3->CCR1 = (uint16_t)((arr + 1) / 2);

    // 즉시 적용
//    TIM3->EGR |= TIM_EGR_UG;

    // TIM3 업데이트 인터럽트 재활성화
//    TIM3->DIER |= TIM_DIER_UIE;

//	buzzer_start = true;
}

void buz_set_tone_hz(uint32_t tone_hz)
{
    if (tone_hz == 0)
    {
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); // BZ_ON=0
        return;
    }

    // ARR = round(1e6 / f) - 1   (1us tick, PSC=71)
    uint32_t arr = (1000000UL + (tone_hz / 2)) / tone_hz;  // round
    if (arr == 0) arr = 1;                                  // 보호
    arr -= 1;
    if (arr > 0xFFFF) arr = 0xFFFF;

    __HAL_TIM_DISABLE(&htim3);

    __HAL_TIM_SET_AUTORELOAD(&htim3, (uint16_t)arr);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ((uint16_t)arr + 1) / 2); // 50%
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    htim3.Instance->EGR = TIM_EGR_UG;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);          // BZ_ON=1
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void buz_beep_ms(uint32_t tone_hz, uint32_t ms)
{
    if (tone_hz == 0 || ms == 0)
    {
        // 바로 끔
        HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);  // BZ_ON=0
        TIM3->DIER &= ~TIM_DIER_UIE;                           // IRQ off
        buz_cycles_left = 0;
        return;
    }

    // 1) 톤 1회 세팅
    buz_set_tone_hz(tone_hz);

    // 2) 게이트 ON + PWM 스타트
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);        // BZ_ON=1
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

    // 3) "몇 주기만 울릴지"를 계산해서 넣어둠
    //    cycles = duration_us / period_us = (ms*1000) / (ARR+1)
    uint32_t arr_plus1 = __HAL_TIM_GET_AUTORELOAD(&htim3) + 1U;

    // 64비트로 안전 계산 + 반올림
    uint64_t duration_us = (uint64_t)ms * 1000ULL;
    uint32_t cycles = (uint32_t)((duration_us + (arr_plus1/2)) / arr_plus1);
    if (cycles == 0) cycles = 1;

    buz_cycles_left = cycles;

    // 4) TIM3 업데이트 인터럽트 켜서 "주기마다 1씩 감소"하게 함
    __HAL_TIM_CLEAR_FLAG(&htim3, TIM_FLAG_UPDATE);
    __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
}

