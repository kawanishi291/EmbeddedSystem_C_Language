#include "iodefine.h"

void main(void);

void main(void)
{
	volatile char switch3;
	
	
	PORTJ.PODR.BIT.B3 = 0;
	PORTJ.PDR.BIT.B3 = 1;
	
	PORTJ.PODR.BIT.B3 = 1;
	
/* ポート初期化 */
	PORTE.PODR.BIT.B0 = 0;
	PORTE.PDR.BIT.B0 = 1;

	PORTE.PODR.BIT.B2 = 0;
	PORTE.PDR.BIT.B2 = 1;

	PORTE.PODR.BIT.B4 = 0;
	PORTE.PDR.BIT.B4 = 1;
	
	PORTE.PODR.BIT.B6 = 0;
	PORTE.PDR.BIT.B6 = 1;
	
	
	PORT0.PDR.BIT.B5 = 0;
	
	while(1){
		switch3 = PORT0.PIDR.BIT.B5;
		if (switch3 == 0){
			PORTE.PODR.BIT.B0 = 1;
			PORTE.PODR.BIT.B2 = 1;
			PORTE.PODR.BIT.B4 = 1;
			PORTE.PODR.BIT.B6 = 1;
		} else {
			PORTE.PODR.BIT.B0 = 0;
			PORTE.PODR.BIT.B2 = 0;
			PORTE.PODR.BIT.B4 = 0;
			PORTE.PODR.BIT.B6 = 0;
		}
	}
}