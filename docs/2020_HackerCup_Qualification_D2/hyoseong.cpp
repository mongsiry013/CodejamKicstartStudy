#include<bits/stdc++.h>
 
using namespace std;

constexpr long long INF = numeric_limits<long long>::max();
long long n, m, a, b, i;
vector<vector<int>> edges;
vector<long long> P, C;

constexpr int MAX_N = 2e6;
long long T[MAX_N * 4 + 20];
bool tree_inited = false;
void tree_init()
{
    tree_inited = true;
    for(auto i = 0; i < MAX_N * 4 + 20; ++i) T[i] = numeric_limits<long long>::max();
}
void put(int i, int l, int r, long long val, int p)
{
    if(!tree_inited) tree_init();
    T[i] = min(T[i], val);
    if(l + 1 == r)
        return;

    int m = (l + r) / 2;
    if(p < m)
        put(i * 2 + 1, l, m, val, p);
    else
        put(i * 2 + 2, m, r, val, p);
}
long long get(int i, int l, int r, int L, int R)
{
    if(!tree_inited) tree_init();
    if(L <= l && R >= r)
        return T[i];

    int m = (l + r) / 2;
    long long ret = numeric_limits<long long>::max();
    if(L < m)
        ret = min(ret, get(i * 2 + 1, l, m, L, R));
    if(R > m)
        ret = min(ret, get(i * 2 + 2, m, r, L, R));

    return ret;
}

bool find_path(int cur, int prev, vector<int>& cur_path) {
    cur_path.push_back(cur);
    if(cur == b) return true;

    for(auto& nxt : edges[cur]) {
        if(nxt == prev) continue;
        if(find_path(nxt, cur, cur_path))
            return true;
    }
    cur_path.pop_back();
    return false;
}

void dfs(int cur, int prev, int d) {
    if(d > m) return;

    auto cur_min_cost = get(0, 0, MAX_N, i+d, i+m+1);
    if(cur_min_cost == INF) return;

    if(C[cur] && cur_min_cost + C[cur] < get(0, 0, MAX_N, i + m - d, i + m - d + 1))
        put(0, 0, MAX_N, cur_min_cost + C[cur], i + m - d);

    for(auto nxt : edges[cur]) {
        if(nxt == prev) continue;
        dfs(nxt, cur, d+1);
    }
}

void solve(int TestCase) {
    tree_inited = false;
    cin >> n >> m >> a >> b;
    a--, b--;

    P = vector<long long>(n);
    C = vector<long long>(n);

    for(auto i = 0; i < n; ++i) {
        cin >> P[i] >> C[i];
        P[i]--;
    }

    edges = vector<vector<int>>(n, vector<int>{});
    for(auto i = 0; i < n; ++i) {
        if(P[i] == -1) continue;
        edges[i].push_back(P[i]);
        edges[P[i]].push_back(i);
    }

    vector<int> path;
    find_path(a, -1, path);

    put(0, 0, MAX_N, 0, m);

    for(i = 0; i < path.size(); ++i) {
        auto cur = path[i];
        auto cur_min_cost = get(0, 0, MAX_N, i, i+m+1);
        if(C[cur] && cur_min_cost != INF) {
            if(get(0, 0, MAX_N, i + m, i + m + 1) > cur_min_cost + C[cur])
                put(0, 0, MAX_N, cur_min_cost + C[cur], i+m);
        }

        for(auto nxt : edges[cur]) {
            if(i && path[i-1] == nxt) continue;
            if(i+1 < path.size() && path[i+1] == nxt) continue;
            dfs(nxt, cur, 1);
        }
    }

    int last = (int)path.size() - 1;
    auto ret = get(0, 0, MAX_N, last, last+m+1);
    if(ret == INF)
        ret = -1;
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
