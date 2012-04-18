/******************************************************************************/
/*                                                                            */
/*    Copyright (c)Yudin Victor. Moscow 2012                                  */
/*                                                                            */
/******************************************************************************/

/******************************************************************************
 * = LIBRARY
 *     dtexconvert
 * = AUTHOR(S)
 *     Victor Yudin
 * = VERSION
 *     $Revision$
 * = DATE RELEASED
 *     $Date$
 * = RCSID
 *     $Id$
 ******************************************************************************/

#include "dsoInterface.h"

#include <stdlib.h>
#include <dlfcn.h>

void* LoadDSO(const char* i_path)
{
	if (!i_path)
	{
		return NULL;
	}
	
	return dlopen(i_path, RTLD_NOW | RTLD_GLOBAL);
}

void* GetDSOSymbol(void* i_dso, const char* i_name)
{
	return dlsym(i_dso, i_name);
}

void CloseDSO(void* i_dso)
{
#ifndef LINUX
	dlclose(i_dso);
#endif	
}
