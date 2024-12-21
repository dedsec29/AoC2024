#include <bits/stdc++.h>
using namespace std;
#define int long long

const int lines = 5;

class Pad {
protected:
    int n,m;
    vector<string> grid;
    pair<int,int> forbidden;
    map<pair<char,char>, vector<string>> paths;
    unordered_map<char, pair<int,int>> keyPosition;

    vector<int> di = {0, -1, 0, 1};
    vector<int> dj = {-1, 0, 1, 0};
    vector<char> button = {'<', '^', '>', 'v'};

    void computeKeyPositions() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) 
                keyPosition[grid[i][j]] = make_pair(i,j);
        }
    }

    bool safe(int i,int j) {
        return 0 <= i && i < n && 0 <= j && j < m && make_pair(i,j) != forbidden;
    }

    void precomputePaths() {
        for (int p = 0; p < n; p++) {
            for (int q = 0; q < m; q++) {
                if (forbidden == make_pair(p,q))
                    continue;

                // starting from character grid[i][j], find shortest paths to all
                bfs(p,q);
            }
        }
    }

    void bfs(int p,int q) {
        queue<char> Q;
        unordered_map<char, int> dist;

        char source = grid[p][q];
        Q.push(source);
        dist[source] = 0;
        paths[make_pair(source, source)] = {""};

        while (!Q.empty()) {
            char v = Q.front();
            Q.pop();
            int x = keyPosition[v].first;
            int y = keyPosition[v].second;

            for (int k = 0; k < 4; k++) {
                int i = x + di[k];
                int j = y + dj[k];

                if (safe(i,j)) {
                    if (dist.find(grid[i][j]) == dist.end()) {
                        Q.push(grid[i][j]);
                        dist[grid[i][j]] = dist[v] + 1;

                        for (const auto& parentPath: paths[make_pair(source, v)]) 
                            paths[make_pair(source, grid[i][j])].push_back(parentPath + button[k]);
                        
                    }
                    else if (dist[grid[i][j]] == dist[v] + 1) {
                        for (const auto& parentPath: paths[make_pair(source, v)]) 
                            paths[make_pair(source, grid[i][j])].push_back(parentPath + button[k]);
                    }
                }
            }
        }
    }

    void dfs(char last,int idx,string& curr,const string& input,vector<string>& combinations) {
        if (idx == input.size()) {
            combinations.emplace_back(curr);
            return;
        }

        int sz = curr.size();
        for (const auto& pairPath: paths[make_pair(last, input[idx])]) {
            curr += pairPath;
            curr += "A";
            dfs(input[idx], idx+1, curr, input, combinations);
            curr.resize(sz);
        }
    }

public:
    vector<string> func(const vector<string> input) {
        vector<string> possibilites;
        for (const auto& i: input) {
            vector<string> combinations;
            string curr = "";
            dfs('A', 0, curr, i, combinations);
            for (const auto& c: combinations)
                possibilites.emplace_back(c);
        }
        int mn = -1;
        vector<string> output;

        for (const auto& i: possibilites) {
            int sz = i.size();
            if (mn == -1 || mn > sz)
                mn = sz;
        }

        for (const auto& i: possibilites) {
            int sz = i.size();
            if (sz == mn)
                output.emplace_back(i);
        }
        return output;
    }
};

class NumPad : public Pad {    
public:
    NumPad() {
        n = 4, m = 3;
        forbidden = make_pair(3, 0);
        grid.push_back("789");
        grid.push_back("456");
        grid.push_back("123");
        grid.push_back("!0A");

        computeKeyPositions();
        precomputePaths();
    }
};

class DirectionPad : public Pad {
public:
    DirectionPad() {
        n = 2, m = 3;
        forbidden = make_pair(0, 0);
        grid.push_back("!^A");
        grid.push_back("<v>");

        computeKeyPositions();
        precomputePaths();
    }
};

void solve() {
    vector<string> codes(lines);
    for (int i = 0; i < lines; i++)
        cin >> codes[i];

    NumPad N;
    DirectionPad D;

    int ans = 0;
    for (auto i: codes) {
        vector<string> output = N.func({i});

        int mn = D.func(D.func(output))[0].size();

        string num = "";
        for (char c: i) {
            if (isdigit(c))
                num += c;
        }

        cout << mn << " " << stoll(num) << endl;
        ans += stoll(num) * mn;
    }

    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
