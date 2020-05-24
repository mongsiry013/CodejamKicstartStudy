#include <bits/stdc++.h>
using namespace std;
void solve(){
  int N, S; cin >> N >> S;
  vector<vector<int>> A(N);
  vector<int> C(N);
  map<vector<int>, int> m;
  for(int i=0; i<N; i++){
    cin >> C[i];
    for(int j=0; j<C[i]; j++){
      int t; cin >> t;
      A[i].push_back(t);
    }
    sort(A[i].begin(), A[i].end());
    m[A[i]]++; 
  }
  long long sum = 0;
  for(int i=0; i<N; i++){
    int sub = 0;
    for(int c=0; c<(1<<A[i].size()); c++){
      vector<int> t;
      if(c&(1<<0)) t.push_back(A[i][0]); 
      if(c&(1<<1)) t.push_back(A[i][1]); 
      if(c&(1<<2)) t.push_back(A[i][2]); 
      if(c&(1<<3)) t.push_back(A[i][3]); 
      if(c&(1<<4)) t.push_back(A[i][4]); 
      if(m.count(t)>0) sub += m[t];
    }
    sum += (N-sub);
  }
  cout << sum << endl;
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

