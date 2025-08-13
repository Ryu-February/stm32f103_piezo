/*
 * ap_isr.h
 *
 *  Created on: Aug 11, 2025
 *      Author: RCY
 */

#ifndef AP_AP_ISR_H_
#define AP_AP_ISR_H_

#include "main.h"
#include <stdbool.h>

void ap_tim1_callback(void);
void ap_tim2_callback(void);
void ap_tim3_callback(void);
void ap_tim4_callback(void);


#endif /* AP_AP_ISR_H_ */
