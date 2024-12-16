#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 141;
const int turnCost = 1000;
vector<char> directions = {'L', 'U', 'R', 'D'};

const int inf =  N * N * turnCost + 5;
vector<int> di = {0, -1, 0, 1};
vector<int> dj = {-1, 0, 1, 0};

struct Node {
    int x,y;
    char direction;

    Node() {}

    Node(int x,int y,char d) {
        this->x = x;
        this->y = y;
        direction = d;
    }
};

int funcd(char c) {
    for (int i = 0; i < 4; i++) {
        if (c == directions[i])
            return i;
    }
    return -1;
}

struct CustomCompare {
    bool operator()(const pair<int,Node>& a,const pair<int,Node>& b) const {
        if (a.first != b.first) 
            return a.first < b.first;  
        if (a.second.x != b.second.x) 
            return a.second.x < b.second.x;  
        if (a.second.y != b.second.y) 
            return a.second.y < b.second.y;  
        return a.second.direction < b.second.direction;
    }
};

bool safe(int a,int b) {
    return 1 <= a && a <= N && 1 <= b && b <= N;
}

int getWeight(char a,char b) {
    return 1 + (a == b ? 0 : turnCost);
}

char opposite(char c) {
    if (c == 'U')
        return 'D';
    else if (c == 'D')
        return 'U';
    else if (c == 'L')
        return 'R';
    else
        return 'L';
}

void print(Node v) {
    cout << v.x << " " << v.y << " " << v.direction << endl;
}

void solve() {
    pair<int,int> source;
    pair<int,int> destination;

    vector<vector<char>> grid(N+1, vector<char>(N+1));

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S')
                source = {i,j};
            else if (grid[i][j] == 'E')
                destination = {i,j};
        }
    }

    set<pair<int, Node>, CustomCompare> s;
    vector<vector<vector<int>>> dist(N+1, vector<vector<int>>(N+1, vector<int>(4, inf)));
    dist[source.first][source.second][funcd('R')] = 0;
    s.insert({0, Node(source.first, source.second, 'R')});


    while (!s.empty()) {
        Node v = s.begin()->second;
        // cout << v.x << " " << v.y << " " << v.direction << " " << dist[v.x][v.y][funcd(v.direction)] << endl;
        s.erase(s.begin());

        for (int k = 0; k < 4; k++) {
            if (directions[k] == opposite(v.direction))
                continue;

            int x = v.x + di[k];
            int y = v.y + dj[k];
            char d = directions[k];
            Node to = Node(x,y,d);

            if (safe(x,y) && grid[x][y] != '#') {
                int wt = getWeight(v.direction, to.direction);
                // cout << "to "; print(to);

                if (dist[v.x][v.y][funcd(v.direction)] + wt < dist[to.x][to.y][funcd(to.direction)]) {
                    s.erase({dist[to.x][to.y][funcd(to.direction)], to});
                    dist[to.x][to.y][funcd(to.direction)] = dist[v.x][v.y][funcd(v.direction)] + wt;
                    s.insert({dist[to.x][to.y][funcd(to.direction)], to});
                }
            }
        }
    }

    int ans = inf;
    for (int k = 0; k < 4; k++) {
        ans = min(dist[destination.first][destination.second][k], ans);
    }

    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

