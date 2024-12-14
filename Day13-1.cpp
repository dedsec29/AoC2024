#include <bits/stdc++.h>
using namespace std;
#define int long long // 19707

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(pair<uint64_t,uint64_t> x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM)^(splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

unordered_map<pair<int,int>, int, custom_hash> dp;

void readButton(int& a,int& b) {
    string tool; cin >> tool; cin >> tool; cin >> tool;
    tool.pop_back();
    tool.erase(tool.begin(), tool.begin()+2);
    a = stoll(tool);

    cin >> tool;
    tool.erase(tool.begin(), tool.begin()+2);
    b = stoll(tool);        
}

void readLocation(int& x,int& y) {
    string tool; cin >> tool; cin >> tool;
    tool.erase(tool.begin(), tool.begin()+2);
    tool.pop_back();
    x = stoll(tool);
    
    cin >> tool;
    tool.erase(tool.begin(), tool.begin()+2);
    y = stoll(tool);    
}

int func(int x,int y,int a,int b,int u,int v) {
    if (x < 0 || y < 0)
        return -1;
    if (x == 0 && y == 0)
        return 0;
    if (dp.find({x,y}) != dp.end())
        return dp[{x,y}];
    int option1 = func(x-a, y-b, a,b, u,v);
    int option2 = func(x-u, y-v, a,b, u,v);

    int ans = -1;
    if (option1 == -1 && option2 == -1)
        ans = -1;
    else if (option1 == -1)
        ans = 1 + option2;
    else if (option2 == -1)
        ans = 3 + option1;
    else
        ans = min(option1 + 3, option2 + 1);
    return dp[{x,y}] = ans;
}

void solve() {
    int n = 320;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        int a,b,u,v,x,y;
        readButton(a,b);
        readButton(u,v);
        readLocation(x,y);

        int q = func(x,y, a,b, u,v);
        // cout << q << "\n";
        if (q != -1)
            ans += q;

        dp.clear();
    }
    cout << ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

