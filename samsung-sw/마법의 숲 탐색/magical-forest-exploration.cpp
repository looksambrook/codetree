#include <iostream>
#include <queue>

using namespace std;

struct Info
{
    int r;
    int c;
    int d;
};
int R, C, K, tc;
int grid[74][71];
Info curr[1001];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

void init() {
    for (int i = 0; i < R + 3; ++i) {
        for (int j = 0; j < C; ++j) {
            grid[i][j] = 0;
        }
    }
}

bool is_range(int x, int y) {
    return x >= 0 && x < R+3
        && y >= 0 && y < C;
}

void moving_down() {    //false면 grid저장 X
    int tmp_r = curr[tc].r;
    while (true) {
        if (!is_range(tmp_r + 2, curr[tc].c) || grid[tmp_r + 2][curr[tc].c] != 0)break;
        if (!is_range(tmp_r + 1, curr[tc].c - 1) || grid[tmp_r + 1][curr[tc].c - 1] != 0) break;
        if (!is_range(tmp_r + 1, curr[tc].c + 1) || grid[tmp_r + 1][curr[tc].c + 1] != 0) break;
        tmp_r++;
    }
    curr[tc].r = tmp_r;
}

bool moving_left() {
    int tmp_r = curr[tc].r;
    int tmp_c = curr[tc].c;
    if (!is_range(tmp_r - 1, tmp_c - 1) || grid[tmp_r - 1][tmp_c - 1] != 0)return false;
    if (!is_range(tmp_r, tmp_c - 2) || grid[tmp_r][tmp_c - 2] != 0)return false;
    if (!is_range(tmp_r + 1, tmp_c - 1) || grid[tmp_r + 1][tmp_c - 1] != 0)return false;
    curr[tc].c -= 1;
    moving_down();
    if (tmp_r == curr[tc].r) {
        curr[tc].c += 1;
        return false;
    }
    curr[tc].d = (curr[tc].d + 3) % 4;
    return true;
}

bool moving_right() {
    int tmp_r = curr[tc].r;
    int tmp_c = curr[tc].c;
    if (!is_range(tmp_r - 1, tmp_c + 1) || grid[tmp_r - 1][tmp_c + 1] != 0)return false;
    if (!is_range(tmp_r, tmp_c + 2) || grid[tmp_r][tmp_c + 2] != 0)return false;
    if (!is_range(tmp_r + 1, tmp_c + 1) || grid[tmp_r + 1][tmp_c + 1] != 0)return false;
    curr[tc].c += 1;
    moving_down();
    if (tmp_r == curr[tc].r) {
        curr[tc].c -= 1;
        return false;
    }
    curr[tc].d = (curr[tc].d + 1) % 4;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> R >> C >> K;

    int result = 0;
    init();
    for (tc = 1; tc <= K; ++tc) {
        int c, d;
        cin >> c >> d;
        curr[tc] = { 1,c - 1,d };
        bool visited[74][71] = { false, };
        while (true) {
            if (visited[curr[tc].r][curr[tc].c])break;
            visited[curr[tc].r][curr[tc].c] = true;
            moving_down();
            if (moving_left())continue;
            if (moving_right())continue;
            break;
        }
        if (curr[tc].r <= 3) {
            init();
            continue;
        }
        for (int d = 0; d < 4; ++d)grid[curr[tc].r + dx[d]][curr[tc].c + dy[d]] = tc;
        grid[curr[tc].r][curr[tc].c] = tc;

        int cur = tc;
        int ans = curr[cur].r;
        queue<int> q;
        q.push(cur);
        bool is_visited[1001] = { false };
        is_visited[cur] = true;
        while (!q.empty()) {
            cur = q.front();
            q.pop();

            int cx = curr[cur].r + dx[curr[cur].d];
            int cy = curr[cur].c + dy[curr[cur].d];
            ans = ans < curr[cur].r ? curr[cur].r : ans;
            if (ans == R + 2)break;
            for (int d = 0; d < 4; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (is_range(nx, ny) && is_visited[grid[nx][ny]] == false && grid[nx][ny] != 0) {
                    q.push(grid[nx][ny]);
                    is_visited[grid[nx][ny]] = true;
                }
            }
        }
        result += ans-1;
    }
    cout << result;

    return 0;
}