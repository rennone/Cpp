#include<fstream>
#include <cstdio>
#include<iostream>
using namespace std;

void openTxt()
{
  ifstream fp("hoge.csv");
  
}
int main()
{
  FILE *fp;
  fp = fopen("hoge.csv","r");
  double a,b,c,d;
  int num;
  int res = fscanf(fp, "%d",&num);
  int count = 0;
  while(num != EOF && count < 10)
  {
    for(int i=0; i<num; i++)
    {
      if(fscanf(fp, "%lf",&a) == EOF)
        return 0;
      cout << a << " ";
    }
    cout << endl;
    res =  fscanf(fp,"%d",&num);
    count++;
  }
  
  /*
  while(fscanf(fp, "%lf,%lf,%lf,%lf",&a,&b,&c,&d) != EOF)
  {    
    cout << a << " " << b << " " << c << " " << d << endl;
    }*/
}
