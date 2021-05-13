#include "iodefine.h"
#include "initBASE.h"

void main(void);
void DEL7SEG(int *num);
void SET7SEG(int *num);

void main(void)
{
	volatile int cnt = 0;
	volatile char switch3;
	volatile char pre_switch3;
	volatile int flag = 0;
	volatile int num = 0;
	
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
	PORTD.PODR.BIT.B6 = 0;
	PORTD.PDR.BIT.B6 = 1;
	PORTD.PODR.BIT.B6 = 1;
	PORTD.PODR.BIT.B5 = 0;
	PORTD.PDR.BIT.B5 = 1;
	PORTD.PODR.BIT.B5 = 1;
	PORTD.PODR.BIT.B4 = 0;
	PORTD.PDR.BIT.B4 = 1;
	PORTD.PODR.BIT.B4 = 1;
	PORTD.PODR.BIT.B3 = 0;
	PORTD.PDR.BIT.B3 = 1;
	PORTD.PODR.BIT.B3 = 1;
	PORTE.PODR.BYTE = 0x00;
	PORTE.PDR.BYTE = 0xFF;
	PORTE.PODR.BIT.B0 = 1;
	PORTE.PODR.BIT.B1 = 1;
	PORTE.PODR.BIT.B2 = 1;
	PORTE.PODR.BIT.B3 = 1;
	PORTE.PODR.BIT.B4 = 1;
	PORTE.PODR.BIT.B5 = 1;
	
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
						DEL7SEG(&num);
						num ++ ;
						SET7SEG(&num);
						flag = 1;
					}
				} else {
					flag = 0;
				}
			}
		}
	}
	
}


void DEL7SEG(int *num)
{
	switch (*num) {
		case 0:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B5 = 0;
			break;
		case 1:
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			break;
		case 2:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
		case 3:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
		case 4:
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
		case 5:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
		case 6:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
		case 7:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B5 = 0;
			break;
		case 8:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
		case 9:
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B1 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B3 = 0;
			PORTE.PODR.BIT.B5 = 0;
			PORTE.PODR.BIT.B6 = 0;
			break;
	}
}
void SET7SEG(int *num)
{
	switch (*num) {
		case 1:
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			break;
		case 2:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 3:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 4:
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B5 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 5:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B5 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 6:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B5 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 7:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B5 = 1;
			break;
		case 8:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B5 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 9:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B5 = 1;
			PORTE.PODR.BIT.B6 = 1;
			break;
		case 10:
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B1 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B3 = 1;
			PORTE.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B5 = 1;
			*num = 0;
			break;
			
	}
}
