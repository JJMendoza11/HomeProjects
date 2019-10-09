/*
 * Timer.h
 *
 *  Created on: 22 sep. 2019
 *      Author: lucky
 */

#ifndef TIMER
#define TIMER

typedef unsigned char uint8;
typedef unsigned short uint16;
#define MaxUniVal 	9
#define Display4On 	8
#define MinDecVal 	5
#define Display3On 	4
#define Display1On 	1

enum{
	SecUniCnt=0,
	SecDecCnt,
	MinUniCnt,
	MinDecCnt,
	TotalCnt
};
void vfnTMR(void);
void vfnTMRLess(void);
void Timer_vfnIdle(void);
void Timer_vfn4DsplyVal(uint8 u8GearSelec);
void Timer_vfnShiftLeft(void);
void Timer_vfnShiftRight(void);
void Timer_vfnShiftUp(void);
void Timer_vfnShiftDown(void);
uint8 vfnCheckTimer(void);

#endif /* 1_APP_TIMER_H_ */
