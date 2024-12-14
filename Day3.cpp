#include <bits/stdc++.h>
using namespace std;
#define int long long

int total = 0;

int extractNumber(string& s,int i) {
    int n = s.size();
    if (!isdigit(s[i]))
        return -1;
    int j = i;
    int num = 0;
    while (j < n && isdigit(s[j])) {
        num = num * 10 + (s[j] - '0');
        j++;
    }
    // cout << i << " " << j-1 << " " << num << endl;
    return num;
}

bool perform = true;

void solve() {
    string s; 
    getline(cin, s);
    int n = s.size();
    int ans = 0;

    

    string doo = "do()";
    string dont = "don't()";
    string mul = "mul";

    for (int i = 0; i < n-1; i++) {
        if (s[i] == '-' && isdigit(s[i+1])) {
            cout << "neg present" << endl;
        }
    }

    for (int i = 0; i < n; i++) {
        if (s.substr(i, doo.size()) == doo) {
            perform = true;
            i += doo.size();
            i--;
            continue;
        }
        if (s.substr(i, dont.size()) == dont) {
            perform = false;
            i += dont.size();
            i--;
            continue;
        }

        if (s.substr(i, mul.size()) == mul) {
            i += mul.size();
            if (s[i] != '(')
                continue;

            int a = extractNumber(s, i+1);
            if (a == -1)
                continue;

            i += to_string(a).size() + 1;
            if (s[i] != ',')
                continue;

            int b = extractNumber(s, i+1);
            if (b == -1)
                continue;

            i += to_string(b).size() + 1;
            if (s[i] != ')')
                continue;
            if (perform) {
                ans += a*b;
            }
            // cout << a << " " << b << endl;
        }
    }

    total += ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 6;
    while (t--)
        solve();
    cout << total << endl;
    return 0;
}

