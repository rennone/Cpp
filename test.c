/*		test16.c			*/
#include <stdio.h>
#include "cfft.h"
typedef double complex Complex;
#define		CPX		/* Complex mode */

#ifndef CPX
void print(double *ar, double *ai, int n);
void print2(double *ar, double *ai, int n, int nmax);
#else
void printx(Complex *a, int n);
void print2x(Complex *a, int n, int nmax);
#endif

#ifndef CPX
void print(double *ar, double *ai, int n)
{
	int i;
	double *p, *q;

	printf("    ar              ai\n");
	for(i = 0, p = ar, q = ai; i < n; i++)	printf("%14.7e %14.7e\n", *p++, *q++);
}
#else
void printx(Complex *a, int n)
{
	int i;
	Complex *p;

	printf("    ar              ai\n");
	for(i = 0, p = a; i < n; i++, p++)	printf("%14.7e %14.7e\n", p->r, p->i);
}
#endif

#ifndef CPX
void print2(double *ar, double *ai, int n, int nmax)
{
	int i, j, k, l;
	double *p;

	printf("< ar >\n");
	for(i = k = 0, p = ar; i < n; i++)
	{
		for(j = 0; j < nmax; j++, k++)	printf("%14.7e ", *p++);
		putchar('\n');
	}
	printf("< ai >\n");
	for(i = k = 0, p = ai; i < n; i++)
	{
		for(j = 0; j < nmax; j++, k++)	printf("%14.7e ", *p++);
		putchar('\n');
	}
}
#else
void print2x(Complex *a, int n, int nmax)
{
	int i, j, k, l;
	Complex *p;

	printf("< Real part >\n");
	for i = k = 0, p = a; i < n; i++)
	{
		for(j = 0; j < nmax; j++, k++, p++)	printf("%14.7e ", p->r);
		putchar('\n');
	}
	printf("< Imaginary part >\n");
	for(i = k = 0, p = a; i < n; i++)
	{
		for(j = 0; j < nmax; j++, k++, p++)	printf("%14.7e ", p->i);
		putchar('\n');
	}
}
#endif

int main(void)
{
	static double ar[8] = { 0., 0., 0., 1., 1., 0., 0., 0.};
	static double ai[8] = { 0., 0., 0., 0., 0., 0., 0., 0.};
	static double ar2[16] = { 0., 0., 0., 0., 0., 1., 1., 0.,
							  0., 1., 1., 0., 0., 0., 0., 0.};
	static double ai2[16] = { 0., 0., 0., 0., 0., 0., 0., 0.,
							  0., 0., 0., 0., 0., 0., 0., 0.};
	Complex a[8], a2[16];
	int flag, i, iter, j, k, n, nmax;

	iter = 0;
	n = 8;
#ifndef CPX
	for(i = 0; i < n; i++)
          a[i] = tocomplex(ar[i], ai[i]);
	print(ar, ai, n);
#else
	printx(a, n);
#endif

/* forward FFT */
	flag = 0;
#ifndef CPX
	fft1(ar, ai, n, iter, flag);
	print(ar, ai, n);
#else
	fft1x(a, n, iter, flag);
	printx(a, n);
#endif

/* reverse FFT */
	flag = 1;
#ifndef CPX
	fft1(ar, ai, n, iter, flag);
	print(ar, ai, n);
#else
	fft1x(a, n, iter, flag);
	printx(a, n);
#endif
	n = nmax = 4;
	for(i = k = 0; i < n; i++)
          for(j = 0; j < n; j++, k++)
            a2[k] = tocomplex(ar2[k], ai2[k]);
#ifndef CPX
	print2(ar2, ai2, n, nmax);
#else
	print2x(a2, n, nmax);
#endif
	flag = 0;
#ifndef CPX
	fft2(ar2, ai2, n, nmax, flag);
	print2(ar2, ai2, n, nmax);
#else
	fft2x(a2, n, nmax, flag);
	print2x(a2, n, nmax);
#endif
	flag = 1;
#ifndef CPX
	fft2(ar2, ai2, n, nmax, flag);
	print2(ar2, ai2, n, nmax);
#else
	fft2x(a2, n, nmax, flag);
	print2x(a2, n, nmax);
#endif
	return 1;
}
