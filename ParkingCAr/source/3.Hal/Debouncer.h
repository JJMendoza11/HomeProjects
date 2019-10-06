/*
 * Debouncer.h
 *
 *  Created on: 19/09/2019
 *      Author: Poncho
 */

#ifndef DEBOUNCER_H_
#define DEBOUNCER_H_
typedef unsigned char uint_8 ;
typedef unsigned long uint_32;

#define LastValue 2
#define ShootCapture 3

typedef enum{
	enPin1=0,
	enPin2,
	enPin3,
	enPin4,
	enPin5,
	enTotalPins
}tenPinConf;

typedef struct{
	uint_8 Pin;
	uint_8 LastStableState;
	uint_8 u8Shots[ShootCapture];
	uint_8 u8Cntr;
	uint_8 u8Stablestate ;
}tstDbncrInfo;


void DbncrInit(uint_8 PinVal);
uint_8 Dbncr(uint_8 u8Pin2Check);





#endif /* 3_HAL_DEBOUNCER_H_ */
