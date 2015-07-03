#include <stdio.h>
#include "scard.h"


int main ()
{

	SCARD_CTX * ctx;
	scard_init (&ctx, RT_DEFAULT);		
	
	return 0;
}
