/*
 * ShiftDriver.c
 *
 *  Created on: 18 sep. 2019
 *      Author: lucky
 */

#include "ShiftDriver.h"
#include "GPIODriver.h"


void Shift_vfnDecode(uint8 *u8DeciVal,uint8 *u8SlcDsply){
	uint8 u8DecoVal=0;
	switch (*u8DeciVal){
	case 0:
		u8DecoVal=Zero;
		break;
	case 1:
		u8DecoVal=One;
		break;
	case 2:
		u8DecoVal=Two;
		break;
	case 3:
		u8DecoVal=Three;
		break;
	case 4:
		u8DecoVal=Four;
		break;
	case 5:
		u8DecoVal=Five;
		break;
	case 6:
		u8DecoVal=Six;
		break;
	case 7:
		u8DecoVal=Seven;
		break;
	case 8:
		u8DecoVal=Eight;
		break;
	case 9:
		u8DecoVal=Nine;
		break;
	case 10:
		u8DecoVal=GearP;
		break;
	case 11:
		u8DecoVal=GearR;
		break;
	default:
		u8DecoVal=Error;
		break;
	}
	GPIO_vfnSetVal(&u8DecoVal);
	GPIO_vfnSetDisplay(u8SlcDsply);
}
