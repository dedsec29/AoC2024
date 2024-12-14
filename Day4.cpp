#include <bits/stdc++.h>
using namespace std;
#define int long long

int find_west(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && y >= 0) {
        if (grid[x][y] != word[ctr])
            return 0;
        y--;
        ctr++;
    }
    return ctr == sz;
}

int find_east(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && y < m) {
        if (grid[x][y] != word[ctr])
            return 0;
        y++;
        ctr++;
    }
    return ctr == sz;
}

int find_north(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && x >= 0) {
        if (grid[x][y] != word[ctr])
            return 0;
        x--;
        ctr++;
    }
    return ctr == sz;
}

int find_south(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && x < n) {
        if (grid[x][y] != word[ctr])
            return 0;
        x++;
        ctr++;
    }
    return ctr == sz;
}

int find_north_east(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && x >= 0 && y < m) {
        if (grid[x][y] != word[ctr])
            return 0;
        x--;
        y++;
        ctr++;
    }
    return ctr == sz;
}

int find_north_west(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && x >= 0 && y >= 0) {
        if (grid[x][y] != word[ctr])
            return 0;
        x--;
        y--;
        ctr++;
    }
    return ctr == sz;
}

int find_south_west(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && x < n && y >= 0) {
        if (grid[x][y] != word[ctr])
            return 0;
        x++;
        y--;
        ctr++;
    }
    return ctr == sz;
}

int find_south_east(vector<string>& grid,int i,int j,string word) {
    int sz = word.size();
    int n = grid.size();
    int m = grid[0].size();

    int x = i, y = j;
    int ctr = 0;
    while (ctr < sz && x < n && y < m) {
        if (grid[x][y] != word[ctr])
            return 0;
        x++;
        y++;
        ctr++;
    }
    return ctr == sz;
}

void solve() {
    vector<string> v = {"AM", "AM", "AS", "AS"};

    int n = 140;
    vector<string> grid(n);
    for (auto& i: grid) cin >> i;
    int m = grid[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (grid[i][j] == 'A') {
                bool good = false;
                for (int k = 0; k < 4; k++) {
                    int a1 = find_north_west(grid, i,j, v[k]);
                    int a2 = find_south_west(grid, i,j, v[(k+1)%4]);
                    int a3 = find_south_east(grid, i,j, v[(k+2)%4]);
                    int a4 = find_north_east(grid, i,j, v[(k+3)%4]);
                    good = good || (a1&a2&a3&a4);
                }
                ans += good;
            }
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

