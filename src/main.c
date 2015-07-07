#include <stdio.h>
#include "scard.h"
#include <sys/poll.h>

int main ()
{

	SCARD_CTX * ctx;
	scard_init (&ctx, RT_OMNNIKEY_5321);		
	int ret = scard_connect_picc (&ctx);	
	printf ("ret %i\n", ret);
	scard_close (&ctx);

	return 0;
}
