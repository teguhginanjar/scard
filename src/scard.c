#include "scard.h"


int _scard_init_2 (SCARD_CTX ** ctx)
{

	(*ctx) = (SCARD_CTX *) malloc (sizeof (SCARD_CTX));
	if ((*ctx) == NULL)	{

		return -1;
	}	 
	
	return 0;
} 


// for omnikey cardman 5321 nfc , or multi card reader in one PC 
int _scard_init (SCARD_CTX ** ctx)
{
	
	(*ctx) = (SCARD_CTX *) malloc (sizeof (SCARD_CTX));
	if ((*ctx) == NULL) {

		return -1;
	} 	
	
	int i , iReaders;
	char * ptr, ** readers = NULL;
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
	(*ctx)->mszReaders = calloc((*ctx)->dwReaders, sizeof (char));
	printf ("scanning present readers .. \n");
	ret = SCardListReaders ((*ctx)->hContext, NULL, (*ctx)->mszReaders, &(*ctx)->dwReaders);

	CHECK ("Reader ", ret);

	if (ret != SCARD_E_NO_READERS_AVAILABLE)	{
		printf ("ScardListReaders %lu %ld \n", ret,  (*ctx)->hContext);
		//return -1;
	}
	
	dwReadersOld = (*ctx)->dwReaders;

	if ((*ctx)->mszReaders)	{
		free ((*ctx)->mszReaders);
		(*ctx)->mszReaders = NULL;		
	}

	(*ctx)->mszReaders = malloc (sizeof (char) * (*ctx)->dwReaders);
	if ((*ctx)->mszReaders == NULL)	{
		printf ("malloc : not enought memory \n");
		return -1;
	}

	*(*ctx)->mszReaders = '\0';
	ret = SCardListReaders ((*ctx)->hContext,NULL, (*ctx)->mszReaders, &(*ctx)->dwReaders);

	iReaders = 0;
	ptr = (*ctx)->mszReaders;
	while (*ptr != '\0')	{
		ptr += strlen (ptr) + 1;
		iReaders ++;
	}

	// allocate readers the table 
	readers = calloc (iReaders + 1, sizeof (char));
	if (NULL == readers)	{
		printf ("calloc : not enought memory for readers table \n");	
		return -1;
	}
	
	iReaders = 0;
	ptr  = (*ctx)->mszReaders;

	while (*ptr != '\0')	{
		printf ("[%d : %s]\n", iReaders, ptr);
		readers[iReaders] = ptr;
		ptr += strlen(ptr) + 1;
		iReaders ++;
	}

	// set initial states something we dont know 
	// the loop below will include this state to the dwCurrentState

	(*ctx)->rgReaderStates_t = calloc (iReaders+1, sizeof (*(*ctx)->rgReaderStates_t));
	if (NULL == (*ctx)->rgReaderStates_t)	{
		printf ("calloc : not enought memory for readers table \n");	
		return -1;
	}
	
 	for (i=0; i<iReaders; i++) {
		(*ctx)->rgReaderStates_t[i].szReader = readers[i];
		(*ctx)->rgReaderStates_t[i].dwCurrentState = SCARD_STATE_UNAWARE;
		printf ("found : %s:: %s\n", readers[i],(*ctx)->rgReaderStates_t[i].szReader = readers[i]);
	}


	//(*ctx)->rgReaderStates_t[iReaders].szReader = "\\\\?PnP\\Notification";
	//(*ctx)->rgReaderStates_t[iReaders].dwCurrentState = SCARD_STATE_UNAWARE;
	
	return 0;
}

int scard_init (SCARD_CTX ** ctx, READER_TYPE RD)
{
	int ret = 0;
	if (RD == RT_DEFAULT)	{
		ret = _scard_init_2 (ctx);
	}
	if (RD == RT_OMNNIKEY_5321)	{
		ret = _scard_init (ctx);
	}
	
}


int scard_connect_picc (SCARD_CTX ** ctx)	
{

	
	fprintf (stderr, "<%s>\n", (*ctx)->rgReaderStates_t[0].szReader);
	
	DWORD dwRet = 
			SCardConnect ((*ctx)->hContext, (*ctx)->rgReaderStates_t[1].szReader,
							SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0| SCARD_PROTOCOL_T1, 
							&(*ctx)->hCard, &(*ctx)->dwActiveProtocol);
	CHECK ("CANT CONNECT ICC/PICC", dwRet);
	if (dwRet == -1) {
		
		return 1;
	} 
	switch ((*ctx)->dwActiveProtocol){
	case SCARD_PROTOCOL_T0:	(*ctx)->pioSendPci = *SCARD_PCI_T0; break;
	case SCARD_PROTOCOL_T1: (*ctx)->pioSendPci = *SCARD_PCI_T1; break;
	};
	return 0;
}


