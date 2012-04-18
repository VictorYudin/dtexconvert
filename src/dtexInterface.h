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

#ifndef dtexconvert_pdtexInterface_h
#define dtexconvert_pdtexInterface_h

#include <dtex.h>

class DtexInterface
{
public:
	DtexInterface(const char *i_libpath);
	~DtexInterface();
	
	bool Valid( void ) const { return m_valid; }
	
	typedef DtexCache* (*DtexCreateCacheType) (
		int numTiles,
		DtexAccessor *accessor);
	typedef int (*DtexDestroyCacheType) (DtexCache *c);
	
	typedef int (*DtexOpenFileType) (
		const char *name,
		const char *mode,
		DtexCache *cache,
		DtexFile **result);
	typedef int (*DtexCreateFileType) (
		const char *name,
		DtexCache *cache,
		DtexFile **result);
	typedef int (*DtexAddImageType) (
		DtexFile *f,
		const char *name,
		int numChan,
		int w, int h,
		int tw, int th,
		float *NP,
		float *Nl,
		enum DtexCompression compression,
		enum DtexDataType datatype,
		DtexImage **result);
	typedef int (*DtexCountImagesType) (DtexFile *f);
	typedef int (*DtexGetImageByIndexType) (
		DtexFile *f,
		int index,
		DtexImage **result);
	typedef int (*DtexCloseType) (DtexFile *ds);
	
	typedef int (*DtexWidthType) (DtexImage *i_i);
	typedef int (*DtexHeightType) (DtexImage *i_i);
	typedef char* (*DtexImageNameType) (DtexImage *i);
	typedef int (*DtexNumChanType) (DtexImage *i_i);
	typedef int (*DtexTileWidthType) (DtexImage *i_i);
	typedef int (*DtexTileHeightType) (DtexImage *i_i);
	typedef int (*DtexNPType) (DtexImage *i_i, float *o_NP);
	typedef int (*DtexNlType) (DtexImage *i_i, float *o_Nl);
	typedef DtexCompression (*DtexGetCompressionType) (DtexImage *i);
	typedef DtexDataType (*DtexGetDataTypeType) (DtexImage *i);
	typedef int (*DtexSetPixelType) (
		DtexImage *io_img,
		int i_x, int i_y,
		DtexPixel *i_pix);
	typedef int (*DtexGetPixelType) (
		DtexImage *io_img,
		int i_x, int i_y,
		DtexPixel *o_pix);
	typedef int (*DtexEvalType) (
		DtexImage *i_img,
		int i_x, int i_y,
		float i_z,
		int i_n,
		float *o_data);
	typedef int (*DtexGetZRangeType) (
		DtexImage *i_img,
		int i_x, int i_y,
		float *o_min,
		float *o_max);
	typedef int (*DtexGetAttributeType) (
		DtexImage *i_img,
		const char *i_name,
		void *o_value);
	typedef int (*DtexSetAttributeType) (
		DtexImage *i_img,
		const char *i_name,
		void *i_value);
	
	typedef DtexPixel* (*DtexMakePixelType) (int i_numChan);
	typedef void (*DtexDestroyPixelType) (DtexPixel *io_pix);
	typedef int (*DtexClearPixelType) (DtexPixel *io_pix, int i_numChan);
	typedef int (*DtexPixelGetNumPointsType) (DtexPixel *i_pix);
	typedef int (*DtexPixelGetPointType) (DtexPixel *pix, int i, float *z, float *data);
	typedef int (*DtexFinishPixelType) (DtexPixel *dest);
	typedef int (*DtexAppendPixelType) (
		DtexPixel *io_pix,
		float i_z,
		int i_numChan,
		float *i_data,
		float i_error);
	typedef int (*DtexEvalPixelType) (
		DtexPixel *i_pix,
		float i_z,
		int i_n,
		float *o_data);
	typedef int (*DtexGetPixelZRangeType) (
		DtexPixel *i_pix,
		float *o_min,
		float *o_max);
	
	DtexCreateCacheType DtexCreateCache_;
	DtexDestroyCacheType DtexDestroyCache_;
	DtexOpenFileType DtexOpenFile_;
	DtexCreateFileType DtexCreateFile_;
	DtexAddImageType DtexAddImage_;
	DtexCountImagesType DtexCountImages_;
	DtexGetImageByIndexType DtexGetImageByIndex_;
	DtexCloseType DtexClose_;
	
	DtexWidthType DtexWidth_;
	DtexHeightType DtexHeight_;
	DtexImageNameType DtexImageName_;
	DtexNumChanType DtexNumChan_;
	DtexTileWidthType DtexTileWidth_;
	DtexTileHeightType DtexTileHeight_;
	DtexNPType DtexNP_;
	DtexNlType DtexNl_;
	DtexGetCompressionType DtexGetCompression_;
	DtexGetDataTypeType DtexGetDataType_;
	DtexSetPixelType DtexSetPixel_;
	DtexGetPixelType DtexGetPixel_;
	DtexEvalType DtexEval_;
	DtexGetZRangeType DtexGetZRange_;
	DtexGetAttributeType DtexGetAttribute_;
	DtexSetAttributeType DtexSetAttribute_;
	
	DtexMakePixelType DtexMakePixel_;
	DtexDestroyPixelType DtexDestroyPixel_;
	DtexClearPixelType DtexClearPixel_;
	DtexPixelGetNumPointsType DtexPixelGetNumPoints_;
	DtexPixelGetPointType DtexPixelGetPoint_;
	DtexFinishPixelType DtexFinishPixel_;
	DtexAppendPixelType DtexAppendPixel_;
	DtexEvalPixelType DtexEvalPixel_;
	DtexGetPixelZRangeType DtexGetPixelZRange_;

private:
	void* m_handle;
	
	/* = true if ctor loaded all symbols correctly */
	bool m_valid;
};

#endif
