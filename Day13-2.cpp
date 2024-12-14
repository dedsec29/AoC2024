#include <bits/stdc++.h>
using namespace std;
#define int long long 

const int ADD = 10000000000000ll;


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
    x += ADD;
    y += ADD;
    // if (x % gcd(a,u) != 0 || y % gcd(b,v) != 0) 
    //     return -1;
    if (abs(b*x - a*y) % abs(b*u - a*v))
        return -1;

    if (b*u - a*v == 0) {
        cout << "bruhhhhh" << endl;
        return -1;
    }

    int q = (b*x - a*y) / (b*u - a*v);
    int p = (x - q*u) / a;

    // cout << p << " " << q << ": " << p*a + q*u << " " << p*b + q*v << endl;
    return 3ll*p + q;
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
        if (q != -1)
            ans += q;
    }
    cout << ans << "\n";
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

