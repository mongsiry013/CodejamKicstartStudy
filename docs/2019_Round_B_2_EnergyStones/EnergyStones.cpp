#include <bits/stdc++.h>
using namespace std;
void solve(){
  int N; cin >> N;
  vector<int> S(N), E(N), L(N), id(N);
  for(int i=0; i<N; i++){
    cin >> S[i] >> E[i] >> L[i];
    id[i] = i;
  }
  
  function<int()> t1 = [&]()->int{
    sort(id.begin(), id.end(), [&](int l, int r){return L[l]>L[r];});    
    int dp[N][10001]; memset(dp,-1,sizeof(int)*N*10001);
    function<int(int,int)> f = [&](int ix, int t)->int{
      if(ix==N) return 0;
      int i = id[ix];
      if(dp[i][t]!=-1) return dp[i][t];
      int& ret = dp[i][t];
      ret = f(ix+1,t);
      if(E[i]-L[i]*t > 0){
        ret = max(ret, E[i]-L[i]*t + f(ix+1,t+S[i]));
      }
      return ret;
    };
    return f(0,0);
  };

  function<int()> t2 = [&]()->int{
    sort(id.begin(), id.end(), [&](int l, int r){return S[r]*L[l]>S[l]*L[r];});    
    int dp[N][10001]; memset(dp,-1,sizeof(int)*N*10001);
    function<int(int,int)> f = [&](int ix, int t)->int{
      if(ix==N) return 0;
      int i = id[ix];
      if(dp[i][t]!=-1) return dp[i][t];
      int& ret = dp[i][t];
      ret = f(ix+1,t);
      if(E[i]-L[i]*t > 0){
        ret = max(ret, E[i]-L[i]*t + f(ix+1,t+S[i]));
      }
      return ret;
    };
    return f(0,0);
  };
  cout << t2() << endl;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int t = 1;
  cin >> t;
  for(int i = 1; i<=t; i++){
    cout << "Case #" << i << ": ";
    solve();
  } 

}
