/*
 * PWMDriver.h
 *
 *  Created on: 3 jul. 2019
 *      Author: lucky
 */

#ifndef PWMDRIVER_H_
#define PWMDRIVER_H_

typedef unsigned char uint8_t;

#define Origen 		40
#define End 		820
#define ReverseVal 3281
#define FrstGearMaxVal 1640
#define ScndGearMaxVal 3280
#define ThrdGearMaxVal 4921
#define TopSpeed		6562


void PWM_vfnDriverInit (void);
uint8_t PWM_bfnAngleAdjustment (uint8_t bNewAngle);
uint8_t PWM_bInitialPosition (void);
void PWM_Acc_or_Dec(uint8_t u8Km);
void PWM_vfnLowBrake(uint8_t *u8Gears);

#endif /* PWMDRIVER_H_ */
