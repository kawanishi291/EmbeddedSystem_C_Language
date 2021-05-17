
#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"

void main(void);
void Excep_ICU_IRQ13(void);


void main(void)
{	
	volatile int cnt = 0;
	volatile int id = 0;
	volatile char check;
	
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
	
	/* LED初期化 */
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	PORTJ.PODR.BIT.B3 = 1;
	PORTE.PODR.BYTE = 0x00;
	PORTE.PDR.BYTE = 0xFF;
	
	/* S12AD */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(S12AD) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PD0PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	
	S12AD.ADCSR.BIT.ADCS = 1;
	S12AD.ADANS0.WORD = 0x0100;
	S12AD.ADCSR.BIT.ADST = 1;
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		while (cnt < 10) {
			cnt ++;
		}
		cnt = 0;
		S12AD.ADCER.BIT.ADRFMT = 0;
		check = S12AD.ADDR8 >> 4;
		id = (int)check;
		if (id <= 0) {
			PORTE.PODR.BIT.B7 = 1;
		} else if (id <= 64) {
			PORTE.PODR.BIT.B5 = 1;
		} else if (id <= 129) {
			PORTE.PODR.BIT.B3 = 1;
		} else if (id <= 192) {
			PORTE.PODR.BIT.B1 = 1;
		} else {
			PORTE.PODR.BYTE = 0x00;
		}
	}
	
}
