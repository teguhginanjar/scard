#include <stdio.h>
#include "scard.h"
#include <sys/poll.h>

int main ()
{

	SCARD_CTX * ctx;
	int ret = scard_init (&ctx, RT_OMNNIKEY_5321);		
	if (ret <= 0) return -1; 
	ret = scard_connect_picc (&ctx);	
	printf ("ret %i\n", ret);
	scard_close (&ctx);

	return 0;
}
