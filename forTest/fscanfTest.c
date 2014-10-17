#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double *grayImage;
int width, height;
double nmPerPixel;

int ind(int x, int y)
{
  return x*height + y;
}

void readImage()
{
  FILE *fp = NULL;
  if( !(fp = fopen("image.txt", "r")))
  {
    printf("cannot find image.txt of morphoScaleModel\n");
    exit(2);
  }
  
  //横幅と縦幅, 1ピクセルの大きさを取得
  fscanf(fp,"%d %d %lf",&width, &height, &nmPerPixel);
  grayImage = (double*)malloc(sizeof(double)*width*height);
  memset(grayImage,0, sizeof(double)*width*height);
  for(int y=0; y<height; y++){
    for(int x=0; x<width; x++){
      fscanf(fp, "%lf ", &grayImage[ind(x,y)]);
    }
  }

  for(int y=0; y<height; y++){
    for(int x=0; x<width; x++){
      printf("%.2lf ", grayImage[ind(x,y)] );
    }
    printf("\n");
  }

  printf("%d %d %lf",width, height, nmPerPixel);
  fclose(fp);
}

void makeImage()
{
  FILE *fp = NULL;
  if( !(fp = fopen("image.txt", "w")))
  {
    printf("cannot find image.txt of morphoScaleModel\n");
    exit(2);
  }

  int wid = 30, hei = 100;
  double npp = 10.8;
  fprintf(fp, "%d %d %lf\n", wid, hei, npp);
  for(int j=0; j<hei; j++)
  {
    for(int i=0; i<wid; i++)
    {
      if( fabs(i-wid/2.0)/wid*hei <= j/2.0 )
        fprintf(fp, "%.2lf ", 1.56);
      else
        fprintf(fp, "%.2lf ", 1.00);
    }
    fprintf(fp,"\n");
  }
  fclose(fp);
}

int main()
{
  makeImage();
  readImage();
  return 0;
}
