/*******************************************************
 * 
 * file fftw_access_func.c
 *
 *  Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 *  complete license terms see file LICENSE
 *
 *******************************************************/

#include <fftw.h>
#include <stdlib.h>
#include "R.h"

void fftw_access_func( Rcomplex *img, int *nx, int *ny, int *dir, int *debug,
					   Rcomplex *spectrum)
{

  int x,y;
  FILE *f;
  fftwnd_plan plan;
  fftw_complex *i, *s;
  int mem_size;
  double im,re;

  if (*debug) {
	  printf("\t*** entered module fftw_access_func...\n");
	  printf("\tgetting dimensions of nx=%d, ny=%d\n",*nx,*ny);
  }

  /***************** first do the neccessary memory allocation **************/
  mem_size = (*nx) * (*ny) * sizeof(fftw_complex);
  i = (fftw_complex*) malloc(mem_size); 
  s = (fftw_complex*) malloc(mem_size); 
  if (*debug) printf("\tmemory allocation successful\n");
  /**************************************************************************/

  for(y=0;y<(*ny);y++)
	  for(x=0;x<(*nx);x++) {
		  i[y*(*nx)+x].re = (fftw_real) img[y + x * (*ny)].r;
		  i[y*(*nx)+x].im = (fftw_real) img[y + x * (*ny)].i;
	  }  

  plan = fftw2d_create_plan(*ny, *nx, *dir, FFTW_ESTIMATE);
  if (*debug) printf("\tcreating a plan succeeded\n");
  fftwnd_one(plan, i, s);
  fftwnd_destroy_plan(plan);
  if (*debug) printf("\tfinished computing the fft\n");
  
  for(x=0;x<(*nx);x++)
	  for(y=0;y<(*ny);y++) {
		  spectrum[y + (*ny) * x].r = (double) s[y*(*nx)+x].re;
		  spectrum[y + (*ny) * x].i = (double) s[y*(*nx)+x].im;
	  }  

  if (*debug) printf("\tfreeing enslaved memory\n");
  free(i);
  free(s);
  if (*debug) printf("\t*** finished cleaning the dishes, now I am leaving...\n");
}

/** the end of file **/
