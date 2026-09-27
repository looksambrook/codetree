#include <iostream>

using namespace std;

int n;
int grid[200][200];
int r, c;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < n
        && y >= 0 && y < n;
}
void gravity() {
    int tmp[200][200] = { 0, };

    for (int j = 0; j < n; ++j) {
        int tcnt = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (grid[i][j] == 0)continue;
            tmp[tcnt++][j] = grid[i][j];
        }
    }

    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            grid[n - 1 - i][j] = tmp[i][j];
        }
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;
    r--, c--;

    // Please write your code here.
    int siz = grid[r][c];
    for (int d = 0; d < 4; ++d) {
        int nx = r;
        int ny = c;
        for (int i = 0; i < siz-1; ++i) {
            nx += dx[d];
            ny += dy[d];
            if (!is_range(nx, ny))break;
            grid[nx][ny] = 0;
        }
    }
    grid[r][c] = 0;
    gravity();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
