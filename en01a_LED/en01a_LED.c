#include "iodefine.h"

void main(void);

void main(void)
{
	PORTE.PODR.BIT.B0 = 0;
	PORTE.PDR.BIT.B0 = 1;
	
	PORTE.PODR.BIT.B0 = 1;
	
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	
	PORTJ.PODR.BIT.B3 = 1;
	
	while(1){
		
	}
}

