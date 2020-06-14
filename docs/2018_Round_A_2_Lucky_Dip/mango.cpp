#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

void solve(){
    int tc, tcn = 0;
    cin >> tc;
    while(tc--){
        int n, k;
        vector<double> item, expectations, itemSum;
        cin >> n >> k;
        item.resize(n);
        itemSum.resize(n);
        expectations.resize(k + 1);
        for(int i = 0; i < n; i++){
            cin >> item[i];  
        }
        
        sort(item.begin(), item.end());
        
        for(int i= 0; i< n; i++){
            itemSum[i] = item[i];
            if( i )
                itemSum[i] += itemSum[i-1];
        }
        expectations[0] = itemSum[n-1] / n;
        for(int i = 1; i <= k; i++){
            int numLessThan = lower_bound(item.begin(), item.end(), expectations[i-1]) - item.begin();
            expectations[i] = expectations[i - 1] * numLessThan / n;
            double sumGE = itemSum[n - 1];
            if( numLessThan )
                sumGE -= itemSum[numLessThan - 1];
            expectations[i] += 1./ n * sumGE;
        }
        printf("Case #%d: %.8lf\n", ++tcn, expectations[k]);
        
    }
    
}

int main(void){
    freopen("input.txt","r",stdin);
    solve();
    return 0;
}