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
uint8 u8IOReg=0;
uint8 u8Speed=0;
uint8 GearStatus=0;
static uint16 a=0;

void Gear_vfnGear(void){
	switch (GearStatus){
	case 0:
		if(Dbncr(enBrake)){
			if(Dbncr(enClutch)){
				if(Dbncr(enGearUp)){
					u8IOReg=16;
					GearStatus=1;
				}else if(Dbncr(enGearDwn)){
					u8IOReg=11<<4;
					GearStatus=11;
					Timer_vfn4DsplyVal(u8IOReg>>4);
				}
			}
		}
		break;
	case 1:
		if((Dbncr(enClutch))&&(u8IOReg&(1<<4))){
			Timer_vfn4DsplyVal(u8IOReg>>4);
			if(Dbncr(enAcc)){
				u8IOReg|=(1<<2);
				GearStatus=2;
			}
		}
		break;
	case 2:
		if(!Dbncr(enClutch)){
			vfnTMR();
			u8Speed++;
			GearStatus=3;
			vfnDriveState();
		}
		break;
	case 3:
		if(Dbncr(enAcc)){
			u8IOReg|=AccFlag;
		}else{
			u8IOReg&=~AccFlag;
		}
		if(u8Seg==160){
			a=0;
			if(Dbncr(enAcc)){
				if(u8Speed<30){
					vfnTMR();
					u8Speed++;
				}else{
					if(u8Speed){
						vfnTMRLess();
						u8Speed--;
					}
				}
			}else{
				if(Dbncr(enBrake)){
					GearStatus=10;
				}else if (Dbncr(enClutch)){
					GearStatus=4;
				}else{
					if(u8Speed<30){
						vfnTMRLess();
						u8Speed--;
						if((u8Speed%30==0)){
							u8IOReg-=16;
							Timer_vfn4DsplyVal(u8IOReg>>4);
							GearStatus=0;
						}
						if(!u8Speed){
							GearStatus=0;
							u8IOReg=10<<4;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
					}else{
						if(u8Speed){
							vfnTMRLess();
							u8Speed--;
						}
					}
				}
			}
			PWM_Acc_or_Dec(u8Speed);
		}
		if(u8Speed>30){
			vfnTMRLess();
			u8Speed--;
		}
		break;
	case 4:
		if(Dbncr(enClutch)){
			if(Dbncr(enGearUp)){
				u8IOReg+=16;
				GearStatus=5;
				Timer_vfn4DsplyVal(u8IOReg>>4);
			}else{
				if((u8Speed)&&(u8Seg==160)){
					vfnTMRLess();
					u8Speed--;
				}
			}
		}else{
			GearStatus=3;
		}
		PWM_Acc_or_Dec(u8Speed);
		break;
	case 5:
		if(u8Seg==160){
			if(!Dbncr(enClutch)){
				if(Dbncr(enAcc)){
					if(u8Speed<60){
						vfnTMR();
						u8Speed++;
					}else{
						if(u8Speed){
							vfnTMRLess();
							u8Speed--;
						}
					}
				}else{
					if(Dbncr(enBrake)){
						GearStatus=10;
					}else if (Dbncr(enClutch)){
						//GearStatus=6;
					}else{
						if(u8Speed<60){
							vfnTMRLess();
							u8Speed--;
							if((u8Speed%30==0)){
								u8IOReg-=16;
								Timer_vfn4DsplyVal(u8IOReg>>4);
								GearStatus=10;
							}
							if(!u8Speed){
								GearStatus=0;
								u8IOReg=0;
								Timer_vfn4DsplyVal(u8IOReg>>4);
							}
						}else{
							if(u8Speed){
								vfnTMRLess();
								u8Speed--;
							}
						}
					}
				}
			}else{
				if(u8Speed>45){
					GearStatus=6;
				}else{
					if(u8Speed){
						vfnTMRLess();
						u8Speed--;
						if((u8Speed%30==0)){
							u8IOReg-=16;
							Timer_vfn4DsplyVal(u8IOReg>>4);
							GearStatus=10;
						}
						if(!u8Speed){
							GearStatus=0;
							u8IOReg=0;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
					}
				}
			}
			PWM_Acc_or_Dec(u8Speed);
		}
		if(u8Speed>60){
			vfnTMRLess();
			u8Speed--;
		}
		break;
	case 6:
		if(Dbncr(enClutch)){
			if(Dbncr(enGearUp)){
				u8IOReg+=16;
				GearStatus=7;
				Timer_vfn4DsplyVal(u8IOReg>>4);
			}else{
				if(Dbncr(enGearDwn)){
					u8IOReg-=16;
					GearStatus=3;
					Timer_vfn4DsplyVal(u8IOReg>>4);
				}else{
					if((u8Speed)&&(u8Seg==160)){
						vfnTMRLess();
						u8Speed--;
						if((u8Speed%30==0)){
							u8IOReg-=16;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
						if(!u8Speed){
							GearStatus=0;
							u8IOReg=0;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
					}
				}
			}
		}else{
			GearStatus=5;
		}
		PWM_Acc_or_Dec(u8Speed);
		break;
	case 7:
		if(u8Seg==160){
			if(!Dbncr(enClutch)){
				if(Dbncr(enAcc)){
					if(u8Speed<90){
						vfnTMR();
						u8Speed++;
					}else{
						if(u8Speed){
							vfnTMRLess();
							u8Speed--;
						}
					}
				}else{
					if(Dbncr(enBrake)){
						GearStatus=10;
					}else if (Dbncr(enClutch)){
						//GearStatus=6;
					}else{
						if(u8Speed<90){
							vfnTMRLess();
							u8Speed--;
							if((u8Speed%30==0)){
								u8IOReg-=16;
								Timer_vfn4DsplyVal(u8IOReg>>4);
								GearStatus=10;
							}
							if(!u8Speed){
								GearStatus=0;
								u8IOReg=0;
								Timer_vfn4DsplyVal(u8IOReg>>4);
							}
						}else{
							if(u8Speed){
								vfnTMRLess();
								u8Speed--;
							}
						}
					}
				}
			}else{
				if(u8Speed>75){
					GearStatus=8;
				}else{
					if(u8Speed){
						vfnTMRLess();
						u8Speed--;
						if((u8Speed%30==0)){
							u8IOReg-=16;
							Timer_vfn4DsplyVal(u8IOReg>>4);
							GearStatus=10;
						}
						if(!u8Speed){
							GearStatus=0;
							u8IOReg=0;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
					}
				}
			}
			PWM_Acc_or_Dec(u8Speed);
		}
		if(u8Speed>90){
			vfnTMRLess();
			u8Speed--;
		}
		break;
	case 8:
		if(Dbncr(enClutch)){
			if(Dbncr(enGearUp)){
				u8IOReg+=16;
				GearStatus=9;
				Timer_vfn4DsplyVal(u8IOReg>>4);
			}
			else{
				if(Dbncr(enGearDwn)){
					u8IOReg-=16;
					GearStatus=5;
					Timer_vfn4DsplyVal(u8IOReg>>4);
				}
				if((u8Speed)&&(u8Seg==160)){
					vfnTMRLess();
					u8Speed--;
					if((u8Speed%30==0)){
						u8IOReg-=16;
						Timer_vfn4DsplyVal(u8IOReg>>4);
					}
					if(!u8Speed){
						GearStatus=0;
						u8IOReg=0;
						Timer_vfn4DsplyVal(u8IOReg>>4);
					}
				}
			}
		}else{
			GearStatus=3;
		}
		PWM_Acc_or_Dec(u8Speed);
		break;
	case 9:
		if(u8Seg==160){
			if(!Dbncr(enClutch)){
				if(Dbncr(enAcc)){
					if(u8Speed<120){
						vfnTMR();
						u8Speed++;
					}
				}else{
					if(Dbncr(enBrake)){
						GearStatus=10;
					}else if (Dbncr(enClutch)){
						//GearStatus=6;
					}else{
						if(u8Speed){
							vfnTMRLess();
							u8Speed--;
							if((u8Speed%30==0)){
								u8IOReg-=16;
								Timer_vfn4DsplyVal(u8IOReg>>4);
								GearStatus=10;
							}
							if(!u8Speed){
								GearStatus=0;
								u8IOReg=0;
								Timer_vfn4DsplyVal(u8IOReg>>4);
							}
						}
					}
				}
				PWM_Acc_or_Dec(u8Speed);
			}else{
				GearStatus=12;
			}
		}
		if(u8Speed>120){
			vfnTMRLess();
			u8Speed--;
		}
		break;
	case 10:
			if(Dbncr(enBrake)){
				if(u8Speed){
					u8Speed--;
					vfnTMRLess();
				}else{
					GearStatus=0;
					u8IOReg=10<<4;
					Timer_vfn4DsplyVal(u8IOReg>>4);
					break;
				}
				if((u8Speed%30==0)){
					u8IOReg-=16;
					Timer_vfn4DsplyVal(u8IOReg>>4);
				}
			}else if(Dbncr(enAcc)){
				if(u8Speed>90){
					GearStatus=9;
					u8IOReg=(4<<4);
				}else if((u8Speed<90)&&(u8Speed>60)){
					GearStatus=7;
					u8IOReg=(3<<4);
				}else if((u8Speed<60)&&(u8Speed>30)){
					GearStatus=5;
					u8IOReg=(2<<4);
				}else if((u8Speed<30)&&(u8Speed>0)){
					GearStatus=3;
					u8IOReg=(1<<4);
				}
				Timer_vfn4DsplyVal(u8IOReg>>4);
			}else{
				if((u8Speed)&&(u8Seg==160)){
					vfnTMRLess();
					u8Speed--;
					if((u8Speed%30==0)&&(u8Seg==160)){
						u8IOReg-=16;
						Timer_vfn4DsplyVal(u8IOReg>>4);
					}
					if(!u8Speed){
						GearStatus=0;
						u8IOReg=10<<4;
						Timer_vfn4DsplyVal(u8IOReg>>4);
					}
				}
			}

			PWM_Acc_or_Dec(u8Speed);
			break;
	case 11:
		if(u8Seg==160){
				if(!Dbncr(enClutch)){
					if(Dbncr(enAcc)){
						if(u8Speed<50){
							vfnTMR();
							u8Speed++;
						}
					}else{
						if(Dbncr(enBrake)){
							GearStatus=10;
						}else if (Dbncr(enClutch)){
							//GearStatus=6;
						}else{
							if(u8Speed){
								vfnTMRLess();
								u8Speed--;
								if(!u8Speed){
									GearStatus=0;
									u8IOReg=10<<4;
									Timer_vfn4DsplyVal(u8IOReg>>4);
								}
							}
						}
					}
					PWM_Acc_or_Dec(u8Speed);
				}
			}
			break;
		break;
	case 12:
		if(Dbncr(enClutch)){
					if(Dbncr(enGearDwn)){
						u8IOReg-=16;
						GearStatus=7;
						Timer_vfn4DsplyVal(u8IOReg>>4);
					}
					if((u8Speed)&&(u8Seg==160)){
						vfnTMRLess();
						u8Speed--;
						if((u8Speed%30==0)){
							u8IOReg-=16;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
						if(!u8Speed){
							GearStatus=0;
							u8IOReg=0;
							Timer_vfn4DsplyVal(u8IOReg>>4);
						}
					}
				}else{
					GearStatus=9;
				}
				PWM_Acc_or_Dec(u8Speed);
				break;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*----------------------------------Posiblemente esto sea basura-------------------------------------------*/
/*---------------------------------------------------------------------------------------------------------*/
void Gear_vfnStartModule(void){
	if(Dbncr(enClutch)){
		u8IOReg|=ClutchFlag;
		if(Check_GearUP_Bttn()){
			u8IOReg+=16;
		}else{
			/*No Used*/
		}
	}else{
		u8IOReg&=~ClutchFlag;
	}
}

void Check_Brake_Bttn(void){
	if(u8IOReg<3){
		if(Dbncr(enBrake)){
			Gear_vfnStartModule();
		}else{
			/*No Used*/
		}
	}else{
		if(u8IOReg>=18){
			Gear_u8AccModule();
		}
	}
}

uint8 Check_GearUP_Bttn(void){
	if(Dbncr(enGearUp)){
		return 1;
	}else{
		return 0;
	}
}

uint8 Gear_u8AccModule(void){
	if(!u8Speed){
		if((Dbncr(enClutch))&&(u8IOReg&(1<<4))){
			Timer_vfn4DsplyVal(u8IOReg>>4);
			if(Dbncr(enAcc)){
				u8IOReg|=(1<<2);
			}
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

void Check_Acc_Bttn(void){
	if(Dbncr(enAcc)){
		u8IOReg|=ClutchFlag;
		u8IOReg|=(Check_GearUP_Bttn()<<4);
	}else{
		u8IOReg&=~ClutchFlag;
	}
}


