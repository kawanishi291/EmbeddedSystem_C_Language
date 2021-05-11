#include "iodefine.h"

void main(void);

void main(void)
{
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	
	PORTJ.PODR.BIT.B3 = 1;
	
	PORTE.PODR.BIT.B0 = 0;
	PORTE.PDR.BIT.B0 = 1;
	
	PORTE.PODR.BIT.B0 = 1;
	
	PORTE.PODR.BIT.B2 = 0;
	PORTE.PDR.BIT.B2 = 1;
	
	PORTE.PODR.BIT.B2 = 1;
	
	PORTE.PODR.BIT.B4 = 0;
	PORTE.PDR.BIT.B4 = 1;
	
	PORTE.PODR.BIT.B4 = 1;
	
	PORTE.PODR.BIT.B6 = 0;
	PORTE.PDR.BIT.B6 = 1;
	
	PORTE.PODR.BIT.B6 = 1;
	
	
	while(1){
		
	}
}