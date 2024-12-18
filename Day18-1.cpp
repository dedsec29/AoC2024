#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 71;
const int inf = N*N + 10;
const int lines = 1024;

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

void solve() {
    vector<vector<char>> grid(N, vector<char>(N, '.'));
    vector<vector<int>> dist(N, vector<int>(N, inf));
    for (int i = 0; i < lines; i++) {
        int u,v;
        read(v,u);
        grid[u][v] = '#';
    }

    // print(grid);

    dist[0][0] = 0;
    queue<pair<int,int>> Q;
    Q.push({0,0});
    while (!Q.empty()) {
        auto v = Q.front();
        grid[v.first][v.second] = 'O';
        // print(grid);
        // cout << endl;
        Q.pop();

        for (auto k: directions) {
            int i = v.first + k.first;
            int j = v.second + k.second;

            if (safe(i,j) && dist[i][j] == inf && grid[i][j] == '.') {
                Q.push({i,j});
                dist[i][j] = dist[v.first][v.second] + 1;
            }
        }
    }

    cout << dist[N-1][N-1];
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
