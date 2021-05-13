#include "iodefine.h"
#include "initBASE.h"

void main(void);


void main(void)
{
	volatile int cnt = 0;
	volatile char switch3;
	volatile char pre_switch3;
	volatile int flag = 0;
	volatile unsigned char bitnum = 0x00;
	
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
	
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		if (cnt < 10) {
			cnt ++;
		} else {
			cnt = 0;
			switch3 = PORT0.PIDR.BIT.B5;
			if (switch3 != pre_switch3) {
				pre_switch3 = switch3;
			} else {
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
	}
	
}
