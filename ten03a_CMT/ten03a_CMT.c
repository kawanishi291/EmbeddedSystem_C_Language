/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c or Main.cpp                                    */
/*  DATE        :Tue, Oct 31, 2006                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/
#include "iodefine.h"
#include "initBASE.h"

void main(void);


void main(void)
{
	volatile int cnt = 0;
	volatile int count = 0;
	volatile char switch3;
	volatile char switch4;
	
	initBASE();
	
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	PORTJ.PODR.BIT.B3 = 1;
	
	/* ポート初期化 */
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
	
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
	CMT0.CMCR.WORD = 0x00C2;
	CMT0.CMCNT = 1;
	CMT0.CMCOR = 374;
	IR(CMT0, CMI0) = 0;
	CMT.CMSTR0.BIT.STR0 = 1;
	
	
	while(1){
		switch3 = PORT0.PIDR.BIT.B5;

		
switch4 = PORT0.PIDR.BIT.B7;
		if (switch3 == 0 && switch4 == 0) {
			
		} else if (switch3 == 0) {
		
			while (IR(CMT0, CMI0) == 0) {	
				;
			}
			IR(CMT0, CMI0) = 0;
			if (count < 100 - 1){
				count ++;
			} else if (count == 99) {
				cnt ++;
				count = 0;
			}
			
			switch (cnt){
				case 1:
					PORTE.PODR.BIT.B7 = 0;
					PORTE.PODR.BIT.B0 = 1;
					break;
				case 2:
					PORTE.PODR.BIT.B0 = 0;
					PORTE.PODR.BIT.B1 = 1;
					break;
				case 3:
					PORTE.PODR.BIT.B1 = 0;
					PORTE.PODR.BIT.B2 = 1;
					break;
				case 4:
					PORTE.PODR.BIT.B2 = 0;
					PORTE.PODR.BIT.B3 = 1;
					break;
				case 5:
					PORTE.PODR.BIT.B3 = 0;
					PORTE.PODR.BIT.B4 = 1;
					break;
				case 6:
					PORTE.PODR.BIT.B4 = 0;
					PORTE.PODR.BIT.B5 = 1;
					break;
				case 7:
					PORTE.PODR.BIT.B5 = 0;
					PORTE.PODR.BIT.B6 = 1;
					break;
				case 8:
					PORTE.PODR.BIT.B6 = 0;
					PORTE.PODR.BIT.B7 = 1;
					cnt = 0;
					break;
			}
		} else if (switch4 == 0) {
			if (cnt == 0) {
				cnt = 8;
			}
			while (IR(CMT0, CMI0) == 0) {	
				;
			}
			IR(CMT0, CMI0) = 0;
			if (count < 100 - 1){
				count ++;
			} else if (count == 99) {
				cnt --;
				count = 0;
			}
			
			switch (cnt){
				case 0:
					cnt = 8;
				case 1:
					PORTE.PODR.BIT.B1 = 0;
					PORTE.PODR.BIT.B0 = 1;
					break;
				case 2:
					PORTE.PODR.BIT.B2 = 0;
					PORTE.PODR.BIT.B1 = 1;
					break;
				case 3:
					PORTE.PODR.BIT.B3 = 0;
					PORTE.PODR.BIT.B2 = 1;
					break;
				case 4:
					PORTE.PODR.BIT.B4 = 0;
					PORTE.PODR.BIT.B3 = 1;
					break;
				case 5:
					PORTE.PODR.BIT.B5 = 0;
					PORTE.PODR.BIT.B4 = 1;
					break;
				case 6:
					PORTE.PODR.BIT.B6 = 0;
					PORTE.PODR.BIT.B5 = 1;
					break;
				case 7:
					PORTE.PODR.BIT.B7 = 0;
					PORTE.PODR.BIT.B6 = 1;
					break;
				case 8:
					PORTE.PODR.BIT.B0 = 0;
					PORTE.PODR.BIT.B7 = 1;
					break;
			}
		}
	}
	
}
