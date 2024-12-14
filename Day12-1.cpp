#include <bits/stdc++.h>
using namespace std;
#define int long long

const int n = 140;

vector<int> di = {0, -1, 0, 1};
vector<int> dj = {-1, 0, 1, 0};

bool safe(int x,int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int findPerimeter(int i,int j,vector<vector<char>>& arr) {
    int perimeter = 0;
    for (int k = 0; k < 4; k++) {
        int x = i + di[k];
        int y = j + dj[k];
        perimeter += !safe(x,y) || arr[i][j] != arr[x][y];
    }
    return perimeter;
}

int bfs(int sx,int sy,vector<vector<bool>>& vis,vector<vector<char>>& arr) {
    queue<pair<int,int>> Q;
    Q.push({sx, sy});
    vis[sx][sy] = true;
    int area = 0;
    int perimeter = 0;
    while (!Q.empty()) {
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();
        area++;
        perimeter += findPerimeter(i,j,arr);

        for (int k = 0; k < 4; k++) {
            int x = i + di[k];
            int y = j + dj[k];
            if (safe(x,y) && !vis[x][y] && arr[x][y] == arr[i][j]) {
                vis[x][y] = true;
                Q.push({x,y});
            }
        }
    }
    return area * perimeter;
}

void solve() {
    vector<vector<char>> arr(n+1, vector<char>(n+1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) 
            cin >> arr[i][j];
    }
    vector<vector<bool>> vis(n+1, vector<bool>(n+1));
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (vis[i][j])
                continue;
            ans += bfs(i,j, vis, arr);
        }
    }
    cout << ans << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

