#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"

void main(void);

void main(void)
{	
	volatile int cnt = 0;
	volatile unsigned char str;
	
	/* CMTO 初期化 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	CMT0.CMCR.WORD = 0x00C2;
	CMT0.CMCNT = 1;
	CMT0.CMCOR = 374;
	IR(CMT0, CMI0) = 0;
	CMT.CMSTR0.BIT.STR0 = 1;
	
	initBASE();
	
	/* SCI2 初期化 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(SCI2) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.P50PFS.BYTE = 0x0A;
	MPC.P52PFS.BYTE = 0x0A;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	
	PORT5.PMR.BIT.B0 = 1;
	PORT5.PMR.BIT.B2 = 1;
	SCI2.SMR.BYTE = 0x00;
	SCI2.BRR = 155;
	
	SCI2.SCR.BYTE = 0x30;
	
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		while (cnt < 10) {
			cnt ++;
		}
		cnt = 0;
		if (SCI2.SSR.BIT.RDRF == 1) {
			str = SCI2.RDR;
			//SCI2.SSR.BIT.RDRF = 0;
			SCI2.TDR = str;
		}
	}
	
}
