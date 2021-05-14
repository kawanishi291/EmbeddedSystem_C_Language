#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"
#include "vect.h"

void main(void);
void Excep_ICU_IRQ13(void);


void main(void)
{	
	/* クロック初期化 */
	initBASE();
	
	/* CMTO初期化 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	CMT0.CMCR.WORD = 0x00C2;
	CMT0.CMCNT = 1;
	CMT0.CMCOR = 374;
	IR(CMT0, CMI0) = 0;
	CMT.CMSTR0.BIT.STR0 = 1;
	
	/* LED初期化 */
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	PORTJ.PODR.BIT.B3 = 1;
	PORTE.PODR.BYTE = 0x00;
	PORTE.PDR.BYTE = 0xFF;
	
	/* スイッチ初期化 */
	PORT0.PDR.BIT.B5 = 0;
	
	/* 割り込み */
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P05PFS.BIT.ISEL = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	
	ICU.IRQCR[13].BIT.IRQMD = 1;
	
	IR(ICU,IRQ13) = 0;
	IPR(ICU,IRQ13) = 1;
	IEN(ICU,IRQ13) = 1;
	
	setpsw_i();
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
	}
	
}



void Excep_ICU_IRQ13(void){
	volatile char switch3;
	
	if (PORTE.PODR.BIT.B0 == 0) {
		PORTE.PODR.BIT.B0 = 1;
	} else {
		PORTE.PODR.BIT.B0 = 0;
	}
}