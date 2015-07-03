#include <stdio.h>
#include "scard.h"


int main ()
{

	SCARD_CTX * ctx;
	scard_init (&ctx, RT_OMNNIKEY_5321);		
	
	return 0;
}
