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

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "dtexInterface.h"

void PrintAbout()
{
	printf( PACKAGE " is utility to covert dtex of 3delight format to dtex "
			"of prman format\n"
			"Version " VERSION "\n"
			"Copyright (c) Victor Yudin, Moscow, 2012\n"
			"Usage: dtexconvet inputtexture outputtexture\n\n" );
}

int main(int argc, char** argv)
{
	/* Check arguments */
	if(argc == 2)
	{
		if( strcmp(argv[1], "--help") == 0 ||
			strcmp(argv[1], "--version") == 0 ||
			strcmp(argv[1], "-h") == 0 ||
			strcmp(argv[1], "-v") == 0 ||
			strcmp(argv[1], "/?") == 0 )
		{
			PrintAbout();
			return 0;
		}
	}
	
	if(argc != 3)
	{
		printf("Wrong arguments.\n");
		PrintAbout();
		return 1;
	}
	
	/* Get full path of libprman.dylib */
	const char* libprman = "libprman.dylib";
	char* libprmandir = getenv("RMANTREE");
	
	char libprmanpath[strlen(libprman) + strlen(libprmandir) + 6];
	strcpy (libprmanpath,libprmandir);
	strcat (libprmanpath,"/lib/");
	strcat (libprmanpath,libprman);
	
	/* Get full path of lib3delight.dylib */
	const char* lib3delight = "lib3delight.dylib";
	char* lib3delightdir = getenv("DELIGHT");
	
	char lib3delightpath[strlen(lib3delight) + strlen(lib3delightdir) + 6];
	strcpy (lib3delightpath,lib3delightdir);
	strcat (lib3delightpath,"/lib/");
	strcat (lib3delightpath,lib3delight);

	/* Get prman Dtex interface */
	DtexInterface prmandtex(libprmanpath);
	
	if(!prmandtex.Valid())
	{
		printf("Error: libprman error\n");
		return 1;
	}

	/* Get 3delight Dtex interface */
	DtexInterface dldtex(lib3delightpath);
	
	if(!dldtex.Valid())
	{
		printf("Error: lib3delight error\n");
		return 1;
	}
	
	/* Open input file */
	DtexFile *inFile = 0;
	DtexImage *inImage = 0;
	
	char *inname = argv[1];
	
	if(dldtex.DtexOpenFile_(inname, "rb", NULL, &inFile) != DTEX_NOERR)
	{
		printf("Error: Unable to open input file %s.\n", inname);
		return 1;
	}
	
	if(dldtex.DtexGetImageByIndex_(inFile, 0, &inImage) != DTEX_NOERR)
	{
		printf("Error: DtexGetImageByIndex error\n");
		return 1;
	}
	
	/* Create output file */
	char* imageName = dldtex.DtexImageName_( inImage );
	int numchan = dldtex.DtexNumChan_( inImage );
	int width = dldtex.DtexWidth_( inImage );
	int height = dldtex.DtexHeight_( inImage );
	int tileWidth = dldtex.DtexTileWidth_( inImage );
	int tileHeight = dldtex.DtexTileHeight_( inImage );
	
	DtexFile *outFile;
	DtexCache *outCache;
	DtexImage *outImage;
	DtexPixel *mergedPixel;
	
	char *outname = argv[2];
	float oneMatrix[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	
	outCache = prmandtex.DtexCreateCache_(128, NULL);
	
	if (prmandtex.DtexCreateFile_(outname, outCache, &outFile) != DTEX_NOERR)
	{
		fprintf(stderr, "Error: Unable to create output file %s.\n", outname);
		return 1;
	}
	
	if (prmandtex.DtexAddImage_(
		outFile,
		imageName?imageName:"imageName",
		numchan,
		width,
		height,
		tileWidth,
		tileHeight,
		oneMatrix,
		oneMatrix,
		DTEX_COMPRESSION_ZIP,
		DTEX_TYPE_FLOAT,
		&outImage) != DTEX_NOERR)
	{
		fprintf(stderr, "Unable to create output image\n");
		return 1;
	}
	
	DtexPixel *inPixel;
	inPixel = dldtex.DtexMakePixel_(0);
	
	printf("Start converting.\n");
	
	for (int x=0; x<width; ++x)
	{
		for(int y=0; y<height; ++y)
		{
			mergedPixel = prmandtex.DtexMakePixel_(numchan);
			prmandtex.DtexClearPixel_(mergedPixel, numchan);
			
			int error = dldtex.DtexGetPixel_(inImage, x, y, inPixel);
			assert( error == DTEX_NOERR );
			int pointswrote = 0;
			int np = dldtex.DtexPixelGetNumPoints_(inPixel);
			for (unsigned int n=0; n<np; ++n)
			{
				float z;
				float d[3];
				error = dldtex.DtexPixelGetPoint_(inPixel, n, &z, d);
				assert( error == DTEX_NOERR );
				
//				if( d[0] < 0.9 &&
//					d[1] < 0.9 &&
//					d[2] < 0.9 )
//				{
//					continue;
//				}
//				float c = 0.95f;
//				
//				if( d[0] > c &&
//					d[1] > c &&
//					d[2] > c &&
//					pointswrote == 0)
//				{
//					continue;
//				}
				
				pointswrote++;
				
				if (prmandtex.DtexAppendPixel_(mergedPixel, z, numchan, d, 0) != DTEX_NOERR)
				{
					fprintf(stderr, "Unable to append to merged pixel at %d %d\n", x, y);
					return 1;
				}
			}
			
			if( pointswrote > 0)
			{
			
				if (prmandtex.DtexFinishPixel_(mergedPixel) != DTEX_NOERR)
				{
					fprintf(stderr, "Unable to finish output pixel at %d %d\n", x, y);
					return 1;
				}
				
				if (prmandtex.DtexSetPixel_(outImage, x, y, mergedPixel) != DTEX_NOERR)
				{
					fprintf(stderr, "Unable to set output pixel at %d %d\n", x, y);
					return 1;			
				}
			
			}
			
			prmandtex.DtexDestroyPixel_(mergedPixel);
		}
	}
	
	if (dldtex.DtexClose_(inFile) != DTEX_NOERR)
	{
		fprintf(stderr, "Unable to close input file\n");
	}
	
	if (prmandtex.DtexClose_(outFile) != DTEX_NOERR)
	{
		fprintf(stderr, "Unable to close output file %s\n", outname);
	}
	
	prmandtex.DtexDestroyCache_(outCache);
	
	printf("Done\n");
	return 0;
}
