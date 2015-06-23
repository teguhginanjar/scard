#ifndef __SCARD_H__
#define __SCARD_H__

#include <pcsclite.h>


typedef enum {
	DEFAULT = 0, 
	OMNNIKEY_5321;
}
READER_TYPE;


typedef struct {
	int fd;	
	int reader;
	
		
}
SCARD_CTX;


int scard_init 			(SCARD_CTX ** ctx, READER_TYPE RT);
int scard_set_speed 	(SCARD_CTX ** ctx, int speed);
int scard_exchange_data (SCARD_CTX ** ctx, BYTE * pbCmd, size_t szLengthCmd, BYTE * pbRecv, int * resplen);
int scard_close 		(SCARD_CTX ** ctx);







#endif
