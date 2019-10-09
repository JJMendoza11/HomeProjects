/*
 * GearBox.c
 *
 *  Created on: 2 oct. 2019
 *      Author: lucky
 */

#include "Micros2_practica1.h"
#include "GearBox.h"
#include "Debouncer.h"
#include "Timer.h"
#include "PWMDriver.h"

extern uint16 u8Seg;
uint8 u8Speed=0;
uint8 a[6][3]={
		{10,0,0},
		{1,30,0},
		{2,60,30},
		{3,90,60},
		{4,120,90},
		{11,50,0}
};

void Gear_vfnParkGear(void);
void Gear_vfnGearDrive(void);
void Gear_vfnBrake(void);
void Gear_vfnFastBreak(void);

tstGearInfo astGearsData[enTotalGears];
static tenGearConf u8Index=enParkGear;
static uint8 u8Delay=0;

void Gear_InitSt(void){
	for (uint8 i=0;i<6;i++){
		for(uint8 j=0;j<3;j++){
			if(j==0){
				astGearsData[i].u8GearName=a[i][j];
			}else if(j==1){
				astGearsData[i].u8MaxVal=a[i][j];
			}else{
				astGearsData[i].u8MinVal=a[i][j];
			}
		}
	}
}

void Gear_vfnParkGear(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if(Dbncr_u8fnCheckStableState(enBrake)){
		if(Dbncr_u8fnCheckStableState(enClutch)){
			Dbncr_vfnDbncr(enGearUp);
			if(Dbncr_u8fnRisingEdge(enGearUp)){
				u8Index=enFirstGear;
				vfnDriveState();
			}else{
				Dbncr_vfnDbncr(enGearDwn);
				if(Dbncr_u8fnRisingEdge(enGearDwn)){
					u8Index=enReverseGear;
					vfnReverseState();
				}
			}
		}
	}
}

void Gear_vfnGearDrive(void){
	u8Delay++;
	if(Dbncr_u8fnCheckStableState(enAcc)){
				if((u8Speed<astGearsData[u8Index].u8MaxVal)&&(u8Speed>=astGearsData[u8Index].u8MinVal-10)){
					vfnTMR();
					u8Speed++;
				}else{
					if(u8Speed<astGearsData[u8Index].u8MinVal-10){
						if(u8Delay==3){
							vfnTMR();
							u8Speed++;
						}
					}
				}
		}else if(u8Speed){
			if(u8Speed>astGearsData[u8Index].u8MaxVal){
				Gear_vfnFastBreak();
			}else{
				vfnTMRLess();
				u8Speed--;
			}
		}
		if((u8Index>4)&&(u8Speed>50)){
			u8Index=enFourthGear;
		}
		PWM_Acc_or_Dec(u8Speed);
		if(u8Delay==3){
			u8Delay=0;
		}
}

void Gear_vfnBrake(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if(u8Speed){
		Gear_vfnFastBreak();
		if((u8Speed<astGearsData[u8Index].u8MinVal)&&(!Dbncr_u8fnCheckStableState(enClutch))){
			u8Index--;
		}
	}else{
		if(!Dbncr_u8fnCheckStableState(enClutch)){
			vfnParkState();
			u8Index=enParkGear;
		}
	}
	PWM_Acc_or_Dec(u8Speed);
}

void Gear_vfnFastBreak(void){
	vfnTMRLess();
	u8Speed--;
}


void Gear_vfCheckBttns4Parking(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	if(Dbncr_u8fnCheckStableState(enBrake)){
		Dbncr_vfnDbncr(enClutch);
		Dbncr_vfnDbncr(enAcc);
		Gear_vfnParkGear();
	}else{
		Dbncr_vfnDbncr(enBrake);
	}
}

void Gear_vfCheckBttns4Drive(void){
	Timer_vfn4DsplyVal(astGearsData[u8Index].u8GearName);
	Dbncr_vfnDbncr(enBrake);
	Dbncr_vfnDbncr(enClutch);
	if(Dbncr_u8fnCheckStableState(enBrake)){
		Gear_vfnBrake();
	}else{
		Dbncr_vfnDbncr(enGearUp);
		Dbncr_vfnDbncr(enGearDwn);
		if (Dbncr_u8fnCheckStableState(enClutch)){
			if(u8Index!=enReverseGear){
				if(Dbncr_u8fnRisingEdge(enGearUp)){
					u8Index++;
				}else{
					if(Dbncr_u8fnRisingEdge(enGearDwn)){
						if(u8Index>1){
							u8Index--;

						}
					}
				}
			}
			if(u8Speed&&(u8Seg==160)){
				vfnTMRLess();
				u8Speed--;
			}
		}
		if(u8Speed>=astGearsData[u8Index].u8MaxVal){
			vfnTMRLess();
			u8Speed--;
		}else{
			Dbncr_vfnDbncr(enAcc);
			if(u8Seg==160){
			Gear_vfnGearDrive();
			}
		}
	}
}
