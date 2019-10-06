/*
 * Timer.c
 *
 *  Created on: 22 sep. 2019
 *      Author: lucky
 */

#include "Timer.h"
#include "ShiftDriver.h"

void vfnTMR2(void);
void vfnTMR3(void);
void vfnTMR4(void);


void vfnTMRLess2(void);
void vfnTMRLess3(void);
void vfnTMRLess4(void);

uint8 u8DsplyOn=1;//Esto tendra un nombre para hacer el siempre jarioso
uint8 au8CountersValues[TotalCnt]={0,0,0,10};
uint8  *pu8Pointer=&au8CountersValues[0];

void vfnTMR(void){
	if(au8CountersValues[SecUniCnt]==MaxUniVal){
		au8CountersValues[SecUniCnt]=0;
		vfnTMR2();
	}else{
		au8CountersValues[SecUniCnt]++;
	}
}

void vfnTMR2(void){
	if(au8CountersValues[SecDecCnt]==MaxUniVal){
		au8CountersValues[SecDecCnt]=0;
		vfnTMR3();
	}else{
		au8CountersValues[SecDecCnt]++;
	}
}

void vfnTMR3(void){
	if(au8CountersValues[MinUniCnt]==MaxUniVal){
		au8CountersValues[MinUniCnt]=0;
	}else{
		au8CountersValues[MinUniCnt]++;
	}
}

void vfnTMR4(void){
	if(au8CountersValues[MinDecCnt]==0){
		au8CountersValues[MinDecCnt]=0;
	}else{
		au8CountersValues[MinDecCnt]--;
	}
}


void vfnTMRLess(void){
	if(au8CountersValues[SecUniCnt]==0){
		au8CountersValues[SecUniCnt]=MaxUniVal;
		vfnTMRLess2();
	}else{
		au8CountersValues[SecUniCnt]--;
	}
}

void vfnTMRLess2(void){
	if(au8CountersValues[SecDecCnt]==0){
		au8CountersValues[SecDecCnt]=MaxUniVal;
		vfnTMRLess3();
	}else{
		au8CountersValues[SecDecCnt]--;
	}
}

void vfnTMRLess3(void){
	if(au8CountersValues[MinUniCnt]==0){
		au8CountersValues[MinUniCnt]=MaxUniVal;
	}else{
		au8CountersValues[MinUniCnt]--;
	}
}

void vfnTMRLess4(void){
	if(au8CountersValues[MinDecCnt]==0){
		au8CountersValues[MinDecCnt]=0;
	}else{
		au8CountersValues[MinDecCnt]--;
	}
}


void Timer_vfnIdle(void){
	if(u8DsplyOn==Display4On){
		u8DsplyOn=Display1On;
		pu8Pointer=&au8CountersValues[0];
	}else{
		u8DsplyOn=u8DsplyOn<<1;
		pu8Pointer++;
	}
	Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
}

void Timer_vfn4DsplyVal(uint8 u8GearSelec){
	au8CountersValues[3]=u8GearSelec;
}

void Timer_vfnShiftLeft(void){
	if(u8DsplyOn==Display4On){
		u8DsplyOn=Display1On;
		pu8Pointer=&au8CountersValues[SecUniCnt];
	}else{
		u8DsplyOn=u8DsplyOn<<1;
		pu8Pointer++;
	}
	Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
}

void Timer_vfnShiftRight(void){
	if(u8DsplyOn==Display1On){
		u8DsplyOn=Display4On;
		pu8Pointer=&au8CountersValues[MinDecCnt];
	}else{
		u8DsplyOn=(u8DsplyOn>>1);
		pu8Pointer--;
	}
	Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
}

void Timer_vfnShiftUp(void){
	if((u8DsplyOn==Display1On)||(u8DsplyOn==Display3On)){
		if(*pu8Pointer<MaxUniVal){
			*pu8Pointer=*pu8Pointer+1;
		}else{
			*pu8Pointer=MaxUniVal;
		}
	}else{
		if(*pu8Pointer<MinDecVal){
			*pu8Pointer=*pu8Pointer+1;
		}else{
			*pu8Pointer=MinDecVal;
		}
	}
	Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
}

void Timer_vfnShiftDown(void){
	if(*pu8Pointer>0){
		*pu8Pointer=*pu8Pointer-1;
	}else{
		*pu8Pointer=0;
	}
	Shift_vfnDecode(pu8Pointer,&u8DsplyOn);
}

uint8 vfnCheckTimer(void){
	if(au8CountersValues[SecUniCnt]+au8CountersValues[SecDecCnt]+au8CountersValues[MinUniCnt]+au8CountersValues[MinDecCnt]!=0){
		return 1;
	}else{
		return 0;
	}
}
