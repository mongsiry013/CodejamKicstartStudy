#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
using namespace std;
#define OBS -100000
typedef pair<int,int> PII;
struct Result{
    int energy_sum;
    bool visit;
};

struct Cell{
    int x, y;
    int e = 0;
};

bool isPossiblePath(int x, int y, int n, int m){
    if( x >=0 && x < n && y >=0 && y < m)
        return true;
    return false;
}

Result bfs(vector<vector<int>> &grid, Cell& start_c, Cell& end_c, map<PII, int> trap2idx, vector<int>& adj, int trap_bit){
    queue<Cell> q;
    vector<vector<bool>> visit(grid.size(), vector<bool>(grid[0].size(), false));
    int energy_sum = 0;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};
    q.push(start_c);
    visit[start_c.x][start_c.y] = true;
    int n = grid.size(), m = grid[0].size();

    while(!q.empty()){
        Cell cur = q.front();
        q.pop();
        int x = cur.x;
        int y = cur.y;
        energy_sum += grid[x][y];
        for(int i = 0; i < 4; i++){
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            if(!isPossiblePath(next_x, next_y, n, m) || visit[next_x][next_y])
                continue;
            if(grid[next_x][next_y] == OBS){
                if(trap2idx.count(PII(next_x, next_y))){
                    adj[trap_bit] |= trap2idx[PII({next_x, next_y})];
                }
                continue;
            }

            q.push(Cell({next_x, next_y}));
            visit[next_x][next_y] = true;
        }
        
    }
    
    return Result({energy_sum, visit[end_c.x][end_c.y]});
}

void caveEscape(){
    int n, m, e, s_r, s_c, t_r, t_c;
    vector<vector<int>> grid;
    vector<Cell> traps;
    vector<int> energy, adj;
    vector<bool> is_escape;
    map<PII, int> trap2idx;

    cin >> n >> m >> e >> s_r >> s_c >> t_r >> t_c;
    --s_r, --s_c, --t_r, --t_c;
    grid.resize(n, vector<int>(m));
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> grid[i][j];
            if(grid[i][j] > OBS && grid[i][j] < 0){
                traps.push_back(Cell({i, j, grid[i][j]}));
                trap2idx[PII(i, j)] = 1 << (traps.size() - 1);
            }
        }   
    }
    grid[s_r][s_c] = e;

    Cell start_c = {s_r, s_c};
    Cell end_c = {t_r, t_c};

    energy.resize(1<<traps.size(), 0);
    is_escape.resize(1<<traps.size(), false);
    adj.resize(1<<traps.size(), 0);

    for(int i = 0; i < (1<<traps.size()); i++){
        vector<int> trap_energy;
        for(int j = 1, k = 0; j < (1<<traps.size()); j <<= 1, k++){
            if( !(i & j )){
                int x = traps[k].x;
                int y = traps[k].y;
                grid[x][y] = OBS;
            }
        }
        Result result = bfs(grid, start_c, end_c, trap2idx, adj, i);
        if( !i ){
            energy[0] = result.energy_sum;
            is_escape[0] = result.visit;
        }
        else{
            for(int j = 1, k = 0; j <= i; j <<= 1, k++){
                if( !(i&j) || !(adj[i-j]&j))
                    continue;
                int energy_need = grid[traps[k].x][traps[k].y];
                if( -energy_need <= energy[i^j] ){
                    energy[i] = max(energy[i], result.energy_sum);
                    is_escape[i] = result.visit;
                }
            }
        }
        int num = 0;
        for(int j = 1, k = 0; j < (1<<traps.size()); j <<= 1, k++){
            if( !(i & j )){
                int x = traps[k].x;
                int y = traps[k].y;
                grid[x][y] = traps[k].e;
            }
        }
    }
    
    int max_energy = -1;
    for(int i = 0; i < (1<< traps.size()); i++){
        if(is_escape[i]){
            max_energy = max(max_energy, energy[i]);
        }
    }    
    cout << max_energy << "\n";
}


void solve(){
    int tc, tcn = 0;
    cin >> tc;
    while(tc--){
        cout << "Case #" << ++tcn << ": ";
        caveEscape();
    }
}


int main(void){
    freopen("input.txt","r",stdin);
    solve();
    return 0;
}
