/*		fft.c		*/
#include <stdio.h>
#include <stdlib.h>
#include "fft.h"
#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

static void make_sintbl(int n, float sintbl[])
{
  int i, n2, n4, n8;
  double c, s, dc, ds, t;
  n2 = n / 2;  n4 = n / 4;  n8 = n / 8;
  t = sin(PI / n);
  dc = 2 * t * t;  ds = sqrt(dc * (2 - dc));
  t = 2 * dc;  c = sintbl[n4] = 1;  s = sintbl[0] = 0;
  for (i = 1; i < n8; i++) {
    c -= dc;  dc += t * c;
    s += ds;  ds -= t * s;
    sintbl[i] = (float)s;
    sintbl[n4 - i] = (float)c;
  }
  if (n8 != 0) sintbl[n8] = (float)sqrt(0.5);
  for (i = 0; i < n4; i++)
    sintbl[n2 - i] = sintbl[i];
  for (i = 0; i < n2 + n4; i++)
    sintbl[i + n2] = - sintbl[i];
}

/*
  関数{\tt fft()}の下請けとしてビット反転表を作る.
*/
static void make_bitrev(int n, int bitrev[])
{
  int i, j, k, n2;
  n2 = n / 2;  i = j = 0;
  for ( ; ; ) {
    bitrev[i] = j;
    if (++i >= n) break;
    k = n2;
    while (k <= j) {  j -= k;  k /= 2;  }
    j += k;
  }
}
/*
  高速Fourier変換 (Cooley--Tukeyのアルゴリズム).
  標本点の数 n は2の整数乗に限る.
  x[] が実部, y[] が虚部 ($k = 0$, $1$, $2$,
  \ldots, $|{\tt n}| - 1$).
  結果は {\tt x[]}, {\tt y[]} に上書きされる.
  ${\tt n} = 0$ なら表のメモリを解放する.
  ${\tt n} < 0$ なら逆変換を行う.
  前回と異なる $|n|$ の値で呼び出すと,
  三角関数とビット反転の表を作るために多少余分に時間がかかる.
  この表のための記憶領域獲得に失敗すると1を返す (正常終了時
  の戻り値は0).
  これらの表の記憶領域を解放するには ${\tt n} = 0$ として
  呼び出す (このときは {\tt x[]}, {\tt y[]} の値は変わらない).
*/

int fft(int n, Complex x[])
{
  static int    last_n = 0;    /* 前回呼出し時の {\tt n} */
  static int   *bitrev  = NULL; /* ビット反転表 */
  static double *sintbl = NULL; /* 三角関数表 */
  
  int i, j, k, ik, h, d, k2, n4, inverse;
  float t, s, c, dx, dy;
  
  /* 準備 */
  if (n < 0){
    n = -n;
    inverse = 1;  /* 逆変換 */
  }
  else{
    inverse = 0;
  }
  
  n4 = n>>2;  // n/4

  //前回実行したときとサンプリング数が異なる場合表を作り直す
  if (n != last_n || n == 0){
    last_n = n;
    if (sintbl != NULL) free(sintbl);
    if (bitrev != NULL) free(bitrev);
    
    if (n == 0)
      return 0;  /* 記憶領域を解放した */
    
    sintbl = (float*)malloc((n + n4) * sizeof(float));
    bitrev = (int*)malloc(n * sizeof(int));
    
    if (sintbl == NULL || bitrev == NULL) {
      fprintf(stderr, "記憶領域不足\n");  return 1;
    }
    
    make_sintbl(n, sintbl);
    make_bitrev(n, bitrev);
  }
  
  for (i = 0; i < n; i++) {    /* ビット反転 */
    j = bitrev[i];
    if (i < j) {
      t = x[i];  x[i] = x[j];  x[j] = t;
      t = y[i];  y[i] = y[j];  y[j] = t;
    }
  }
  
  for (k = 1; k < n; k = k2) {    /* 変換 */
    h = 0;  k2 = k + k;  d = n / k2;
    for (j = 0; j < k; j++) {
      c = sintbl[h + n4];
      if (inverse) s = - sintbl[h];
      else         s =   sintbl[h];
      for (i = j; i < n; i += k2) {
        ik = i + k;
        dx = s * y[ik] + c * x[ik];
        dy = c * y[ik] - s * x[ik];
        x[ik] = x[i] - dx;  x[i] += dx;
        y[ik] = y[i] - dy;  y[i] += dy;
      }
      h += d;
    }
  }
  if (! inverse)    /* 逆変換でないならnで割る */
    for (i = 0; i < n; i++) {  x[i] /= n;  y[i] /= n;  }
  return 0;  /* 正常終了 */
}
