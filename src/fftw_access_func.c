/*******************************************************/
/* 
 * file fftw_access_func.c
 *
 *  Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 *  complete license terms see file LICENSE
 *
/*******************************************************/
/*
  WARNING:

  change the include path to R's header files!

*/


#include <fftw.h>
#include <stdlib.h>

#include "R.h" /********************************/


/**
   debugging issues...
**/
//double tmp[300][200];
//void savepgm(char *name, double u[300][200]);
//void normalize(double u[300][200]);


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
    for(x=0;x<(*nx);x++)
      {
	//i[x][y].re = (fftw_real) img[y + x * (*ny)].r;
	//i[x][y].im = (fftw_real) img[y + x * (*ny)].i;
	i[y*(*nx)+x].re = (fftw_real) img[y + x * (*ny)].r;
	i[y*(*nx)+x].im = (fftw_real) img[y + x * (*ny)].i;
      }  

  /*
  for(x=0;x<(*nx);x++)
    for(y=0;y<(*ny);y++)
      tmp[x][y]=255*255*sqrt( (i[x*(*nx)+y].re)*(i[x*(*nx)+y].re) + (i[x*(*nx)+y].im)*(i[x*(*nx)+y].im));
  normalize(tmp);
  savepgm("received.pgm",tmp);
  */

  plan = fftw2d_create_plan(*ny, *nx, *dir, FFTW_ESTIMATE);
  if (*debug) printf("\tcreating a plan succeeded\n");
  fftwnd_one(plan, i, s);
  fftwnd_destroy_plan(plan);
  if (*debug) printf("\tfinished computing the fft\n");

  
  for(x=0;x<(*nx);x++)
    for(y=0;y<(*ny);y++)
      {
	spectrum[y + (*ny) * x].r = (double) s[y*(*nx)+x].re;
	spectrum[y + (*ny) * x].i = (double) s[y*(*nx)+x].im;
      }  
  /*
    tmp[x*(nx)+y]=log(1+255*sqrt( (s[x*(*nx)+y].re)*(s[x*(*nx)+y].re) + (s[x*(*nx)+y].im)*(s[x*(*nx)+y].im)));
  normalize(tmp);
  savepgm("ffted.pgm",tmp);
  */
  if (*debug) printf("\tfreeing enslaved memory\n");
  free(i);
  free(s);
  if (*debug) printf("\t*** finished cleaning the dishes, now I am leaving...\n");
}
 

void normalize(double u[300][200])
{

  int i,j;

  double highest = 0.0;
  double lowest = u[0][0];
  double quot;

  for(i=0;i<300;i++)
    for(j=0;j<200;j++)
      {
	if(u[i][j] > highest) highest = u[i][j];
	if(u[i][j] < lowest) lowest = u[i][j];
      }
  quot = 1 / (highest - lowest);
  for(i=0;i<300;i++)
    for(j=0;j<200;j++)
	u[i][j] = (u[i][j]-lowest) * 255.0 * quot;


}

void savepgm(char *name,double u[300][200]) {

  FILE *imagefile;
  long i,j;
  unsigned char byte;

  imagefile = fopen (name, "w");
  
/*  printf("P5 \n");*/
/*  printf("# Komentar\n");*/
/*  printf("%ld %ld \n255\n", x, y);*/
  
  fprintf (imagefile, "P5 \n");
  fprintf (imagefile, "%ld %ld \n255\n", 300, 200);

  /* write image data and close file */
  for (j=0; j<200; j++) {
    for (i=0; i<300; i++) {
      if (u[i][j] < 0.0)
        byte = (unsigned char)(0.0);
      else if (u[i][j] > 255.0)
        byte = (unsigned char)(255.0);
      else
        byte = (unsigned char)(u[i][j]);
      fwrite (&byte, sizeof(unsigned char), 1, imagefile);
    }
  }

  fclose(imagefile);
/*  printf("output image %s successfully written\n\n", name);*/
  
}
