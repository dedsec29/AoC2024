// Find the top 10 dense grids, tree must in one of them
// I then translate the code to python, generate the top 10 dense images
// Density = number of connected components

#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<pair<int,int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

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

const int iterations = 1000;

vector<pair<int,int>> density;

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

void analyse(int n,int m,vector<pair<int,int>>& robots,int it) {
    int sz = robots.size();
    unordered_set<pair<int,int>, custom_hash> nodes;
    for (auto i: robots)
        nodes.insert(i);

    int dens = 0;

    for (int i = 0; i < sz; i++) {
        if (nodes.find(robots[i]) == nodes.end())
            continue;

        queue<pair<int,int>> Q;
        Q.push(robots[i]);
        nodes.erase(robots[i]);

        int cnt = 0;
        while (!Q.empty()) {
            int x = Q.front().first;
            int y = Q.front().second;
            Q.pop();
            cnt++;

            for (auto d: directions) {
                int u = d.first + x;
                int v = d.second + y;
                if (nodes.find({u,v}) != nodes.end()) {
                    nodes.erase({u,v});
                    Q.push({u,v});
                }
            }
        }
        dens = max(dens, cnt);
    }
    density.emplace_back(dens, it);
}

void print(int n,int m,vector<pair<int,int>>& robots) {
    vector<vector<char>> grid(n, vector<char>(m, '.'));
    for (auto i: robots) {
        grid[i.first][i.second] = '#';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << grid[i][j];
        cout << endl;
    }

    cout << endl << endl << endl;
}

int advance(int a,int b,int t,int m) {
    a = (a + m)%m; b = (b+m)%m; t = (t + m) % m;
    return ((a + (b * t % m)) % m + m) % m;
}

void advance(int n,int m,vector<pair<int,int>> robots,vector<pair<int,int>> velocity,int times) {
    int sz = robots.size();
    for (int i = 0; i < sz; i++) {
        robots[i].first = advance(robots[i].first, velocity[i].first, times, n);
        robots[i].second = advance(robots[i].second, velocity[i].second ,times, m);
    }
    print(n,m, robots);
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

        robots.emplace_back(x,y);
        velocity.emplace_back(u,v);
    }

    int sz = robots.size();
    vector<pair<int,int>> original(robots);

    for (int t = 0; t < iterations; t++) {
        for (int i = 0; i < sz; i++) {
            robots[i].first = advance(robots[i].first, velocity[i].first, 1, n);
            robots[i].second = advance(robots[i].second, velocity[i].second, 1, m);
        }
        analyse(n,m, robots, t+1);
    }

    sort(density.begin(), density.end(), greater<pair<int,int>>());

    for (int k = 0; k < min(iterations, (long long)density.size()); k++) {
        cout << "This is iteration number " << density[k].second << " with density = " << density[k].first << endl;
        advance(n,m, original, velocity, density[k].second);
    }
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
