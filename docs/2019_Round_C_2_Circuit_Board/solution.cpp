#include<bits/stdc++.h>
 
using namespace std;

void solve(int TestCase) {
    int r, c, k;
    cin >> r >> c >> k;
    
    auto A = vector<vector<int>>(r, vector<int>(c));
    for(auto i = 0; i < r; ++i)
    {
        for(auto j = 0; j < c; ++j)
        {
            cin >> A[i][j];
        }
    }

    auto B = vector<vector<int>>(r, vector<int>(c));
    for(auto i = 0; i < r; ++i)
    {
        for(auto j = c - 1; j >= 0; --j)
        {
            if(j == c - 1) {
                B[i][j] = 1;
                continue;
            }

            auto max_val = -1;
            auto min_val = 1000000;
            for(auto p = 1; j + p <= c; ++p)
            {
                max_val = max(max_val, A[i][j + p - 1]);
                min_val = min(min_val, A[i][j + p - 1]);

                if(max_val - min_val > k)
                    break;
                else
                    B[i][j] = p;
            }
        }
    }

    auto ret = 0;
    for(auto i = 0; i < r; ++i)
    {
        for(auto j = 0; j < c; ++j)
        {
            auto min_val = 1000000;
            for(auto p = 1; i + p <= r; ++p)
            {
                min_val = min(min_val, B[i + p - 1][j]);
                ret = max(ret, p * min_val);
            }
        }
    }

    cout << ret << endl;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
 
    int t = 1;
    cin >> t;
    for(auto i = 1; i <= t; ++i) {
        cout << "Case #"<< i << ": ";
        solve(i);
    }
}