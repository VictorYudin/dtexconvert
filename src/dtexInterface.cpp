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

#include "dtexInterface.h"

#include <stdio.h>

#include "dsoInterface.h"

DtexInterface::DtexInterface(const char *i_libpath) : m_valid(0)
{
	m_handle = LoadDSO(i_libpath);
	
	if (!m_handle)
	{
		fprintf( stderr, "Unable to load %s library\n", i_libpath );
		return;
	}
	
	bool error = false;
	LOAD_SYMBOL( error, m_handle, DtexCreateCache );
	LOAD_SYMBOL( error, m_handle, DtexDestroyCache );
	LOAD_SYMBOL( error, m_handle, DtexOpenFile );
	LOAD_SYMBOL( error, m_handle, DtexCreateFile );
	LOAD_SYMBOL( error, m_handle, DtexAddImage );
	LOAD_SYMBOL( error, m_handle, DtexCountImages );
	LOAD_SYMBOL( error, m_handle, DtexGetImageByIndex );
	LOAD_SYMBOL( error, m_handle, DtexClose );
	
	LOAD_SYMBOL( error, m_handle, DtexWidth );
	LOAD_SYMBOL( error, m_handle, DtexHeight );
	LOAD_SYMBOL( error, m_handle, DtexImageName );
	LOAD_SYMBOL( error, m_handle, DtexNumChan );
	LOAD_SYMBOL( error, m_handle, DtexTileWidth );
	LOAD_SYMBOL( error, m_handle, DtexTileHeight );
	LOAD_SYMBOL( error, m_handle, DtexNP );
	LOAD_SYMBOL( error, m_handle, DtexNl );
	LOAD_SYMBOL( error, m_handle, DtexGetCompression );
	LOAD_SYMBOL( error, m_handle, DtexGetDataType );
	LOAD_SYMBOL( error, m_handle, DtexSetPixel );
	LOAD_SYMBOL( error, m_handle, DtexGetPixel );
	LOAD_SYMBOL( error, m_handle, DtexEval );
	LOAD_SYMBOL( error, m_handle, DtexGetZRange );
	//LOAD_SYMBOL( error, m_handle, DtexGetAttribute );
	//LOAD_SYMBOL( error, m_handle, DtexSetAttribute );
	
	LOAD_SYMBOL( error, m_handle, DtexMakePixel );
	LOAD_SYMBOL( error, m_handle, DtexDestroyPixel );
	LOAD_SYMBOL( error, m_handle, DtexClearPixel );
	LOAD_SYMBOL( error, m_handle, DtexPixelGetNumPoints );
	LOAD_SYMBOL( error, m_handle, DtexPixelGetPoint );
	LOAD_SYMBOL( error, m_handle, DtexFinishPixel );
	LOAD_SYMBOL( error, m_handle, DtexAppendPixel );
	LOAD_SYMBOL( error, m_handle, DtexEvalPixel );
	LOAD_SYMBOL( error, m_handle, DtexGetPixelZRange );
	
	if( error )
	{
		fprintf( stderr, "Unable to load symbols in %s library\n", i_libpath );
	}
	else
	{
		m_valid = true;
	}
}

DtexInterface::~DtexInterface()
{
	if( m_valid )
	{
		CloseDSO(m_handle);
	}
}
