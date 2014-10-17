#include<cmath>
#include<stack>
#include<iostream>
#include<time.h>
#include<map>
using namespace std;
const int Blank = 12;
int tile[4][3] = { 1, 2, 3,
		   4, 5, 6,
		   7, 8, 9,
		   10,11,12};

stack<int> ans;
map<long long, bool>  closedList;

//A*用の評価関数, 空白以外の各タイルのゴールの位置とのマンハッタン距離の和
int evaluate(){
  int cost=0;
  for(int i=0; i<4;i++){
    for(int j=0; j<3;j++){
      if(tile[i][j] == Blank)
	continue;
      int num = tile[i][j];
      cost += abs((num-1)%3 - j) + abs(floor((num-1)/3)-i);      
    }
  }
  return cost;
}

//各タイルの値を4bitで表現し, long long 型の値で表現する 
long long toLongLong(){
  long long state = 0;
  for(int i=0; i<4; i++){
    for(int j=0; j<3; j++){
      int n = (3*i + j)*4;
      state |= tile[i][j]<<n;
    }
  }
  return state;
}


//4近傍探索用
int dx[] = {-1,1,0,0};
int dy[] = { 0,0,1,-1};

//limit : 最大手数, n : 現在の手数, blankI,J : 空白の位置
bool calc(int limit, int n, int blankI, int blankJ){
  
  if(evaluate() == 0)
    return true;  //現在の状態がゴールならtrue
  
  if(n + evaluate() > limit)
    return false;  //今までの手数 + ここからゴールまでにかかる最低手数がlimitを超えるならfalse 

  long long state = toLongLong(); //現在のタイルの情報をlong longに変換 
  if(closedList.count(state) != 0) //既にしらべて居たら, false 
    return false;

  closedList[state] = true; //探索済みにする. 

  for(int i=0; i<4;i++){
    int moveI = blankI + dx[i];  //4近傍の位置から動かすタイルを決める
    int moveJ = blankJ + dy[i];

    //外にあるタイルは無視 
    if(moveI < 0 || moveJ < 0 || moveI>3 || moveJ > 2) 
      continue;

    tile[blankI][blankJ] = tile[moveI][moveJ];    //タイルを動かす
    tile[moveI][moveJ] = Blank;

    //再帰処理
    if(calc(limit, n+1, moveI, moveJ)){
      ans.push( (moveI<<4)|moveJ); //動かしたタイルの位置をスタックにプッシュ
      tile[moveI][moveJ] = tile[blankI][blankJ]; //タイルを元に戻す 
      tile[blankI][blankJ] = Blank;
      return true;
    }
 
    tile[moveI][moveJ] = tile[blankI][blankJ];    //タイルを元に戻す
    tile[blankI][blankJ] = Blank;
  }
  return false;
}

//反復深化で解く 
void iteral(int blankI, int blankJ){
  int minStep = evaluate();
  cout << "start" << endl;
 
  while(!calc(minStep,0,blankI, blankJ)){
    closedList.clear(); //探索済みのハッシュを空に 
    minStep++;
  }
}


//デバッグ用, パズルを動かす. 
void shufflePuzzle(){
  int bi, bj;
  
  for(int i=0; i<4; i++){
    for(int j=0; j<3; j++){
      if(tile[i][j] != Blank)
	continue;
      bi = i;
      bj = j;
      break;
    }
  }
  int r = rand()%4;
  int mi = bi + dx[r];
  int mj = bj + dy[r];

  while(mi<0 || mj<0 || mi>3 || mj>2){
    r = rand()%4;
    mi = bi + dx[r];
    mj = bj + dy[r];  
  }
  tile[bi][bj] = tile[mi][mj];
  tile[mi][mj] = Blank;
}

//タイルの状態を表示する. 
void printTile(){
  for(int i=0; i<4; i++){
    for(int j=0; j<3; j++){
      if(tile[i][j] != Blank)
	printf("%2d ", tile[i][j]);
      else
	printf("   ");
    }
    printf("\n");
  }
  printf("\n");
}

int main(){
  srand((unsigned int)time(NULL));

  cout << "Shuffle Num = ";
  int n;
  cin >> n;
  for(int i=0; i<n; i++){
    shufflePuzzle();
  }

  
  int bi,bj;
  for(int i=0; i<4;i++){
    for(int j=0; j<3; j++){
      if(tile[i][j] != Blank)
	continue;
      bi = i;
      bj = j;
      break;
    }
  }
  
  iteral(bi, bj);  //反復深化 
  
  cout << ans.size() << "手" << endl;
  
  printTile();  
  while(!ans.empty()){
    int mi = (ans.top()&0xf0)>>4;
    int mj = (ans.top()&0xf);
    tile[bi][bj] = tile[mi][mj];
    tile[mi][mj] = Blank;
    bi=mi; bj=mj;
    printTile();
    ans.pop();
  }
}



