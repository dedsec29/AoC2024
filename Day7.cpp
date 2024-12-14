#include <bits/stdc++.h>
using namespace std;
#define int long long

int total = 0;

int applyOperation(int b,int a,char op) {
    if (op == '*')
        return a*b;
    if (op == '+')
        return a+b;

    // cout << a << " " << b << " now ";
    int x = b;
    while (x) {
        a *= 10ll;
        x /= 10;
    }
    // cout << b+a << endl;
    return a+b;
}

bool func(int i,vector<int>& nums,int lastOperand,char lastOperation,int target) {
    if (i == nums.size())
        return lastOperand == target;
    int curr = applyOperation(nums[i], lastOperand, lastOperation);
    return func(i+1, nums, curr, '+', target) || func(i+1, nums, curr, '*', target) || func(i+1, nums, curr, '|', target);
}

void solve() {
    string s;
    getline(cin, s);
    stringstream ss(s);
    vector<string> arr;
    string num;
    while (getline(ss, num, ' ')) 
        arr.push_back(num);

    // for (auto i: arr) cout << i << " ";
    // cout << endl;

    arr[0].pop_back();
    int target = stoll(arr[0]);

    vector<int> nums;
    for (int i = 1; i < arr.size(); i++)
        nums.push_back(stoll(arr[i]));

    if (func(0, nums, 0, '+', target) || func(0, nums, 1, '*', target))
        total += target;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t = 850;
    while (t--)
        solve();
    cout << total;
    return 0;
}

