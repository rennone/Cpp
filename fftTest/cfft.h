#ifndef _CFFT_H
#define _CFFT_H

#include<complex.h>
typedef double complex Complex;

/*	fft.c	*/
void fft1(double ar[], double ai[], int n, int iter, int flag);
void fft1x(Complex a[], int n, int iter, int flag);
void fft2(double ar[], double ai[], int n, int nmax, int flag);
void fft2x(Complex a[], int n, int nmax, int flag);

#endif
