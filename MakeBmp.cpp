#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string>
#include <string.h>
#define max(a,b) (a>b ? a : b)
#define min(a,b) (a<b ? a : b)
typedef struct {
 float r,g,b;
}colorf;
using namespace std;
static void colorTransform(double phi, colorf *col)
{
  double range = 1.0; //波の振幅  
  double ab_phi = phi < 0 ? -phi : phi;
  double a = ab_phi < range ? (ab_phi <  range/3.0 ? 3.0/range*ab_phi : (-3.0/4.0/range*ab_phi+1.25) ) : 0.5;
  
  col->r = phi > 0 ? a:0;
  col->b = phi < 0 ? a:0;
  col->g = min(1.0, max(0.0, -3*ab_phi+2));
}

static int putBmpHeader(FILE *s, int x, int y, int c);
static int fputc4LowHigh(unsigned long d, FILE *s);
static int fputc2LowHigh(unsigned short d, FILE *s);

static void drawer_outputImage(const char *fileName, double *model, int width, int height)
{
  const int bpp = 24; //1ピクセルセル24ビット
  const int datasize = height*((((width*bpp/8) + 3) >> 2) << 2);
  
  unsigned char *buf = (unsigned char*)malloc(sizeof(unsigned char)*datasize);
  memset(buf, 0, sizeof(unsigned char)*datasize);

  colorf c;
  int k=0;
  for(int j=0; j<height; j++)
    for(int i=0; i<width; i++)
    {
      colorTransform( 0 , &c);
//      double n = model[i*height+j];
      double n = 1;
      double c_n = n == 0 ? 0 : 1.0-1.0/n;
      buf[k]   = 255;//max(0, min(255, (c.b-c_n)*255));
      buf[k+1] = 0;//max(0, min(255, (c.g-c_n)*255));
      buf[k+2] = 0;//max(0, min(255, (c.r-c_n)*255));
      k+=(bpp>>3);
    }

  FILE *fp = fopen(fileName, "wb");
  if(fp==NULL)
  {
    printf("can not open file %s",fileName);
    free(buf);
    return;
  }

  if( !putBmpHeader(fp, width, height, bpp) ) {
    printf("can not write headers");
    fclose(fp);
    free(buf);
    return;
  }

  if( fwrite((unsigned char*)buf, sizeof(unsigned char), datasize, fp) != datasize)
  {
    printf("can not write data");
    fclose(fp);
    free(buf);
    return;
  }

  free(buf);
  fclose(fp);
  return;
}


/*
  putBmpHeader BMPヘッダ書出
	
  BMPファイルのヘッダを書き出す

  戻り値
  int:0…失敗, 1…成功
  
  引数
  FILE *s:[i] 出力ストリーム
  int x:[i] 画像Xサイズ(dot, 1〜)
  int y:[i] 画像Yサイズ(dot, 1〜)
  intc:[i] 色ビット数(bit/dot, 1 or 4 or 8 or 24)
*/
static int putBmpHeader(FILE *s, int x, int y, int c)
{
  int i;
  int color; /* 色数 */
  unsigned long int bfOffBits; /* ヘッダサイズ(byte) */

  /* 画像サイズが異常の場合,エラーでリターン */
  if (x <= 0 || y <= 0) {
    return 0;
  }

  /* 出力ストリーム異常の場合,エラーでリターン */
  if (s == NULL || ferror(s)) {
    return 0;
  }

  /* 色数を計算 */
  if (c == 24) {
    color = 0;
  } else {
    color = 1;
    for (i=1;i<=c;i++) {
      color *= 2;
    }
  }

  /* ヘッダサイズ(byte)を計算 */
  /* ヘッダサイズはビットマップファイルヘッダ(14) + ビットマップ情報ヘッダ(40) + 色数 */
  bfOffBits = 14 + 40 + 4 * color;

  /* ビットマップファイルヘッダ(計14byte)を書出 */
  /* 識別文字列 */
  fputs("BM", s);

  /* bfSize ファイルサイズ(byte) */
  fputc4LowHigh(bfOffBits + (unsigned long)x * y, s);

  /* bfReserved1 予約領域1(byte) */
  fputc2LowHigh(0, s);

  /* bfReserved2 予約領域2(byte) */
  fputc2LowHigh(0, s);

  /* bfOffBits ヘッダサイズ(byte) */
  fputc4LowHigh(bfOffBits, s);

  /* ビットマップ情報ヘッダ(計40byte) */
  /* biSize 情報サイズ(byte) */
  fputc4LowHigh(40, s);

  /* biWidth 画像Xサイズ(dot) */
  fputc4LowHigh(x, s);

  /* biHeight 画像Yサイズ(dot) */
  fputc4LowHigh(y, s);

  /* biPlanes 面数 */
  fputc2LowHigh(1, s);

  /* biBitCount 色ビット数(bit/dot) */
  fputc2LowHigh(c, s);

  /* biCompression 圧縮方式 */
  fputc4LowHigh(0, s);

  /* biSizeImage 圧縮サイズ(byte) */
  fputc4LowHigh(0, s);

  /* biXPelsPerMeter 水平解像度(dot/m) */
  fputc4LowHigh(0, s);

  /* biYPelsPerMeter 垂直解像度(dot/m) */
  fputc4LowHigh(0, s);

  /* biClrUsed 色数 */
  fputc4LowHigh(0, s);

  /* biClrImportant 重要色数 */
  fputc4LowHigh(0, s);

  /* 書出失敗ならエラーでリターン */
  if (ferror(s)) {
    return 0;
  }

  /* 成功でリターン */
  return 1;
}

/*
  fputc2LowHigh 2バイトデータ書出(下位〜上位)
	
  2バイトのデータを下位〜上位の順で書き出す

  戻り値
  int:EOF…失敗, EOF以外…成功
  引数
  unsigned short d:[i] データ
  FILE *s:[i] 出力ストリーム
*/
static int fputc2LowHigh(unsigned short d, FILE *s)
{
  putc(d & 0xFF, s);
  return putc(d >> CHAR_BIT, s);
}

/*
  fputc4LowHigh 4バイトデータ書出(下位〜上位)
	
  4バイトのデータを下位〜上位の順で書き出す

  ●戻り値
  int:EOF…失敗, EOF以外…成功
  ●引数
  unsigned long d:[i] データ
  FILE *s:[i] 出力ストリーム
*/
static int fputc4LowHigh(unsigned long d, FILE *s)
{
  putc(d & 0xFF, s);
  putc((d >> CHAR_BIT) & 0xFF, s);
  putc((d >> CHAR_BIT * 2) & 0xFF, s);
  return putc((d >> CHAR_BIT * 3) & 0xFF, s);
}

int main()
{
  int width  = 155;
  int height = 155;
  double *data = (double*)malloc(sizeof(double)*width*height);
  memset(data, 0, sizeof(double)*width*height);
  string name = "image.bmp";
  drawer_outputImage(name.c_str(), data, width, height);
}
