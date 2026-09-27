#include <iostream>

using namespace std;

int n;
int grid[50][50];
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };

struct Board
{
    int tmp[50][50];
};

Board bomb(int r, int c) {
    Board board;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board.tmp[i][j] = grid[i][j];
        }
    }
    for (int d = 0; d < 4; ++d) {
        int nx = r;
        int ny = c;
        for (int i = 1; i < board.tmp[r][c]; ++i) {
            nx += dx[d];
            ny += dy[d];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
            board.tmp[nx][ny] = 0;
        }
    }
    board.tmp[r][c] = 0;
    for (int j = 0; j < n; ++j) {
        int temp[50] = { 0, };
        int tcnt = n - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (board.tmp[i][j] == 0)continue;
            temp[tcnt--] = board.tmp[i][j];
        }
        for (int i = 0; i < n; ++i) {
            board.tmp[i][j] = temp[i];
        }
    }
    return board;
}

int count_bomb(const Board& board) {
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board.tmp[i][j] == 0)continue;
            for (int d = 0; d < 2; ++d) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n)continue;
                if (board.tmp[i][j] == board.tmp[nx][ny])ans++;
            }
        }
    }
    return ans;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int c = count_bomb(bomb(i, j));
            if (c > ans)ans = c;
        }
    }
    cout << ans;

    return 0;
}
