/*
 * buzzer.h
 *
 *  Created on: Jul 29, 2025
 *      Author: RCY
 */

#ifndef INC_DRIVER_BUZZER_H_
#define INC_DRIVER_BUZZER_H_


#include "stm32f1xx_hal.h"


typedef enum
{
	BUZZER_ON,
	BUZZER_OFF,
	BUZZER_TOGGLE
}buzzer_t;



void buzzer_init(void);
void buzzer_beep(uint16_t freq, uint16_t duration_ms);
void buzzer_op(buzzer_t op);
void pitches_to_period(uint16_t tone_hz);

void buz_set_tone_hz(uint32_t tone_hz);
void buz_beep_ms(uint32_t tone_hz, uint32_t ms);

#endif /* INC_DRIVER_BUZZER_H_ */
