#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 141;
const int inf = N*N + 10;
const int deadline = 100;

unordered_map<int,int> finishTimes;
set<pair<pair<int,int>, pair<int,int>>> cheats;

vector<int> di = {0, -1, 0, 1};
vector<int> dj = {-1, 0, 1, 0};

bool safe(int i,int j) {
    return 1 <= i && i <= N && 1 <= j && j <= N;
}

vector<vector<int>> bfs(vector<vector<char>>& grid,pair<int,int> source) {
    vector<vector<int>> dist(N+1, vector<int>(N+1, inf));
    dist[source.first][source.second] = 0;
    queue<pair<int,int>> Q;
    Q.push(source);
    while (!Q.empty()) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int k = 0; k < 4; k++) {
            int i = x + di[k];
            int j = y + dj[k];
            if (safe(i,j) && dist[i][j] == inf && grid[i][j] != '#') {
                dist[i][j] = dist[x][y] + 1;
                Q.push({i,j});
            }
        }
    }
    return dist;
}

void countType(vector<vector<char>>& grid,vector<vector<int>>& dist1,vector<vector<int>>& dist2,pair<int,int> destination) {
    for (int x = 1; x <= N; x++) {
        for (int y = 1; y <= N; y++) {
            if (dist1[x][y] == inf)
                continue;
            // Impossible: start cheat now, in next second be in free cell
            // Does not make sense it will never save us seconds

            // Start cheat now, must go in #, then go either free or wall
            //      If I go free, ok    else adj free wall must
            //  BUT question says I must go free

            for (int k1 = 0; k1 < 4; k1++) {
                int a = x + di[k1];
                int b = y + dj[k1];
                if (safe(a,b) && grid[a][b] == '#') {
                    // Now I am in a wall. Explore other neighbors
                    for (int k2 = 0; k2 < 4; k2++) {
                        int c = a + di[k2];
                        int d = b + dj[k2];

                        // don't visit from where I have come already
                        if (make_pair(c,d) == make_pair(x,y))
                            continue;

                        // Now I am in the second move
                        if (safe(c,d) && cheats.find({{x,y}, {c,d}}) == cheats.end()) {
                            if (grid[c][d] != '#') {
                                int moves = dist1[x][y] + dist2[c][d] + 2;
                                finishTimes[moves]++;
                            }
                        }
                        cheats.insert({{x,y}, {c,d}});    
                    }
                }
            }
        }
    }
}

void solve() {
    vector<vector<char>> grid(N+1, vector<char>(N+1));
    pair<int,int> source, destination;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S')
                source = {i,j};
            else if (grid[i][j] == 'E')
                destination = {i,j};
        }
    }    

    vector<vector<int>> dist1 = bfs(grid, source);
    vector<vector<int>> dist2 = bfs(grid, destination);

    int original = dist1[destination.first][destination.second];
    countType(grid, dist1, dist2, destination);
    int ans = 0;
    for (auto i: finishTimes) {
        // cout << original << " " << i.first << endl;
        if (original - i.first >= deadline)
            ans += i.second;
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
