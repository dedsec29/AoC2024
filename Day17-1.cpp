#include <bits/stdc++.h>
using namespace std;
#define int long long

int A = 0, B = 0, C = 0;

vector<int> answers;

int poww(int a,int b) {
    int res = 1;
    while (b) {
        if (b&1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

void readRegister(int& x) {
    string s; cin >> s; cin >> s; cin >> s;
    x = stoll(s);
}

int getComboOperand(int x) {
    if (0 <= x && x <= 3)
        return x;
    else if (x == 4)
        return A;
    else if (x == 5)
        return B;
    else if (x == 6)
        return C;
    return -1;
}

void perform(int opcode,int operand,int& ptr) {
    // cout << opcode << " " << operand << " " << ptr << " " << A << " " << B << " " << C << endl;
    if (opcode == 0) {
        A = A / poww(2, getComboOperand(operand));
        ++ptr;
    }
    else if (opcode == 1) {
        B = B ^ operand;
        ++ptr;
    }
    else if (opcode == 2) {
        B = getComboOperand(operand) % 8;
        ++ptr;
    }
    else if (opcode == 3) {
        if (A == 0) {
            ++ptr;
            return;
        }
        --ptr;
        ptr = operand;
    }
    else if (opcode == 4) {
        B = B ^ C;
        ++ptr;
    }
    else if (opcode == 5) {
        // cout << getComboOperand(operand) << " bruh"<< endl;
        answers.push_back(getComboOperand(operand) % 8);
        ++ptr;
    }
    else if (opcode == 6) {
        B = A / poww(2, getComboOperand(operand));
        ++ptr;
    }
    else {
        C = A / poww(2, getComboOperand(operand));
        ++ptr;
    }
}

void solve() {
    readRegister(A);
    readRegister(B);
    readRegister(C);
    string program; cin >> program; cin >> program;
    stringstream ss(program);
    string dummy;
    int ctr = 0;
    vector<int> arr;
    while (getline(ss, dummy, ','))  
        arr.push_back(stoll(dummy));

    int n = arr.size();
    int ptr = 0;
    while (ptr+1 < n) {
        int opcode = arr[ptr];
        ++ptr;
        int operand = arr[ptr];
        perform(opcode, operand, ptr);
    }

    int sz = answers.size();
    for (int i = 0; i < sz-1; i++)
        cout << answers[i] << ",";
    if (sz > 0)
        cout << answers.back() << endl;

    // cout << A << " " << B << " " << C << endl;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}

