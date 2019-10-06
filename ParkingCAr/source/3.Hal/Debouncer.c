#include "Debouncer.h"
#include "GPIODriver.h"
#include "Timer.h"
#include "Micros2_practica1.h"


tstDbncrInfo astPinsData[enTotalPins];

uint_8 Dbncr_vfnRiseDec(uint_8 SearchPin);

void DbncrInit(uint_8 PinVal){
	static uint_8 u8Index=0;
		astPinsData[u8Index].Pin=PinVal;
		u8Index++;
}

uint_8 Dbncr(uint_8 u8Pin2Check){
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
		if((astPinsData[u8Pin2Check].LastStableState==0)&&(astPinsData[u8Pin2Check].u8Stablestate==1)){
			return 1;
		}else{
			if(astPinsData[u8Pin2Check].u8Stablestate==1){
				return 1;
			}else{
				return 0;
			}
		}
	}else{
		return 0;
	}

}









