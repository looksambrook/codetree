#include <iostream>
#include <queue>

using namespace std;

struct Grid {
    int cnt;
    queue<int> dir;
    queue<int> dead;
};
struct Info {
    int cnt;
    queue<int> dir;
};

struct Data {
    int x[3];
    int y[3];
};

Grid grid[4][4];
Info egg_grid[4][4];
int M, T;
int px, py;
int test_case;
int dx[] = { -1,-1,0,1,1,1,0,-1 };
int dy[] = { 0,-1,-1,-1,0,1,1,1 };

bool is_range(int x, int y) {
    return x >= 0 && x < 4
        && y >= 0 && y < 4;
}

void make_egg() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int cnt = 0; cnt < grid[i][j].cnt; ++cnt) {
                int tmp_d = grid[i][j].dir.front();
                grid[i][j].dir.pop();
                egg_grid[i][j].dir.push(tmp_d);
                grid[i][j].dir.push(tmp_d);
            }
            egg_grid[i][j].cnt = grid[i][j].cnt;
        }
    }
}

void mon_moving() {
    queue<int> temp[4][4];
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int cnt = 0; cnt < grid[i][j].cnt; ++cnt) {
                int cx = i, cy = j;
                int tmp_d = grid[i][j].dir.front();
                grid[i][j].dir.pop();
                for (int d = 0; d < 8; ++d) {
                    int nx = i + dx[(tmp_d + d) % 8];
                    int ny = j + dy[(tmp_d + d) % 8];
                    if (!is_range(nx, ny) || !grid[nx][ny].dead.empty() || (nx == px && ny == py))continue;
                    tmp_d = (tmp_d + d) % 8;
                    cx = nx, cy = ny;
                    break;
                }
                temp[cx][cy].push(tmp_d);
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            grid[i][j].cnt = temp[i][j].size();
            for (int cnt = 0; cnt < grid[i][j].cnt; ++cnt) {
                grid[i][j].dir.push(temp[i][j].front());
                temp[i][j].pop();
            }
        }
    }
}

int tmon = 0;
int tx, ty;
bool visit[4][4] = { false, };
Data ans_parent = { 0, };
void DFS(int x, int y, int cnt, int mon, Data parent) {
    if (cnt == 3) {
        if (tmon < mon) {
            tmon = mon;
            tx = x, ty = y;
            for (int i = 0; i < 3; ++i) ans_parent = parent;
        }
        return;
    }

    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[2 * d];
        int ny = y + dy[2 * d];
        if (!is_range(nx, ny))continue;
        parent.x[cnt] = nx;
        parent.y[cnt] = ny;
        if (visit[nx][ny]) DFS(nx, ny, cnt + 1, mon, parent);
        else {
            visit[nx][ny] = true;
            DFS(nx, ny, cnt + 1, mon + grid[nx][ny].cnt, parent);
            visit[nx][ny] = false;
        }
    }
}

void pa_moving() {
    tmon = -1;
    DFS(px, py, 0, 0, Data{});

    px = tx, py = ty;
    for (int cnt = 0; cnt < 3; ++cnt) {
        tx = ans_parent.x[cnt], ty = ans_parent.y[cnt];
        for (int i = 0; i < grid[tx][ty].cnt; ++i) {
            grid[tx][ty].dead.push(test_case);
            grid[tx][ty].dir.pop();
        }
        grid[tx][ty].cnt = 0;
    }
}

void delete_dead() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            while (!grid[i][j].dead.empty()) {
                if (grid[i][j].dead.front() + 2 > test_case)break;
                grid[i][j].dead.pop();
            }
        }
    }
}

void baby() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            while (!egg_grid[i][j].dir.empty()) {
                grid[i][j].dir.push(egg_grid[i][j].dir.front());
                egg_grid[i][j].dir.pop();
            }
            grid[i][j].cnt += egg_grid[i][j].cnt;
            egg_grid[i][j].cnt = 0;
        }
    }
}

void debug() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << grid[i][j].cnt << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> M >> T;
    cin >> px >> py;
    px--, py--;
    for (int i = 0; i < M; ++i) {
        int r, c, d;
        cin >> r >> c >> d;
        r--, c--, d--;
        grid[r][c].cnt++;
        grid[r][c].dir.push(d);
    }

    for (test_case = 1; test_case <= T; ++test_case) {
        make_egg();
        mon_moving();
        pa_moving();
        delete_dead();
        baby();
    }
    int result = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result += grid[i][j].cnt;
        }
    }
    cout << result;

    return 0;
}