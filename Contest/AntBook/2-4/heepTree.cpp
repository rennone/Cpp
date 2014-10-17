//ヒープ木の実装
#define MAXSIZE 1000
int heep[MAXSIZE], sz = 0;

void push(int x)
{
  heep[sz] = x;
  int i = sz++;
  while( i>0 )
  {
    int p = (i-1)/2;
    if( heep[p] <= x)
      break;
    heep[i] = heep[p];
    i = p;
  }
  heep[i] = x;
}

int pop()
{
  int top = heep[0];
  int i=0;
  int x = heep[--sz];  
  while( 2*i+1 < sz)
  {
    int c1 = 2*i+1;
    int c2 = 2*i+2;
    int c = c2 >= sz || heep[c1]<heep[c2] ? c1 : c2;
    if( x <= heep[c] )
      break;

    heep[i] = heep[c];
    i = c;
  }  
  heep[i] = x;

  return top;
}

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

bool test1()
{
  srand(0);
  for(int i=0; i<MAXSIZE;i++)
    push(rand());

  int min = pop();
  for(int i=0; i<MAXSIZE-1;i++)
  {
    int top = pop();
    if(min > top)
    {
      cout << min << "," << top << "," << i << endl;
      return false;
    }
    min = top;
  }
  return true;
}

bool test2()
{
  int size = 0;
  for(int i=0; i<MAXSIZE; i++)
  {
    if(rand()%2 == 0 || size==0)
    {
      push(rand());
      size++;
    }
    else
    {
      pop();
      size--;
    }
  }
  
  int min = pop();
  for(int i=0; i<size-1;i++)
  {
    int top = pop();
    if(min > top)
    {
      cout << min << "," << top << "," << i << endl;
      return false;
    }
    min = top;
  }
  return true;
}

int main()
{
  string str = test2() ? "ok" : "falied";
  cout << str << endl;
  
}
