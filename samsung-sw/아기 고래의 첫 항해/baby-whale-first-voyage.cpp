#include <iostream>
#include <queue>

using namespace std;

bool board[50][50] = { false, };
bool visited[50][50] = { false, };
int N, r, c, d;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

struct Info
{
    int r;
    int c;
    int d;

    bool operator<(const Info& other) const{
        if (r != other.r) return r > other.r;
        return c > other.c;
    }
};

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N
        && !board[x][y];
}

bool first_step() {
    int df[4][4] = { 0,2,3,1,1,3,2,0,2,1,0,3,3,0,1,2 };
    for (int i = 0; i < 4; ++i) {
        int nd = df[d][i];
        int nx = r + dx[nd];
        int ny = c + dy[nd];
        if (is_range(nx, ny) && !visited[nx][ny] && !board[nx][ny]) {
            r = nx, c = ny, d = nd;
            visited[r][c] = true;
            return true;
        }
    }
    return false;
}

bool second_step() {
    int ds[4] = { 2,1,3,0 };
    queue<Info> q;
    priority_queue<Info> ans;
    q.push({ r,c,d });
    bool selected[50][50] = { false, };
    selected[r][c] = true;

    while (ans.empty()) {
        int cnt = q.size();
        if (cnt == 0)return false;
        for (int j = 0; j < cnt; ++j) {
            int cx = q.front().r;
            int cy = q.front().c;
            int cd = q.front().d;
            q.pop();

            for (int i = 0; i < 4; ++i) {
                int nd = ds[i];
                int nx = cx + dx[nd];
                int ny = cy + dy[nd];
                if (is_range(nx, ny) && !selected[nx][ny] && !board[nx][ny]) {
                    selected[nx][ny] = true;
                    if (visited[nx][ny])q.push({ nx,ny,nd });
                    else {
                        ans.push({ nx,ny,nd });
                    }
                }
            }
        }
    }

    r = ans.top().r;
    c = ans.top().c;
    d = ans.top().d;
    visited[r][c] = true;
    return true;
}

int main() {
    // Please write your code here.
    cin >> N >> r >> c >> d;
    r -= 1, c -= 1, d -= 1;
    visited[r][c] = true;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> board[i][j];
        }
    }

    while (true) {
        cout << r + 1 << " " << c + 1 << "\n";
        if (first_step())continue;
        if (second_step())continue;
        break;
    }

    return 0;
}