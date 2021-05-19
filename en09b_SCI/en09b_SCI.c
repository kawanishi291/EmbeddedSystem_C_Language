#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"
#include "vect.h"


void main(void);

volatile char msg;

void main(void)
{	
	volatile int cnt = 0;
	
	/* CMTO初期化 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(CMT0) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	CMT0.CMCR.WORD = 0x00C2;
	CMT0.CMCNT = 1;
	CMT0.CMCOR = 374;
	IR(CMT0, CMI0) = 0;
	CMT.CMSTR0.BIT.STR0 = 1;
	
	/* クロック初期化 */
	initBASE();
	
	/* SCI2 */
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
	
	/* 割り込み */
	SCI2.SCR.BIT.RIE = 1;
	SCI2.SCR.BIT.TIE = 0;
	SCI2.SCR.BIT.TEIE = 0;
	
	IPR(SCI2,RXI2) = 1;
	IPR(SCI2,TXI2) = 1;
	IPR(SCI2,TEI2) = 1;
	
	IEN(SCI2,RXI2) = 1;
	IEN(SCI2,TXI2) = 1;
	IEN(SCI2,TEI2) = 1;
	
	SCI2.SCR.BYTE = 0xF4;
	
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		while (cnt < 10) {
			cnt ++;
		}
		cnt = 0;
	}
	
}


void Excep_SCI2_RXI2(void)
{
	if (SCI2.SSR.BIT.RDRF == 1) {
		msg  = SCI2.RDR;
		SCI2.SSR.BIT.RDRF = 0;
	}
	SCI2.SCR.BIT.RIE = 0;
	SCI2.SCR.BIT.TEIE = 1;
}

void Excep_SCI2_TXI2(void)
{
	if (SCI2.SSR.BIT.TDRE == 0) {
		SCI2.TDR = msg;
		SCI2.SSR.BIT.TDRE = 1;
	}
	SCI2.SCR.BIT.TEIE = 0;
	SCI2.SCR.BIT.TIE = 1;
}


void Excep_SCI2_TEI2(void)
{
	SCI2.SCR.BIT.RIE = 1;
	SCI2.SCR.BIT.TIE = 0;
}