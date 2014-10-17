#include<iostream>
#include<queue>
using namespace std;

#define MAX_N 10000
int N, L, P;
int A[MAX_N+1], B[MAX_N+1];


void calc()
{
  A[N] = L; B[N]= 0;
  int ans = 0, pos = 0, tank = P;
  priority_queue<int> que;
  
  for(int i=0; i<N; i++)
  {
    int d = A[i] - pos; //現在地からスタンドまでの距離
    //足りない場合,過去のスタンドで補給した事にする.
    while(tank - d < 0)
    {
      if(que.empty())
      {
        cout << -1 << endl;
        return;
      }
      tank += que.top();
      que.pop();
      ans++;
    }    
    tank -= d;
    pos = A[i];
    que.push(B[i]);
  }

  cout << ans << endl;
}

int main()
{
  while( cin>>N>>L>>P, N|L|P )
  {
    for(int i=0; i<N; i++)
      cin >> A[i];
    for(int i=0; i<N; i++)
      cin >> B[i];

    calc();
  }  
}
