#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 71;
const int inf = N*N + 10;
const int lines = 3450;

vector<pair<int,int>> directions = { {0,-1}, {-1,0}, {0,1}, {1,0} };

void read(int& u,int& v) {
    string s; cin >> s;
    stringstream ss(s);
    string num;
    vector<int> arr;
    while (getline(ss, num, ','))
        arr.push_back(stoi(num));
    u = arr[0];
    v = arr[1];
}

void print(vector<vector<char>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << grid[i][j];
        cout << endl;
    }
}

bool safe(int x,int y) {
    return 0 <= x && x < N && 0 <= y && y < N;
}

bool bfs(vector<pair<int,int>>& hurdles,int z) {
    vector<vector<char>> grid(N, vector<char>(N, '.'));
    int n = hurdles.size();
    for (int i = 0; i <= z; i++)
        grid[hurdles[i].first][hurdles[i].second] = '#';

    vector<vector<int>> dist(N, vector<int>(N, inf));
    dist[0][0] = 0;
    queue<pair<int,int>> Q;
    Q.push({0,0});
    while (!Q.empty()) {
        auto v = Q.front();
        Q.pop();

        grid[v.first][v.second] = 'O';
        if (v.first == N-1 && v.second == N-1)
            break;

        for (auto k: directions) {
            int i = v.first + k.first;
            int j = v.second + k.second;

            if (safe(i,j) && dist[i][j] == inf && grid[i][j] == '.') {
                Q.push({i,j});
                dist[i][j] = dist[v.first][v.second] + 1;
            }
        }
    }
    return dist[N-1][N-1] < inf;
}

void solve() {
    vector<pair<int,int>> hurdles;
    for (int i = 0; i < lines; i++) {
        int u,v;
        read(v,u);
        hurdles.push_back({u,v});
    }

    int l = -1, r = lines;
    while (r-l > 1) {
        int mid = (l+r)>>1;
        if (bfs(hurdles, mid))
            l = mid;
        else
            r = mid;
    }
    cout << hurdles[r].second << "," << hurdles[r].first;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
