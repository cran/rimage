/***************************************************
 *
 *  Laplacian Filter Functions for rimage (R package)
 *
 *  $Header: /home/repository/rimage/src/laplacian.c,v 1.3 2003/03/15 06:48:33 tomo Exp $
 *
 *  Copyright (c) 2003 Nikon Digital Technologies Co., Ltd.
 *  complete license terms see file LICENSE
 ***************************************************/

void laplacian(double *img, long *w, long *h, double *eimg) {
	int i, j;
	double val[8];
	clearFrame(eimg, *w, *h);
	for (i = 1; i<*w-1; i++) {
		for (j = 1; j<*h-1; j++) {
			eimg[*h * i + j] = img[*h * i + (j-1)] + 
				img[*h * (i-1) + j] + 
				img[*h * (i+1) + j] + 
				img[*h * i + (j+1)] - 4.0 * img[*h * i + j];
		}
	}
}

/* the end of this file */

