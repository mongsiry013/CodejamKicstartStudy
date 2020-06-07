#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;

typedef struct Fenwick{
    vector<LL> nodes;
    int n;
    
    Fenwick(){};
    void resize(int n_){
        n = n_;
        nodes.clear();
        nodes.resize(n);
    }
    
    void update(int idx, int val){
        while(idx <= n){
            nodes[idx] += val;
            idx += (idx & -idx);
        }
    }
    
    LL getSum(int idx){
        LL querySum = 0;
        while(idx > 0){
            querySum += nodes[idx];
            idx -= (idx & -idx);
        }
        return querySum;
    }
    
}Fenwick;

void candiesSweetness(){
    int tc, tcn = 0;
    Fenwick a, b;
    cin >> tc;
    while(tc--){
        int n, q;
        LL totalSweet = 0;
        cin >> n >> q;
        a.resize(n + 1);
        b.resize(n + 1);
        for(int i = 0; i < n; i++){
            int val;
            cin >> val;
            a.update(i + 1, val * (i%2 == 0 ? 1: -1));
            b.update(i + 1, val * (i%2 == 0 ? 1: -1) * (i + 1));
        }
        
        for(int i = 0; i < q; i++){
            string query;
            cin >> query;
            if( query == "Q"){
                int left, right;
                cin >> left >> right;
                LL sweet = (b.getSum(right) - b.getSum(left - 1));
                sweet -= (a.getSum(right) - a.getSum(left - 1)) * (left - 1);
                if( left % 2 == 0)
                    sweet *= -1;
                totalSweet += sweet;
            }
            else{
                int idx;
                LL val;
                cin >> idx >> val;
                LL origVal;
                origVal = a.getSum(idx) - a.getSum(idx - 1);
                a.update(idx, val * (idx%2 ? 1: -1) - origVal);
                origVal = b.getSum(idx) - b.getSum(idx - 1);
                b.update(idx, val * (idx%2 ? 1: -1) * idx - origVal);
            }
        }
        cout << "Case #" << ++tcn << ": " << totalSweet << "\n";
    }
}

int main(void){
    freopen("input.txt","r",stdin);
    candiesSweetness();
    return 0;
}
