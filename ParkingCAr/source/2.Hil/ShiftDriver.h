/*
 * ShiftDriver.h
 *
 *  Created on: 18 sep. 2019
 *      Author: lucky
 */

#ifndef SHIFTDRIVER_H_
#define SHIFTDRIVER_H_

typedef unsigned char uint8;

#define One 	0x6
#define Two 	0x5B
#define Three 	0x4F
#define Four 	0x66
#define Five 	0x6D
#define Six 	0x7D
#define Seven 	0x7
#define Eight 	0x7F
#define Nine 	0x67
#define Zero 	0x3F
#define GearN	0x54
#define GearR	0x50
#define GearP	0x73
#define Error 	0x76


void Shift_vfnDecode(uint8 *u8DecVal,uint8 *u8SlcDsply);

#endif /* 2_HIL_SHIFTDRIVER_H_ */
