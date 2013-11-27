const int n = 5000000;
int c[n+5];
int main(){
  for(int j=1; j<=n; j++)
    for(int i=j; i<=n; i+=j)
      c[i]++;
  return 0;
}
