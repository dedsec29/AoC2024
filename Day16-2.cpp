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

struct CustomLookup {
    bool operator()(const Node& a,const Node& b) const {
        if (a.x != b.x) 
            return a.x < b.x;  
        if (a.y != b.y) 
            return a.y < b.y;  
        return a.direction < b.direction;
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

void dfs(Node v,set<pair<int,int>>& tiles, set<Node, CustomLookup>& vis, map<Node, vector<Node>, CustomLookup>& parent) {
    vis.insert(v);
    tiles.insert({v.x, v.y});

    auto p = parent[v];
    for (auto i: p) {
        if (vis.find(i) == vis.end()) {
            dfs(i, tiles, vis, parent);
        }
    }
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
    map<Node, vector<Node>, CustomLookup> parent;
    dist[source.first][source.second][funcd('R')] = 0;
    s.insert({0, Node(source.first, source.second, 'R')});
    parent[Node(source.first, source.second, 'R')] = {Node(source.first, source.second, 'R')};

    while (!s.empty()) {
        Node v = s.begin()->second;
        s.erase(s.begin());

        // print(v);

        for (int k = 0; k < 4; k++) {
            if (directions[k] == opposite(v.direction))
                continue;

            int x = v.x + di[k];
            int y = v.y + dj[k];
            char d = directions[k];
            Node to = Node(x,y,d);

            if (safe(x,y) && grid[x][y] != '#') {
                int wt = getWeight(v.direction, to.direction);

                if (dist[v.x][v.y][funcd(v.direction)] + wt < dist[to.x][to.y][funcd(to.direction)]) {
                    s.erase({dist[to.x][to.y][funcd(to.direction)], to});
                    dist[to.x][to.y][funcd(to.direction)] = dist[v.x][v.y][funcd(v.direction)] + wt;
                    s.insert({dist[to.x][to.y][funcd(to.direction)], to});
                    
                    parent[to] = {v};
                }
                else if (dist[v.x][v.y][funcd(v.direction)] + wt == dist[to.x][to.y][funcd(to.direction)]) {
                    parent[to].emplace_back(v);
                }
            }
        }
    }

    int ans = inf;
    for (int k = 0; k < 4; k++) {
        ans = min(dist[destination.first][destination.second][k], ans);
    }

    set<Node, CustomLookup> vis;
    set<pair<int,int>> tiles;
    for (char c: directions) {
        if (ans == dist[destination.first][destination.second][funcd(c)]) {
            dfs(Node(destination.first, destination.second, c), tiles, vis, parent);
        }
    }
    cout << tiles.size();
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

