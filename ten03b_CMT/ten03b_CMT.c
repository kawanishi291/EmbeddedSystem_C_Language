#include "iodefine.h"
#include "initBASE.h"

void main(void);


void main(void)
{
	volatile int cnt = 0;
	
	initBASE();
	
	/* ポート初期化 */
	PORTD.PODR.BIT.B7 = 0;
	PORTD.PDR.BIT.B7 = 1;
	PORTD.PODR.BIT.B6 = 0;
	PORTD.PDR.BIT.B6 = 1;
	PORTD.PODR.BIT.B5 = 0;
	PORTD.PDR.BIT.B5 = 1;
	PORTD.PODR.BIT.B4 = 0;
	PORTD.PDR.BIT.B4 = 1;
	PORTD.PODR.BIT.B3 = 0;
	PORTD.PDR.BIT.B3 = 1;
	PORTE.PODR.BIT.B7 = 0;
	PORTE.PDR.BIT.B7 = 1;
	PORTE.PODR.BIT.B6 = 0;
	PORTE.PDR.BIT.B6 = 1;
	PORTE.PODR.BIT.B5 = 0;
	PORTE.PDR.BIT.B5 = 1;
	PORTE.PODR.BIT.B4 = 0;
	PORTE.PDR.BIT.B4 = 1;
	PORTE.PODR.BIT.B3 = 0;
	PORTE.PDR.BIT.B3 = 1;
	PORTE.PODR.BIT.B2 = 0;
	PORTE.PDR.BIT.B2 = 1;
	PORTE.PODR.BIT.B1 = 0;
	PORTE.PDR.BIT.B1 = 1;
	PORTE.PODR.BIT.B0 = 0;
	PORTE.PDR.BIT.B0 = 1;
	
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
	CMT0.CMCR.WORD = 0x00C2;
	CMT0.CMCNT = 1;
	CMT0.CMCOR = 374;
	IR(CMT0, CMI0) = 0;
	CMT.CMSTR0.BIT.STR0 = 1;
	
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		cnt ++;
		if (cnt == 1) {
			/* :消灯 */
			PORTD.PODR.BIT.B7 = 0;
			PORTE.PODR.BIT.B0 = 0;
			/* 1点灯 */
			PORTD.PODR.BIT.B6 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
		} else if (cnt == 2) {
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
		} else if (cnt == 3) {
			/* 2消灯 */
			PORTD.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B4 = 0;
			/* 3点灯 */
			PORTD.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B2 = 1;
		} else if (cnt == 4) {
			/* 3消灯 */
			PORTD.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B3 = 0;
			/* 4点灯 */
			PORTD.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B5 = 1;
		} else if (cnt == 5) {
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
			cnt = 0;
		}
	}
	
}
