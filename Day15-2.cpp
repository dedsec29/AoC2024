#include <bits/stdc++.h>
using namespace std;
#define int long long

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

const int N = 50;
const int M = 50 * 2;
const int numLines = 20;

char grid[N+1][M+1];
int rx = -1, ry = -1; 

void exploreHorizonalNeighbors(int i,int j,unordered_set<pair<int,int>, custom_hash>& vis,queue<pair<int,int>>& Q) {
    if (grid[i][j] == '[' && vis.find({i, j+1}) == vis.end()) {
        vis.insert({i, j+1});
        Q.push({i, j+1});
    }
    else if (grid[i][j] == ']' && vis.find({i,j-1}) == vis.end()) {
        vis.insert({i, j-1});
        Q.push({i, j-1});
    }
}

void moveRight() {
    // Need to find the first free cell to right
    int ptr = ry+1;
    while (ptr < M && (grid[rx][ptr] == '[' || grid[rx][ptr] == ']'))
        ptr++;

    // encountered wall
    if (grid[rx][ptr] == '#')
        return;

    // shift [ry..ptr-1] to right
    for (int j = ptr; j > ry; j--)
        grid[rx][j] = grid[rx][j-1];

    grid[rx][ry] = '.';
    ry++;
}

void moveLeft() {
    // Need to find the first free cell to left
    int ptr = ry-1;
    while (ptr > 1 && (grid[rx][ptr] == '[' || grid[rx][ptr] == ']'))
        ptr--;

    // encountered wall
    if (grid[rx][ptr] == '#')
        return;

    // shift [ptr+1..ry] to left
    for (int j = ptr; j < ry; j++)
        grid[rx][j] = grid[rx][j+1];

    grid[rx][ry] = '.';
    ry--;
}

void moveUp() {
    if (grid[rx-1][ry] == '#')
        return;
    if (grid[rx-1][ry] == '.') {
        grid[rx][ry] = '.';
        grid[rx-1][ry] = '@';
        rx--;
        return;
    }

    // Find all connected components in upward direction
    vector<pair<int,int>> boxes;
    unordered_set<pair<int,int>, custom_hash> vis;
    queue<pair<int,int>> Q;
    if (grid[rx-1][ry] == '[' || grid[rx-1][ry] == ']') {
        Q.push({rx-1, ry});
        vis.insert({rx-1, ry});
    }

    while (!Q.empty()) {
        boxes.emplace_back(Q.front());
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();

        exploreHorizonalNeighbors(i,j, vis, Q);

        // explore up
        if (grid[i-1][j] == '[' || grid[i-1][j] == ']') {
            Q.push({i-1, j});
            vis.insert({i-1, j});
        }

        // Can move none
        if (grid[i-1][j] == '#')
            return;
    }

    int sz = boxes.size();
    vector<char> original;

    for (auto i: boxes) {
        // cout << i.first << " " << i.second << endl;
        original.push_back(grid[i.first][i.second]);
        grid[i.first][i.second] = '.';
    }
    for (int i = 0; i < sz; i++) {
        grid[boxes[i].first-1][boxes[i].second] = original[i];
    }
    grid[rx][ry] = '.';
    grid[rx-1][ry] = '@';
    rx--;
}

void moveDown() {
    if (grid[rx+1][ry] == '#')
        return;
    if (grid[rx+1][ry] == '.') {
        grid[rx][ry] = '.';
        grid[rx+1][ry] = '@';
        rx++;
        return;
    }

    // Find all connected components in downwards direction
    vector<pair<int,int>> boxes;
    unordered_set<pair<int,int>, custom_hash> vis;
    queue<pair<int,int>> Q;
    if (grid[rx+1][ry] == '[' || grid[rx+1][ry] == ']') {
        Q.push({rx+1, ry});
        vis.insert({rx+1, ry});
    }

    while (!Q.empty()) {
        boxes.emplace_back(Q.front());
        int i = Q.front().first;
        int j = Q.front().second;
        Q.pop();

        exploreHorizonalNeighbors(i,j, vis, Q);

        // explore down
        if (grid[i+1][j] == '[' || grid[i+1][j] == ']') {
            Q.push({i+1, j});
            vis.insert({i+1, j});
        }

        // Can move none
        if (grid[i+1][j] == '#')
            return;
    }

    int sz = boxes.size();
    vector<char> original;

    for (auto i: boxes) {
        // cout << i.first << " " << i.second << endl;
        original.push_back(grid[i.first][i.second]);
        grid[i.first][i.second] = '.';
    }
    for (int i = 0; i < sz; i++) {
        grid[boxes[i].first+1][boxes[i].second] = original[i];
    }
    grid[rx][ry] = '.';
    grid[rx+1][ry] = '@';
    rx++;
}

void applyInstruction(char c) {
    if (c == '>')
        moveRight();
    else if (c == '<')
        moveLeft();
    else if (c == '^')
        moveUp();
    else
        moveDown();
}

void print() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

void solve() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j += 2) {
            char c; cin >> c;
            if (c == 'O') {
                grid[i][j] = '[';
                grid[i][j+1] = ']';
            }
            else if (c == '@') {
                grid[i][j] = c;
                grid[i][j+1] = '.';
            }
            else
                grid[i][j] = grid[i][j+1] = c;

            if (grid[i][j] == '@')
                rx = i, ry = j;
        }
    }

    cout << "Initial state: " << endl;
    print();

    string instructions = "";
    int times = numLines;
    while (times--) {
        string s; cin >> s;
        instructions += s;
    } 

    for (char c: instructions) {
        applyInstruction(c);
        // cout << "Instruction: " << c << endl;
        // print();
    }

    print();

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] == '[') {
                ans += (i-1) * 100ll + (j-1);
            }
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

