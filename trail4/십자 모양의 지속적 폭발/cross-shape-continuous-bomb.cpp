#include <iostream>

using namespace std;

int n, m;
int grid[200][200];
int bomb_cols[15];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < n
        && y >= 0 && y < n;
}

void bomb(int r, int c) {
    for (int d = 0; d < 4; ++d) {
        int nx = r;
        int ny = c;
        for (int j = 0; j < grid[r][c] - 1; ++j) {
            nx += dx[d];
            ny += dy[d];
            if (!is_range(nx, ny))break;
            grid[nx][ny] = 0;
        }
    }
    grid[r][c] = 0;
}

void gravity() {
    for (int j = 0; j < n; ++j) {
        int tmp[201] = { 0, };
        int tcnt = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (grid[i][j] == 0)continue;
            tmp[tcnt--] = grid[i][j];
        }
        for (int i = 0; i < n; ++i) {
            grid[i][j] = tmp[i];
        }
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < m; i++) {
        cin >> bomb_cols[i];
    }

    // Please write your code here.
    for (int i = 0; i < m; ++i) {
        int r = 0, c = bomb_cols[i] - 1;
        for (r = 0; r < n; ++r) {
            if (grid[r][c] != 0)break;
        }
        if (r == n)continue;

        bomb(r, c);
        gravity();
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}