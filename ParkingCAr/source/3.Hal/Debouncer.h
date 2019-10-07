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
	enClutch=0,
	enBrake,
	enAcc,
	enGearUp,
	enGearDwn,
	enTotalPins
}tenPinInputs;

typedef struct{
	uint_8 Pin;
	uint_8 LastStableState;
	uint_8 u8Shots[ShootCapture];
	uint_8 u8Cntr;
	uint_8 u8Stablestate ;
}tstDbncrInfo;


void Dbncr_vfnInit(uint_8 PinVal);
void Dbncr_vfnDbncr(uint_8 u8Pin2Check);
uint_8 Dbncr_u8fnRisingEdge(uint_8 u8Pin2Check);
uint_8 Dbncr_u8fnCheckStableState(uint_8 u8Pin2Check);
void Dbncr_vfCheckBttns4Parking(void);





#endif /* 3_HAL_DEBOUNCER_H_ */
