#include "scard.h"


int _scard_init (SCARD_CTX ** ctx, READER_TYPE RT)
{
	
	(*ctx) = (SCARD_CTX *) malloc (sizeof (SCARD_CTX));
	if ((*ctx) == NULL) {

		return -1;
	} 	
	
	int i , iReaders;
	char * ptr, ** readers;
	DWORD dwReadersOld = 0;
	
	DWORD ret = SCardEstablishContext (SCARD_SCOPE_SYSTEM, NULL, NULL, &(*ctx)->hContext);
	CHECK ("ESTABLISH CONTEXT", ret);
	(*ctx)->rgReaderStates[0].szReader = "\\\\?PnP\\Notification";
	(*ctx)->rgReaderStates[0].dwCurrentState = SCARD_STATE_UNAWARE;
	
	ret = SCardGetStatusChange ((*ctx)->hContext, 0, (*ctx)->rgReaderStates, 1);
	
get_readers :
	
	if (NULL != readers)	{
		free (readers);
		readers = NULL;	
	}	
	

	if ((*ctx)->rgReaderStates_t != NULL)	{
		free ((*ctx)->rgReaderStates_t);
		(*ctx)->rgReaderStates_t = NULL;
	}
	
	
	ret = SCardListReaders ((*ctx)->hContext, NULL, NULL, &(*ctx)->dwReaders);

	return -1;
}


