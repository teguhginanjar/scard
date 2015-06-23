#ifndef __SCARD_INTERNAL_H__
#define __SCARD_INTERNAL_H__


#include <pcsclite.h>
#include <winscard.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>



#define CHECK(f, rv) \
	if (SCARD_S_SUCCESS != rv)\
	{\
		printf(f ": %s\n", pcsc_stringify_error(rv)); \
		return -1; \
	}





#endif 
