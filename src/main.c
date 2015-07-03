#include <stdio.h>
#include "scard.h"


int main ()
{

	SCARD_CTX * ctx;
	scard_init (&ctx, DEFAULT);		
	
	return 0;
}
