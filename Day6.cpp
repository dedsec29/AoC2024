#include <bits/stdc++.h>
using namespace std;
#define int long long

void advance(int& i,int& j,char& direction,vector<vector<char>>& grid) {
    if (direction == 'U') {
        if (grid[i-1][j] == '#') 
            direction = 'R';
        else
            i--;
    }
    else if (direction == 'R') {
        if (grid[i][j+1] == '#')
            direction = 'D';
        else
            j++;
    }
    else if (direction == 'D') {
        if (grid[i+1][j] == '#')
            direction = 'L';
        else
            i++;
    }
    else {
        if (grid[i][j-1] == '#')
            direction = 'U';
        else
            j--;
    }
}

int func(char direction) {
    vector<char> v = {'U', 'R', 'D', 'L'};
    for (int k = 0; k < 4; k++) {
        if (v[k] == direction)
            return k;
    }
    return 0;
}

void solve() {
    int n = 130;
    int m = 130;
    int x,y;
    vector<vector<char>> grid(n+2, vector<char>(m+2, '!'));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '^') 
                x = i, y = j;
        }
    }

    int ans = 0;

    for (int sx = 1; sx <= n; sx++) {
        for (int sy = 1; sy <= m; sy++) {
            if (grid[sx][sy] == '.') {
                grid[sx][sy] = '#';

                vector<vector<vector<bool>>> vis(n+2, vector<vector<bool>>(m+2, vector<bool>(4)));

                char direction = 'U';
                int i = x, j = y;

                bool loop = false;

                while (i != 0 && i != n+1 && j != 0 && j != m+1) {
                    if (vis[i][j][func(direction)]) {
                        loop = true;
                        break;
                    }
                    vis[i][j][func(direction)] = true;
                    advance(i,j, direction, grid);
                }

                if (loop)
                    ans++;

                grid[sx][sy] = '.';
            }
        }
    }

    cout << ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
