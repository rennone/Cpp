#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;
class rect;

int n,r;

map<pair<int, int>, bool> vertex;
int main(){
  while(cin>>n>>r,n|r){
    int a,b,c,d;

    if(!vertex.empty()) vertex.clear();
    
    for(int i=0; i<n; i++){
      cin >> a >> b >> c >> d; //左下(a,b) 右上(c,d)      
      for(int x=a; x<c-0.5; x++)
	for(int y=b; y<d-0.5; y++)
	  vertex[make_pair(x,y)] = true; //長方形が包んでいる, 1*1の格子を全てセット
    }

    cout << vertex.size() << endl;
    if(r == 1) continue;
    int l=0;
    map<pair<int,int>, bool>::iterator it = vertex.begin();
    while(it != vertex.end()){
      pair<int,int> v = (*it).first;
      int x = v.first;
      int y = v.second;
      l+=4;
      for(int i=0; i<4; i++){
	int dx = (i-1)%2;
	int dy = (2-i)* (i%2);
	if(vertex.find(make_pair(x+dx,y+dy)) != vertex.end()){
	  l--;
	}
      }
      ++it;
    }
    cout << l << endl;
  }
}
