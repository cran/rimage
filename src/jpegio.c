/***************************************************
 *
 *  Jpeg Read Write Functions
 *
 * 
 *  $Header: /home/repository/rimage/src/Attic/jpegio.c,v 1.1.2.3 2003/10/17 06:00:06 tomo Exp $
 *  Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 *  complete license terms see file LICENSE
 * 
 ***************************************************/


#include <stdio.h>
#include "jpeglib.h"
#include <setjmp.h>

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */
	jmp_buf setjmp_buffer;	    /* for return to caller */
};

typedef struct my_error_mgr * my_error_ptr;


METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
{
	my_error_ptr myerr = (my_error_ptr) cinfo->err;
	(*cinfo->err->output_message) (cinfo);
	longjmp(myerr->setjmp_buffer, 1);
}

void
get_imagesize_of_JPEG_file (char **filename, 
							int *width, int *height, int *depth, int *ret)
{
	char *fname = *filename;
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;
	FILE * infile;		
	
	if ((infile = fopen(fname, "rb")) == NULL) {
		*ret = -1;    /* couldn't open file */
		return;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit; /* override by my error exit */

	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		*ret = -2;   /* internal error */
		return;
	}
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);
	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);

	*width = cinfo.output_width;
	*height = cinfo.output_height;
	*depth = cinfo.output_components;

	jpeg_destroy_decompress(&cinfo);
	fclose(infile);
	*ret = 1;
}

void read_JPEG_file (char **filename, double *image, int *ret)
{
	char *fname = *filename;
	struct jpeg_decompress_struct cinfo;
	struct my_error_mgr jerr;
	FILE * infile;		/* source file */
	JSAMPARRAY buffer;	/* Output row buffer */
	int row_stride;		/* physical row width in output buffer */
	int plane_size;
	int i, j;
	int line;
	char *p;
	
	if ((infile = fopen(fname, "rb")) == NULL) {
		*ret = -1;   /* couldn't open file */
		return;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;  /* override by my error exit */
	if (setjmp(jerr.setjmp_buffer)) {
		jpeg_destroy_decompress(&cinfo);
		fclose(infile);
		*ret = -2;   /* internal error */
		return;
	}
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, infile);

	(void) jpeg_read_header(&cinfo, TRUE);
	(void) jpeg_start_decompress(&cinfo);
	row_stride = cinfo.output_width * cinfo.output_components;
	buffer = (*cinfo.mem->alloc_sarray)
		((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
	
	while (cinfo.output_scanline < cinfo.output_height) {
		line = cinfo.output_scanline;  /* preserve current scanline */
		(void) jpeg_read_scanlines(&cinfo, buffer, 1);
		p = buffer[0]; 
		plane_size = cinfo.output_width * cinfo.output_height;
		for (i = 0; i < cinfo.output_width; i++) {
			for (j = 0; j<cinfo.output_components; j++) {
				image[line + cinfo.output_height * i 
					 + j * plane_size] = (unsigned char) *p++;
			}
		}
	}

	(void) jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	fclose(infile);
	*ret = 1;
	return;
}


/* the end of file */
