#include <bits/stdc++.h>
using namespace std;
#define int long long

const int n = 40;

vector<int> di = {0,-1,0,1};
vector<int> dj = {-1,0,1,0};

bool safe(int x,int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int bfs(int sx,int sy,vector<vector<int>>& arr) {
    vector<vector<int>> vis(n+1, vector<int>(n+1));
    queue<pair<int,int>> Q;
    Q.push({sx, sy});
    vis[sx][sy] = 1;
    int cnt = 0;

    while (!Q.empty()) {
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();

        if (arr[i][j] == 9) 
            cnt += vis[i][j];

        for (int k = 0; k < 4; k++) {
            int x = i + di[k];
            int y = j + dj[k];
            if (safe(x,y) && arr[x][y]-1 == arr[i][j]) {
                if (vis[x][y] == 0) 
                    Q.push({x,y});
                vis[x][y] += vis[i][j];
            }
        }
    }
    return cnt;
}

void solve() {
    vector<vector<int>> arr(n+1, vector<int>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            arr[i][j] = c-'0';
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (arr[i][j] == 0)
                ans += bfs(i,j, arr);
        }
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

