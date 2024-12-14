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
    for (int i = n-1; i >= 0; i--) {
        if (arr[i] == -1)
            continue;
        // trying to allocate contiguous block ending at i
        int j = i;
        while (j >= 0 && arr[j] == arr[i])
            j--;
        j++;

        // j...i must be a contiguous block
        int block = i-j+1;

        for (int u = 0; u < j; u++) {
            if (arr[u] != -1) 
                continue;
            // What is the size of block of spaces starting at i?
            int v = u;
            while (v < j && arr[v] == arr[u])
                v++;
            v--;

            if (v-u+1 >= block) {
                // Can allocate here
                for (int p = u; p <= u+block-1; p++)
                    arr[p] = arr[i];
                // optionally deallocate [j...i]
                for (int p = j; p <= i; p++)
                    arr[p] = -1;

                break;
            }
            u = v;
        }

        i = j;
    }

    for (int i = 0; i < n; i++) {
        if (arr[i] != -1)
            ans += i * arr[i];
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

