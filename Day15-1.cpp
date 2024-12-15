#include <bits/stdc++.h>
using namespace std;
#define int long long

const int N = 50;
const int M = 50;
const int numLines = 20;

char grid[N+1][M+1];
int rx = -1, ry = -1; 

void moveRight() {
    // Need to find the first free cell to right
    int ptr = ry+1;
    while (ptr < M && grid[rx][ptr] == 'O')
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
    while (ptr > 1 && grid[rx][ptr] == 'O')
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
    // Need to find the first free cell Up
    int ptr = rx-1;
    while (ptr > 1 && grid[ptr][ry] == 'O')
        ptr--;

    // encountered wall
    if (grid[ptr][ry] == '#')
        return;

    // Shift [ptr+1..rx] up
    for (int j = ptr; j < rx; j++)
        grid[j][ry] = grid[j+1][ry];

    grid[rx][ry] = '.';
    rx--;
}

void moveDown() {
    // Need to find the first free cell down
    int ptr = rx+1;
    while (ptr < N && grid[ptr][ry] == 'O')
        ptr++;

    // encountered wall
    if (grid[ptr][ry] == '#')
        return;

    // shift [rx..ptr-1] down
    for (int j = ptr; j > rx; j--)
        grid[j][ry] = grid[j-1][ry];

    grid[rx][ry] = '.';
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
        for (int j = 1; j <= M; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '@')
                rx = i, ry = j;
        }
    }

    string instructions = "";
    int times = numLines;
    while (times--) {
        string s; cin >> s;
        instructions += s;
    } 

    for (char c: instructions) {
        applyInstruction(c);
        cout << "Instruction: " << c << endl;
        print();
    }

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] == 'O') {
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

