#include<bits/stdc++.h>
 
using namespace std;

class SegTree {
private :
    int n;
    vector<long long> T;

    void upd(int pos, long long val, int i, int l, int r)
    {
        if(l + 1 == r) {
            T[i] = val;
            return;
        }

        int m = (l + r) / 2;
        if(pos < m) upd(pos, val, i * 2 + 1, l, m);
        else upd(pos, val, i * 2 + 2, m, r);
        T[i] = T[i * 2 + 1] + T[i * 2 + 2];
    }

    long long get(int left, int right, int i, int l, int r)
    {
        if(right <= l || left >= r) return 0;
        if(left <= l && r <= right) return T[i];

        int m = (l + r) / 2;
        return get(left, right, i * 2 + 1, l, m) 
                + get(left, right, i * 2 + 2, m, r);
    }

public :

    SegTree(int n)
    : n(n), T(n * 4 + 20)
    {}

    void upd(int pos, long long val) { upd(pos, val, 0, 0, n); }
    long long get(int left, int right) { return get(left, right, 0, 0, n); }
};

void solve(int TestCase) {
    int n, q;
    cin >> n >> q;
    auto A = vector<long long>(n);
    for(auto& x : A)
        cin >> x;
    
    SegTree t1(n), t2(n);
    for(auto i = 0; i < n; ++i)
    {
        t1.upd(i, A[i] * (i % 2 == 0 ? 1:-1));
        t2.upd(i, A[i] * (i + 1) * (i % 2 == 0 ? 1:-1));
    }

    long long ret = 0;
    for(auto i = 0; i < q; ++i)
    {
        char command;
        cin >> command;
        if(command == 'Q') {
            int left, right;
            cin >> left >> right;
            left--;

            auto ret1 = t1.get(left, right);
            auto ret2 = t2.get(left, right);
            ret += (ret2 - left * ret1) * (left % 2 == 0 ? 1:-1);
        }
        else {
            long long pos, val;
            cin >> pos >> val;
            pos--;

            t1.upd(pos, val * (pos % 2 == 0 ? 1:-1));
            t2.upd(pos, val * (pos + 1) * (pos % 2 == 0 ? 1:-1));
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
