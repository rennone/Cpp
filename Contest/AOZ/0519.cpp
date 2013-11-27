#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<cstring>
using namespace std;

int n,m;
int rank[5002]; //各チームの順位(重複あり)
map<int,vector<int> >win;
map<int,vector<int> >ans; //各順位のチーム()

int calc(int x){
  if(rank[x] > 0) return rank[x];

  int winNum = win[x].size();
  if(winNum==0){ //勝ち数が0の時は一番下の順位とする(重複ありの順位)
    rank[x] = n;
    return rank[x];
  }
  int r=n;
  for(int i=0; i<winNum;i++){
    r = min(r,calc(win[x][i])-1);
  }
  rank[x] = r;
  return rank[x];  
}

int main(){  
    cin>>m;
    int winner, loser;
    win.clear();
    ans.clear();
    memset(rank,0,sizeof(rank));
    for(int i=1;i<=m;i++){
      cin >> winner >> loser;
      win[winner].push_back(loser);
    }
    
    for(int i=1; i<=n;i++)
      ans[calc(i)].push_back(i);
    
    bool flag = false;
    map<int,vector<int> >::iterator it;
    for(it = ans.begin(); it!=ans.end();it++){
      flag |= (*it).second.size()>1;
      for(int i=0; i<(*it).second.size(); i++)
	cout << (*it).second[i] << endl;
    }
    cout << (flag ? 1 : 0) << endl;    
  return 0;
}
