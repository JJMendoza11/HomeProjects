#include "Debouncer.h"
#include "GPIODriver.h"
#include "Timer.h"
#include "Micros2_practica1.h"

uint_8 u8Index;

tstDbncrInfo astPinsData[enTotalPins];





void Dbncr_vfnInit(uint_8 PinVal){
	static uint_8 u8Index=0;
		astPinsData[u8Index].Pin=PinVal;
		u8Index++;
}

void Dbncr_vfnDbncr(uint_8 u8Pin2Check){
	astPinsData[u8Pin2Check].u8Shots[astPinsData[u8Pin2Check].u8Cntr]=GPIO_u8fnReadPin(astPinsData[u8Pin2Check].Pin);
	if(astPinsData[u8Pin2Check].u8Shots[astPinsData[u8Pin2Check].u8Cntr]!=astPinsData[u8Pin2Check].u8Stablestate){
		astPinsData[u8Pin2Check].u8Cntr++;
	}else{
		astPinsData[u8Pin2Check].u8Cntr=0;
	}

	if(astPinsData[u8Pin2Check].u8Shots[0]==astPinsData[u8Pin2Check].u8Shots[LastValue]){
		astPinsData[u8Pin2Check].LastStableState=astPinsData[u8Pin2Check].u8Stablestate;
		astPinsData[u8Pin2Check].u8Stablestate=astPinsData[u8Pin2Check].u8Shots[LastValue];
		astPinsData[u8Pin2Check].u8Cntr=0;
	}
}

uint_8 Dbncr_u8fnRisingEdge(uint_8 u8Pin2Check){
	if((astPinsData[u8Pin2Check].LastStableState==0)&&(astPinsData[u8Pin2Check].u8Stablestate==1)){
		astPinsData[u8Pin2Check].LastStableState=1;
		return 1;
	}else{
		return 0;
	}
}

uint_8 Dbncr_u8fnCheckStableState(uint_8 u8Pin2Check){
	return astPinsData[u8Pin2Check].u8Stablestate;
}










