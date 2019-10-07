/*
 * GearBox.h
 *
 *  Created on: 2 oct. 2019
 *      Author: lucky
 */

#ifndef GEARBOX_H_
#define GEARBOX_H_

typedef unsigned char uint8;
typedef enum{
	enParkGear=0,
	enFirstGear,
	enSecondGear,
	enThirdGear,
	enFourthGear,
	enReverseGear,
	enTotalGears
}tenGearConf;

typedef struct{
	uint8 u8GearName;
	uint8 u8MaxVal;
	uint8 u8MinVal;
}tstGearInfo;

#define Park 10
#define Rvrs 11


void Gear_InitSt(void);
void Gear_vfnParkGear(void);
void Gear_vfCheckBttns4Parking(void);
void Gear_vfCheckBttns4Drive(void);


#endif /* 2_HIL_GEARBOX_H_ */
