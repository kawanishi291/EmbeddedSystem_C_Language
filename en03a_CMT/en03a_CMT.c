#include "iodefine.h"
#include "initBASE.h"

void main(void);


void main(void)
{
	volatile int cnt = 0;
	
	initBASE();
	
	/* ポート初期化 */
	PORTA.PODR.BIT.B0 = 0;
	PORTA.PDR.BIT.B0 = 1;
	PORTA.PODR.BIT.B1 = 0;
	PORTA.PDR.BIT.B1 = 1;
	
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
		if (cnt < 100 - 1){
			cnt ++;
		} else {
			if (PORTA.PODR.BIT.B0 == 0) {
				/* LED 1 */
				PORTA.PODR.BIT.B0 = 1;
				PORTA.PODR.BIT.B1 = 0;
			} else {
				/* LED 2 */
				PORTA.PODR.BIT.B0 = 0;
				PORTA.PODR.BIT.B1 = 1;
			}
			cnt = 0;
		}
	}
	
}
