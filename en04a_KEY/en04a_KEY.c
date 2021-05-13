#include "iodefine.h"
#include "initBASE.h"

void main(void);


void main(void)
{
	volatile int cnt = 0;
	volatile char switch3;
	// volatile char switch4;
	volatile int flag = 0;
	volatile unsigned char bitnum = 0x00;
	
	initBASE();
	
	/* クロック初期化 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	/* CMTO初期化 */
	CMT0.CMCR.WORD = 0x00C2;
	CMT0.CMCNT = 1;
	CMT0.CMCOR = 374;
	IR(CMT0, CMI0) = 0;
	CMT.CMSTR0.BIT.STR0 = 1;
	
	/* LED初期化 */
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	PORTJ.PODR.BIT.B3 = 1;
	PORTE.PODR.BIT.B0 = 0;
	PORTE.PDR.BIT.B0 = 1;
	PORTE.PODR.BIT.B1 = 0;
	PORTE.PDR.BIT.B1 = 1;
	PORTE.PODR.BIT.B2 = 0;
	PORTE.PDR.BIT.B2 = 1;
	PORTE.PODR.BIT.B2 = 0;
	PORTE.PDR.BIT.B2 = 1;
	PORTE.PODR.BIT.B3 = 0;
	PORTE.PDR.BIT.B3 = 1;
	PORTE.PODR.BIT.B4 = 0;
	PORTE.PDR.BIT.B4 = 1;
	PORTE.PODR.BIT.B5 = 0;
	PORTE.PDR.BIT.B5 = 1;
	PORTE.PODR.BIT.B6 = 0;
	PORTE.PDR.BIT.B6 = 1;
	PORTE.PODR.BIT.B7 = 0;
	PORTE.PDR.BIT.B7 = 1;
	
	
	
	/* スイッチ初期化 */
	PORT0.PDR.BIT.B5 = 0;
	
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		switch3 = PORT0.PIDR.BIT.B5;
		//switch4 = PORT0.PIDR.BIT.B7;
		if (switch3 == 0) {
			if (flag == 0) {
				PORTE.PODR.BYTE &= ~bitnum;
				bitnum ++;
				PORTE.PODR.BYTE |= bitnum;
				flag = 1;
			}
		} else {
			flag = 0;
		}
	}
	
}
