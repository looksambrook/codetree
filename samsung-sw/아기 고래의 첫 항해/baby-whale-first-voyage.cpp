#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Info {
    int x, y, dir, dist;
};
int N, r, c, dir;
int grid[51][51];
int K;
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int fdir[4][4] = { {0,2,3,1},{1,3,2,0},{2,1,0,3},{3,0,1,2} };
int sdir[] = { 2,1,3,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

bool fstep() {
    for (int d = 0; d < 4; ++d) {
        int nx = r + dx[fdir[dir][d]];
        int ny = c + dy[fdir[dir][d]];
        if (!is_range(nx, ny) || grid[nx][ny] != 0)continue;
        r = nx;
        c = ny;
        dir = fdir[dir][d];
        return true;
    }
    return false;
}

void sstep() {
    queue<Info> q;
    bool visited[51][51] = { false, };
    q.push({ r,c,dir,0 });
    visited[r][c] = true;
    Info ans = { N,N,-1,10000 };

    while (!q.empty()) {
        Info curr = q.front();
        q.pop();

        if (grid[curr.x][curr.y] == 0) {
            if (ans.dist > curr.dist || (ans.dist == curr.dist && (ans.x > curr.x || (ans.x == curr.x && ans.y > curr.y)))) {
                ans = curr;
            }
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = curr.x + dx[sdir[d]];
            int ny = curr.y + dy[sdir[d]];
            if (!is_range(nx, ny) || visited[nx][ny] || grid[nx][ny] < 0)continue;
            visited[nx][ny] = true;
            q.push({ nx,ny,sdir[d],curr.dist + 1 });
        }
    }
    r = ans.x;
    c = ans.y;
    dir = ans.dir;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> r >> c >> dir;
    r--, c--, dir--;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 0)K++;
            grid[i][j] *= -1;
        }
    }

    for (int test_case = 1; test_case <= K; ++test_case) {
        cout << r + 1 << " " << c + 1 << "\n";
        grid[r][c] = test_case;
        if (fstep())continue;
        sstep();
    }
    return 0;
}