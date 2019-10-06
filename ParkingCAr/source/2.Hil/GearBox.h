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
	enClutch=0,
	enBrake,
	enAcc,
	enGearUp,
	enGearDwn,
	enTotalInputs
}tenInputsPin;

#define BrakeFlag		(1<<0)
#define ClutchFlag		(1<<1)
#define AccFlag			(1<<2)

void Gear_vfnGear(void);
void Check_Clutch_Bttn(void);
void Check_Brake_Bttn(void);
uint8 Check_GearUP_Bttn(void);
uint8 Gear_u8AccModule(void);
void Gear_vfnStartModule(void);

#endif /* 2_HIL_GEARBOX_H_ */
