#include <bits/stdc++.h>
using namespace std;
#define int long long

bool safe(int i,int j,int n) {
    return 1 <= i && i <= n && 1 <= j && j <= n;
}

void solve() {
    int n = 50;
    unordered_map<char, vector<pair<int,int>>> coordinates;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c; cin >> c;
            if (c != '.')
                coordinates[c].push_back({i,j});
        }
    }

    vector<vector<bool>> vis(n+1, vector<bool>(n+1));

    for (auto it: coordinates) {
        int sz = it.second.size();
        for (int a = 0; a < sz; a++) {
            for (int b = a+1; b < sz; b++) {
                int i = it.second[a].first, j = it.second[a].second;
                int u = it.second[b].first, v = it.second[b].second;
                // cout << i << ", " << j << " ; " << u << ", " << v << endl;

                if (j < v) {
                    int p = u + u-i;
                    int q = v + v-j;
                    if (safe(p,q, n))
                        vis[p][q] = true;

                    // cout << p << " " << q << endl;

                    p = i - (u-i);
                    q = j - (v-j);
                    if (safe(p,q, n))
                        vis[p][q] = true;

                    // cout << p << " " << q << endl;
                }
                else {
                    int p = u + u-i;
                    int q = v - (j-v);
                    if (safe(p,q, n))
                        vis[p][q] = true;

                    p = i - (u-i);
                    q = j + (j-v);
                    if (safe(p,q, n))
                        vis[p][q] = true;
                }
            }
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (vis[i][j]) {
                ans++;
                cout << "#";
            }
            else cout << ".";
        }
        cout << endl;
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
