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

#ifndef dtexconvert_dsoInterface_h
#define dtexconvert_dsoInterface_h

/* A useful macro to load a symbol from the library */
#define LOAD_SYMBOL(error, handle, symbol) \
	if( !error ) \
	{ \
		symbol##_ = (symbol##Type)GetDSOSymbol( handle, #symbol ); \
		if( !symbol##_ ) \
		{ \
			error = true; \
		} \
	}

void* LoadDSO(const char* i_path);
void* GetDSOSymbol(void* i_dso, const char* i_name);
void CloseDSO(void* i_dso);

#endif
