/**
 ** Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 ** For complete license terms see file LICENSE
 **/

#include <fftw.h>
#include <stdlib.h>
#include "R.h" /********************************/

using namespace std;

extern "C" {

  void fftw_access_func( Rcomplex *img, int *nx, int *ny, // input data
			 int *dir, // determines the direction that fft is heading
			 // (-1: fft,  +1: inverse fft)
			 int *debug, // puts debugging messages on
			 Rcomplex *spectrum); // output data

}

/*******************************************************/
/*
  WARNING:

  change the include path to R's header files!

*/
