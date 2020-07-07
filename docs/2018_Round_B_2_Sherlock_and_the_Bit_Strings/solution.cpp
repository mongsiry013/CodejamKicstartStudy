#include <bits/stdc++.h>
using namespace std;

vector<pair<int,int> > blc[101];
long long dp[101][1<<16];
int N, K;
long long P;
unsigned int filter[17]={0b0000000000000000,
                0b0000000000000001,
                0b0000000000000011,
                0b0000000000000111,
                0b0000000000001111,
                0b0000000000011111,
                0b0000000000111111,
                0b0000000001111111,
                0b0000000011111111,
                0b0000000111111111,
                0b0000001111111111,
                0b0000011111111111,
                0b0000111111111111,
                0b0001111111111111,
                0b0011111111111111,
                0b0111111111111111,
                0b1111111111111111,
};
bool check(int ix, unsigned int s){
  for(auto& lc : blc[ix]){
    int l = lc.first;
    int c = lc.second;
    unsigned int cmp = (s & filter[l]) & 0xffff;
    if(__builtin_popcount(cmp) != c) return false;
  }
  return true;
}

long long dfs(int ix, unsigned int s){
  if(ix==N+1) return 0;
  
  long long& ret = dp[ix][s];
  if(ret != -1) return ret;
  
  if(!check(ix,s)) return ret=0;
  
	if(ix == N) return ret=1;
  
  unsigned int ns = (s<<1) & 0xffff;
  ret = dfs(ix+1, ns);
  if(ret < P)
    ret += dfs(ix+1, ns+1);
  return ret;
}

void solve(){
  cin >> N >> K >> P;
  for(int i=1 ; i<=N ; ++i)
    blc[i].clear();
  memset(dp,-1,sizeof(dp));

  for(int k=0; k<K; k++){
    int a, b, c; cin >> a >> b >> c;
    int l = b-a+1;
    blc[b].push_back({l,c});
  }
 	
  dfs(0,0);
  
  unsigned int s = 0;
  string ans="";
  for(int ix=1; ix<=N; ix++){
    s = (s<<1) & 0xffff;
    if(dp[ix][s]>=P) ans += "0";
    else{
      P -= dp[ix][s];
      s = (s+1) & 0xffff;
      ans += "1";
    }
  }
  cout << ans << endl;
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

