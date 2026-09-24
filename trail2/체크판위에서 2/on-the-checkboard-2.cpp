#include <iostream>

using namespace std;

int R, C;
int ans = 0;
char grid[15][15];

void move(int cnt, int r, int c) {
    if (cnt == 3) {
        if(r==R-1&&c==C-1)
            ans++;
        return;
    }
    for (int i = r + 1; i < R; ++i) {
        for (int j = c + 1; j < C; ++j) {
            if (grid[r][c] != grid[i][j])move(cnt + 1, i, j);
        }
    }
}

int main() {
    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    move(0, 0, 0);
    cout << ans;

    return 0;
}