#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"
#include "vect.h"

void main(void);
void Excep_ICU_IRQ13(void);


void main(void)
{	
	volatile int cnt = 0;
	volatile int count = 0;
	
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
	PORTD.PODR.BIT.B3 = 0;
	PORTD.PDR.BIT.B3 = 0;
	
	PORTD.PODR.BIT.B4 = 0;
	PORTD.PDR.BIT.B4 = 0;
	
	PORTD.PODR.BIT.B5 = 0;
	PORTD.PDR.BIT.B5 = 0;
	
	PORTD.PODR.BIT.B6 = 0;
	PORTD.PDR.BIT.B6 = 0;
	
	PORTD.PODR.BIT.B7 = 0;
	PORTD.PDR.BIT.B7 = 0;
	
	PORTE.PODR.BYTE = 0x00;
	PORTE.PDR.BYTE = 0xFF;
	
	/* スイッチ初期化 */
	PORT0.PDR.BIT.B5 = 0;
	
	/* 割り込み */
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P05PFS.BIT.ISEL = 1;
	MPC.P07PFS.BIT.ISEL = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	
	ICU.IRQCR[13].BIT.IRQMD = 1;
	ICU.IRQCR[15].BIT.IRQMD = 1;
	
	IR(ICU,IRQ13) = 0;
	IPR(ICU,IRQ13) = 1;
	IEN(ICU,IRQ13) = 1;
	IR(ICU,IRQ15) = 0;
	IPR(ICU,IRQ15) = 1;
	IEN(ICU,IRQ15) = 1;
	
	setpsw_i();
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		while (cnt < 100) {
			cnt ++;
		}
		cnt = 0;
		count ++;
		if (count < 40) {
			/* :消灯 */
			PORTD.PODR.BIT.B7 = 0;
			PORTE.PODR.BIT.B0 = 0;
			/* 1点灯 */
			PORTD.PODR.BIT.B6 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
		} else if (count < 80) {
			/* 1消灯 */
			PORTD.PODR.BIT.B6 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			/* 2点灯 */
			PORTD.PODR.BIT.B5 = 1;
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B6 = 1;
		} else if (count < 120) {
			/* 2消灯 */
			PORTD.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B4 = 0;
			/* 3点灯 */
			PORTD.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B2 = 1;
		} else if (count < 160) {
			/* 3消灯 */
			PORTD.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B3 = 0;
			/* 4点灯 */
			PORTD.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B5 = 1;
		} else if (count < 200) {
			/* 4消灯 */
			PORTD.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B6 = 0;
			/* :点灯 */
			PORTD.PODR.BIT.B7 = 1;
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
		} else {
			count = 0;
		}
	}
	
}



void Excep_ICU_IRQ13(void)
{	
	PORTD.PDR.BIT.B3 = 1;
	PORTD.PDR.BIT.B4 = 1;
	PORTD.PDR.BIT.B5 = 1;
	PORTD.PDR.BIT.B6 = 1;
	PORTD.PDR.BIT.B7 = 1;
}

void Excep_ICU_IRQ15(void)
{
	PORTD.PDR.BIT.B3 = 0;
	PORTD.PDR.BIT.B4 = 0;
	PORTD.PDR.BIT.B5 = 0;
	PORTD.PDR.BIT.B6 = 0;
	PORTD.PDR.BIT.B7 = 0;
}