/*
 * TPWDriver.c
 *
 *  Created on: 4 jul. 2019
 *      Author: lucky
 */


/*-----------------------------------------------------------------------------------------------*/
/*-----------------------------------------PWM Functions-----------------------------------------*/
/*-----------------------------------------------------------------------------------------------*/

#include "MKL25Z4.h"
#include "PWMDriver.h"

static uint16_t u16ModVal=0;

	void PWM_vfnDriverInit (void){
	//---PWM Initialization---
		SIM->SOPT2|=SIM_SOPT2_TPMSRC(1); 										//SELECT THE CLOCK
		SIM->SOPT2|=SIM_SOPT2_PLLFLLSEL(0);										//PLL OR FLL
		SIM->SCGC6|=SIM_SCGC6_TPM0_MASK;										//TPM0 activation
		TPM0->SC|=TPM_SC_PS(6);													//Division of CLK
		TPM0->SC|=TPM_SC_CMOD(1);												//CLK
		TPM0->SC|=TPM_SC_CPWMS(0);												//Up counting
		TPM0->MOD= 6562;															//Period of 20ms
		TPM0->CONTROLS[0].CnSC|=TPM_CnSC_ELSB_MASK|TPM_CnSC_MSB_MASK;			//HIGH TRUE
		TPM0->CONTROLS[1].CnSC|=TPM_CnSC_ELSB_MASK|TPM_CnSC_MSB_MASK;			//HIGH TRUE
		TPM0->CONF|=TPM_CONF_DBGMODE_MASK;										//Debug ON
		//---Initialization oPWM---
		SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;										//PortD Activation
		PORTD->PCR[0]|=PORT_PCR_MUX(4);
		//PORTD->PCR[1]|=PORT_PCR_MUX(4);
	}

	uint8_t PWM_bInitialPosition (void){
	//Move gauge to 0°
		uint16_t i=0;
		TPM0->CONTROLS[0].CnV=Origen;
		TPM0->CONTROLS[1].CnV=End;
		while(i!=0xFFF){
			i++;
		}
		return 1;
	}


	void PWM_Acc_or_Dec(uint8_t u8Km){
		u16ModVal=u8Km*55;
		TPM0->CONTROLS[0].CnV=u16ModVal;
	}


	void PWM_vfnLowBrake(uint8_t *u8Gears){
		u16ModVal--;
		TPM0->CONTROLS[0].CnV=u16ModVal;
		if(u16ModVal<ThrdGearMaxVal){
			*u8Gears&=~(1<<7);
		}else{
			if(u16ModVal<ScndGearMaxVal){
				*u8Gears&=~(1<<6);
			}else{
				if(u16ModVal<FrstGearMaxVal){
					*u8Gears&=~(1<<5);
				}else{
					if(!u16ModVal){
						*u8Gears&=~(1<<4);
					}
				}
			}
		}
	}

	uint8_t PWM_bfnAngleAdjustment (uint8_t bNewAngle){
	//Make a relation between °C and angle degrees through the Duty Cycle
		uint16_t	sAngleVal=0;												//Formula (50°C,135°)
		if(bNewAngle>128){
			sAngleVal=(39*bNewAngle)-4952;
			if(bNewAngle>148){
				TPM0->CONTROLS[0].CnV=End;
			}
			else{
				TPM0->CONTROLS[0].CnV=sAngleVal;
			}
		}
		if(bNewAngle<128){
			sAngleVal=5032+(-39*bNewAngle);
			if(bNewAngle<108){
				TPM0->CONTROLS[1].CnV=End;
			}
				else{
					TPM0->CONTROLS[1].CnV=sAngleVal;
				}
		}

		if(bNewAngle==128){
			TPM0->CONTROLS[0].CnV=40;
			TPM0->CONTROLS[1].CnV=40;
		}
		return 1;
	}

