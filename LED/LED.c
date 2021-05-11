#include "iodefine.h"

void main(void);

void main(void)
{
/* ポート初期化 */
	PORTA.PODR.BIT.B0 = 0;
	PORTA.PDR.BIT.B0 = 1;
/* LED点灯 */	
	PORTA.PODR.BIT.B0 = 1;
	
	while (1) {
		/* 終了ループ */
	}
}