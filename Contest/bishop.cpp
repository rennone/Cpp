#include<iostream>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
using namespace std;

long long num;
int N,K;

long long memo[33][33][905];

//分けた後は, 図を回転させて, 十字で考える.
//pos のこり行数, p選択肢の数, k残りの駒数
long long calcA(int pos,int p, int k){
  if(k==0)
    return 1; //駒が無い場合置かないの１択のみ, 中心をすぎても,駒が無ければok(そこで終了すれば良い)  
    
  if(k<0 || pos < k || pos<=0)  
    return 0;  //残りの駒が負, もしくは, まだ置く駒が残っていて, 残り行数が0以下, 残りの駒より少なければ失敗
    
  if(memo[pos][p][k] != -1)
    return memo[pos][p][k];  //既にメモしてたらそれを返す

  // のこり1行では対称となる行が無いので選択肢がpだけ 
  if(pos == 1){
    memo[pos][p][k] = p; //ここに入る時, kは必ず1である.
    return p;
  }
  
  long long a,b,c;
  a = p*(p-1)*calcA(pos-2, p, k-2);  //自身と対称位置の両方に置く場合の数, 次の行の選択肢はp
  b = 2*p*calcA(pos-2, p+1, k-1);    //この行, もしくは反対側の行にしか置かない場合, 次の行の選択肢はp+1  
  c = calcA(pos-2, p+2, k);          //何も置かずに, 次の行にまわす,次の行の選択肢はp+2
  memo[pos][p][k] = a+b+c;
  return a+b+c;  
}

long long calc(){
  num=0;
  if(N==1 && K==1)
    return 1;
  
  if(K>2*N-2)
    return 0;//多分最大で2n-2までしか置けない.

  if(K==0)
    return 1;
  else if(K==1)
    return N*N;

  int maxK = min(N-1, K);
  int minK = K-maxK;
  if(N%2 == 0){
    for(int i=minK; i<=maxK; i++){
      num += calcA(N,1,i)*calcA(N,1,K-i);
    }
  }
  else{
    for(int i=minK; i<=maxK; i++){
      num += calcA(N,1,i)*calcA(N-1,2,K-i);
    }

  }
  return num;
}

//正方形を互いに影響を及ぼさない領域で分けて, それぞれの場合の数の積.
int main(){
  memset(memo, -1, sizeof(memo));
  
   while(cin>>N>>K, N|K){     
     cout << calc() << endl;     
   }
  
   /*
  for(int i=1; i<30; i++){
    for(int j=1; j<i*i; j++){
      N=i; K=j;
      calc();
	cout << N << " " << K << endl;
      }
  
    }
  }
   */
  return 0;
}
