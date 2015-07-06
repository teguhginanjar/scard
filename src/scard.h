#ifndef __SCARD_H__
#define __SCARD_H__

#include "scard-internal.h"

typedef enum {
	RT_DEFAULT = 0, 
	RT_OMNNIKEY_5321
}
READER_TYPE;


typedef struct _SCARD_CTX {
	int fd;	
	int reader;
	
	SCARDCONTEXT hContext;
	LPTSTR mszReaders;
	SCARDHANDLE hCard;
	DWORD dwReaders, dwActiveProtocol, dwRecvLength;

	SCARD_IO_REQUEST pioSendPci;
	BYTE pbRecvLength[258];
	SCARD_READERSTATE * rgReaderStates_t;
	SCARD_READERSTATE rgReaderStates[1];		
}
SCARD_CTX;

int scard_connect_picc (SCARD_CTX ** ctx);
int scard_init 			(SCARD_CTX ** ctx, READER_TYPE RT);
int scard_set_speed 	(SCARD_CTX ** ctx, int speed);
int scard_exchange_data (SCARD_CTX ** ctx, int timeout, BYTE * pbCmd, size_t szLengthCmd, BYTE * pbRecv, int * resplen);
int scard_close 		(SCARD_CTX ** ctx);







#endif
