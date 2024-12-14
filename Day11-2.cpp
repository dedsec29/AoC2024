#include <bits/stdc++.h>
using namespace std;
#define int long long

const int siz = 2e6;
const int depth = 75;

vector<vector<int>> dp(siz+1, vector<int>(depth+1, -1));

int func(int num,int d) {
    if (d == 0)
        return 1;

    if (num <= siz && dp[num][d] != -1)
        return dp[num][d];

    if (num == 0)
        return func(1, d-1);

    string s = to_string(num);
    int n = s.size();
    if (n&1) {
        int ans = func(num * 2024ll, d-1);
        if (num <= siz)
            dp[num][d] = ans;
        return ans;
    }

    int a = stoll(s.substr(0, n/2));
    int b = stoll(s.substr(n/2, n/2));
    int ans = func(a, d-1) + func(b, d-1);

    if (num <= siz)
        dp[num][d] = ans;

    return ans;
}

void solve() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string num;

    int ans = 0;
    while (getline(ss, num, ' ')) {
        ans += func(stoll(num), depth);
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

