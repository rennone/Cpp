#include<iostream>
#include<string.h>
#include<complex>
#include<map>
#include<vector>
using namespace std;
int n;
int ans;
bool maps[5002][5002];
int vertex[3001][2];

bool range(int x, int y){
  if(x>=0 && y>=0 && x<=5000 && y<=5000)
    return true;
  else
    return false;
}

int main(){
  while(cin>>n, n){

    memset(maps,0, sizeof(maps));
    memset(vertex,0,sizeof(vertex));
    int x,y;    
    for(int i=0;i<n;i++){
      cin >> x >> y;
      maps[x][y] = 1;
      vertex[i][0] = x;
      vertex[i][1] = y;      
    }

    ans = 0;
    for(int i=0; i<n-1;i++){
      for(int j=i+1; j<n; j++){
	
	int dy = vertex[i][0] - vertex[j][0]; //i-jのx差分がy差分
	int dx = vertex[i][1] - vertex[j][1];
	int s = dx*dx + dy*dy;
	if(s <= ans) continue;

	int cx1 = vertex[i][0] + dx; //ijと直角に位置する点
	int cy1 = vertex[i][1] - dy;
		
	int cx2 = vertex[i][0] - dx;
	int cy2 = vertex[i][1] + dy;

	int cx3 = vertex[j][0] + dx;
	int cy3 = vertex[j][1] - dy;

	int cx4 = vertex[j][0] - dx;
	int cy4 = vertex[j][1] + dy;

	if( range(cx1,cy1) && range(cx3,cy3) && maps[cx1][cy1] && maps[cx3][cy3]){
	  ans = s;
	  continue;
	}

	if( range(cx2,cy2) && range(cx4,cy4) && maps[cx2][cy2] && maps[cx4][cy4]){
	  ans = s;
	  continue;
	}
      }
    }

    cout << ans << endl;
  }
  return 0;
}
