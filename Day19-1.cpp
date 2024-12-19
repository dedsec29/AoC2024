#include <bits/stdc++.h>
using namespace std;
#define int long long

const static int al = 26;
const int numLines = 400;
vector<int> dp;

class Node {
public:
    
    bool isEnd;
    Node* edges[al];

    Node() {
        isEnd = false;
        for (int i = 0; i < al; i++)
            edges[i] = nullptr;
    }
};

class Trie {
public:

    Node root;

    void insert(const string& s) {
        Node* temp = &root;
        for (char c: s) {
            if (temp->edges[c-'a'] == nullptr)
                temp->edges[c-'a'] = new Node();
            temp = temp->edges[c-'a'];
        }
        temp->isEnd = true;
    }
};

int func(int pos,Trie& X,string& s) {
    if (pos == s.size())
        return true;
    
    if (dp[pos] != -1)
        return dp[pos];
    
    Node* temp = &(X.root);
    for (int i = pos; i < s.size(); i++) {
        // is s[pos..i] in trie?
        if (temp->edges[s[i]-'a'] == nullptr)
            return dp[pos] = 0;
        temp = temp->edges[s[i]-'a'];
        if (temp->isEnd && func(i+1, X, s) == 1)
            return dp[pos] = 1;
    }
    return dp[pos] = 0;
}

vector<string> readTowels() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    vector<string> ans;
    string s;
    while (getline(ss, s, ' '))  
        ans.emplace_back(s);
    
    int sz = ans.size();
    for (int i = 0; i < sz-1; i++)
        ans[i].pop_back();
    return ans;
}

void solve() {
    int ans = 0;
    vector<string> towels = readTowels();
    Trie X;
    for (const auto& i: towels)
        X.insert(i);
    for (int t = 0; t < numLines; t++) {
        string s; cin >> s;
        int n = s.size();
        dp = vector<int>(n, -1);
        if (func(0, X, s))      
            ans++;  
    }
    cout << ans ;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
