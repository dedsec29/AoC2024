#include <bits/stdc++.h>
using namespace std;
#define int long long

struct Node {
    int val;
    Node* next;

    Node() {
        val = -1;
        next = nullptr;
    }

    Node(int val) {
        this->val = val;
        next = nullptr;
    }
};

void solve() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    string num;

    Node* head = new Node();
    {
        Node* temp = head;

        while (getline(ss, num, ' ')) {
            temp->next = new Node(stoll(num));
            temp = temp->next;
        }
    }

        int ct = 0;


    for (int i = 1; i <= 40; i++) {
        Node* temp = head->next;
        Node* prev = head;

        while (temp != nullptr) {
            int curr = temp->val;
            if (curr == 0)
                temp->val = 1;
            else {
                string s = to_string(curr);
                int n = s.size();
                if (n&1)
                    temp->val *= 2024ll;
                else {
                    Node* left = new Node(stoll(s.substr(0, n/2)));
                    temp->val = stoll(s.substr(n/2, n/2));
                    
                    prev->next = left;
                    left->next = temp;
                }
            }

            prev = temp;
            temp = temp->next;
        }

        Node* p = head->next;
        while (p) {
            cout << p->val << " ";
            ct = max(ct, (long long)to_string(p->val).size());
            p = p->next;
        }
        cout << endl;
    }

    cout << endl << ct << endl;

    int ans = 0;
    Node* temp = head->next;
    while (temp) {
        ans++;
        temp = temp->next;
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

