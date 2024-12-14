#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    string s; cin >> s;
    int n = s.size();
    int ans = 0;
    vector<int> arr;
    for (int i = 0, id = 0; i < n; i++, id += (i&1)) {
        int times = s[i] - '0';
        int c = (i&1) ? -1 : id;
        while (times--)
            arr.push_back(c);
    }

    n = arr.size();
    int l = 0, r = n-1;
    while (l <= r) {
        if (arr[l] != -1) {
            ans += l * arr[l];
            l++;
        }
        else if (arr[r] == -1)
            r--;
        else if (arr[l] == -1) {
            ans += l * arr[r];
            l++;
            r--;
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

