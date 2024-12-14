#include <bits/stdc++.h>
using namespace std;
#define int long long

const int iterations = 100;

void readInfo(string& s,int& x,int& y) {
    s.erase(s.begin(), s.begin() + 2);
    stringstream ss(s);
    string num;
    vector<int> arr;
    while (getline(ss, num, ',')) 
        arr.push_back(stoi(num));
    y = arr[0];
    x = arr[1];
}

void solve() {
    int m = 101;
    int n = 103;
    vector<pair<int,int>> robots;
    vector<pair<int,int>> velocity;

    string line;
    while (getline(cin, line)) {
        vector<string> words;
        stringstream ss(line);
        string word;
        while (getline(ss, word, ' '))
            words.emplace_back(word);

        int x,y,u,v;
        readInfo(words[0], x,y);
        readInfo(words[1], u,v);

        // cout << x%n << " " << y << " " << u << " " << v << endl;

        u %= n;
        v %= m;
        if (u < 0) u += n;
        if (v < 0) v += m;
        robots.emplace_back(x,y);
        velocity.emplace_back(u,v);
    }

    int sz = robots.size();
    for (int i = 0; i < sz; i++) {
        robots[i].first = (robots[i].first + (iterations * velocity[i].first) % n) % n;
        robots[i].second = (robots[i].second + (iterations * velocity[i].second) % m) % m;
    }

    vector<int> quadrants(4);  
    for (auto i: robots) {
        // cout << i.first << " " << i.second << endl;
        if (i.first == n/2 || i.second == m/2) 
            continue;
        if (i.first < n/2 && i.second < m/2)
            quadrants[0]++;
        else if (i.first < n/2 && i.second > m/2)
            quadrants[1]++;
        else if (i.first > n/2 && i.second < m/2)
            quadrants[2]++;
        else
            quadrants[3]++;
    }
    int ans = 1;
    for (int i: quadrants) {
        // cout << i << endl;
        ans *= i;
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

