#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"
#include "vect.h"

void main(void);
void Excep_CMT1_CMI1(void);


void main(void)
{
	initBASE();
	
	/* LED */
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	PORTJ.PODR.BIT.B3 = 1;
	PORTE.PODR.BYTE = 0x00;
	PORTE.PDR.BYTE = 0xFF;
	
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT1) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
	CMT1.CMCR.WORD = 0x00C2;
	CMT1.CMCNT = 0;
	CMT1.CMCOR = 37500 - 1;
	IR(CMT1, CMI1) = 0;
	IPR(CMT1, CMI1) = 1;
	IEN(CMT1, CMI1) = 1;
	CMT.CMSTR0.BIT.STR1 = 1;
	
	setpsw_i();
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {	
			;
		}
	}
	
}


void Excep_CMT1_CMI1(void)
{
	if (PORTE.PODR.BIT.B0 == 0){
		PORTE.PODR.BIT.B0 = 1;
		PORTE.PODR.BIT.B1 = 0;
	} else {
		PORTE.PODR.BIT.B0 = 0;
		PORTE.PODR.BIT.B1 = 1;
	}
}