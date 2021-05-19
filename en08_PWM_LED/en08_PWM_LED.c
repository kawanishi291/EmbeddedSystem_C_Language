#include <machine.h>
#include "iodefine.h"
#include "initBASE.h"

void main(void);
void Excep_ICU_IRQ13(void);


void main(void)
{	
	volatile int cnt = 0;
	volatile short int t1;
	volatile short int t2;
	
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
	MPC.P46PFS.BIT.ASEL = 1;
	MPC.P47PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	
	S12AD.ADCSR.BIT.ADCS = 1;
	S12AD.ADANS0.WORD = 0x00C0;
	S12AD.ADCSR.BIT.ADST = 1;
	
	/* MTU2初期化 */
	SYSTEM.PRCR.WORD = 0xA502;
	MSTP(MTU) = 0;
	SYSTEM.PRCR.WORD = 0xA500;
	
	MPC.PWPR.BIT.B0WI = 0;
	MPC.PWPR.BIT.PFSWE = 1;
	MPC.PE1PFS.BIT.ASEL = 1;
	MPC.PE2PFS.BIT.ASEL = 1;
	MPC.PWPR.BIT.PFSWE = 0;
	MPC.PWPR.BIT.B0WI = 1;
	
	
	PORTE.PMR.BIT.B1 = 1;
	PORTE.PMR.BIT.B2 = 1;
	

	SYSTEM.PRCR.WORD = 0xA502;		
	MSTP(MTU) = 0;					
	SYSTEM.PRCR.WORD = 0xA500;		

	MPC.PWPR.BIT.B0WI	= 0;		
	MPC.PWPR.BIT.PFSWE	= 1;		
		
	MPC.PE1PFS.BIT.PSEL = 0x1;		
	MPC.PE2PFS.BIT.PSEL = 0x1;		
		
	MPC.PWPR.BIT.PFSWE	= 0;		
	MPC.PWPR.BIT.B0WI	= 1;		

	PORTE.PMR.BIT.B1 = 1;			
	PORTE.PMR.BIT.B2 = 1;			

	MTU4.TCR.BIT.TPSC = 3;			
	MTU4.TCR.BIT.CKEG = 0;			
	MTU4.TCR.BIT.CCLR = 1;			

		
	MTU4.TMDR.BIT.MD = 2;			
		
	MTU.TOER.BIT.OE4A = 1;			
	MTU.TOER.BIT.OE4C = 1;			

	MTU4.TIORH.BIT.IOA = 6;			
	MTU4.TIORH.BIT.IOB = 5;			
	MTU4.TIORL.BIT.IOC = 6;			
	MTU4.TIORL.BIT.IOD = 5;			

		
	MTU4.TCNT = 0;					

	MTU4.TGRA = 4095;				
	MTU4.TGRB = 0;					
	MTU4.TGRC = 4095; 				
	MTU4.TGRD = 0;					
	MTU.TSTR.BIT.CST4 = 1;
	
	
	while(1){
		while (IR(CMT0, CMI0) == 0) {
			;
		}
		IR(CMT0, CMI0) = 0;
		while (cnt < 10) {
			cnt ++;
		}
		cnt = 0;
		t1 = S12AD.ADDR6;
		t2 = S12AD.ADDR7;
		MTU4.TGRB = t1;
		MTU4.TGRD = t2;
	}
	
}
