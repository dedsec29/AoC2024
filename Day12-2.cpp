#include <bits/stdc++.h>
using namespace std;
#define int long long

const int n = 140;

vector<int> di = {0, -1, 0, 1};
vector<int> dj = {-1, 0, 1, 0};
vector<char> directions = {'L', 'U', 'R', 'D'};

bool safe(int x,int y) {
    return 1 <= x && x <= n && 1 <= y && y <= n;
}

int checkWest(int sx,int sy,vector<vector<char>>& arr,set<pair<int,int>>& processed) {
    if (processed.find({sx, sy}) != processed.end())
        return 0;
    if (safe(sx, sy-1) && arr[sx][sy-1] == arr[sx][sy])
        return 0;
    int i = sx;
    //cout << "W ";
    while (i <= n && !(safe(i, sy-1) && arr[i][sy-1] == arr[sx][sy]) && arr[i][sy] == arr[sx][sy]) {
        processed.insert({i, sy});
        //cout << i << " " << sy << ", ";
        i++;
    }
    //cout << endl;
    return 1;
}

int checkEast(int sx,int sy,vector<vector<char>>& arr,set<pair<int,int>>& processed) {
    if (processed.find({sx, sy}) != processed.end())
        return 0;
    if (safe(sx, sy+1) && arr[sx][sy+1] == arr[sx][sy])
        return 0;
    int i = sx;
    //cout << "E ";
    while (i <= n && !(safe(i, sy+1) && arr[i][sy+1] == arr[sx][sy]) && arr[i][sy] == arr[sx][sy]) {
        processed.insert({i, sy});
        //cout << i << " " << sy << ", ";
        i++;
    }
    //cout << endl;
    return 1;
}

int checkSouth(int sx,int sy,vector<vector<char>>& arr,set<pair<int,int>>& processed) {
    if (processed.find({sx, sy}) != processed.end())
        return 0;
    if (safe(sx+1, sy) && arr[sx+1][sy] == arr[sx][sy])
        return 0;
    int i = sy;
    //cout << "S ";
    while (i <= n && !(safe(sx+1, i) && arr[sx+1][i] == arr[sx][sy]) && arr[sx][i] == arr[sx][sy]) {
        processed.insert({sx, i});
        //cout << sx << " " << i << ", ";
        i++;
    }
    //cout << endl;
    return 1;
}

int checkNorth(int sx,int sy,vector<vector<char>>& arr,set<pair<int,int>>& processed) {
    if (processed.find({sx, sy}) != processed.end())
        return 0;
    if (safe(sx-1, sy) && arr[sx-1][sy] == arr[sx][sy])
        return 0;
    int i = sy;
    //cout << "N ";
    while (i <= n && !(safe(sx-1, i) && arr[sx-1][i] == arr[sx][sy]) && arr[sx][i] == arr[sx][sy]) {
        processed.insert({sx, i});
        //cout << sx << " " << i << ", ";
        i++;
    }
    //cout << endl;
    return 1;
}

int bfs(int sx,int sy,vector<vector<bool>>& vis,vector<vector<char>>& arr) {
    set<pair<int,int>> east, west, south, north;  

    queue<pair<int,int>> Q;
    Q.push({sx, sy});
    vis[sx][sy] = true;
    int area = 0;
    int perimeter = 0;
    unordered_set<int> rows, columns;

    vector<pair<int,int>> nodes;

    while (!Q.empty()) {
        nodes.emplace_back(Q.front());
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();
        area++;

        for (int k = 0; k < 4; k++) {
            int x = i + di[k];
            int y = j + dj[k];
            if (safe(x,y) && !vis[x][y] && arr[x][y] == arr[i][j]) {
                vis[x][y] = true;
                Q.push({x,y});
            }
        }
    }

    sort(nodes.begin(), nodes.end());

    for (auto node: nodes) {
        int i = node.first;
        int j = node.second;
        perimeter += checkEast(i,j, arr, east);
        perimeter += checkWest(i,j, arr, west);
        perimeter += checkNorth(i,j, arr, north);
        perimeter += checkSouth(i,j, arr, south);
    }

    //cout << arr[sx][sy] << " " << area << " " << perimeter << endl << endl;
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

