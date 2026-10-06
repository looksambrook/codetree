#include <iostream>
#include <queue>

using namespace std;

struct Info {
    int x, y;
};

int N, K, L;
int grid[31][31];
int rocation[31][31];
Info cleaner[51];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
int cal;

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void first_step() {
    for (int i = 1; i <= K; ++i) {
        int x = cleaner[i].x;
        int y = cleaner[i].y;
        if (grid[x][y] != 0)continue;
        rocation[x][y] = 0;

        queue<pair<Info, int>>q;
        bool visited[31][31] = { false, };
        q.push({ {x,y},0 });
        visited[x][y] = true;

        Info target = { N,N };
        int tcnt = 1000;

        while (!q.empty()) {  //visited, rocation, grid, is_range
            int cx = q.front().first.x;
            int cy = q.front().first.y;
            int ccnt = q.front().second;
            q.pop();

            if (grid[cx][cy] > 0) {
                if (tcnt > ccnt) {
                    target = { cx,cy };
                    tcnt = ccnt;
                }
                else if (tcnt == ccnt) {
                    if (target.x > cx) {
                        target = { cx,cy };
                        tcnt = ccnt;
                    }
                    else if (target.x == cx) {
                        if (target.y > cy) {
                            target = { cx,cy };
                            tcnt = ccnt;
                        }
                    }
                }
                continue;
            }

            for (int d = 0; d < 4; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (!is_range(nx, ny) || visited[nx][ny] || rocation[nx][ny] != 0 || grid[nx][ny] == -1)continue;
                visited[nx][ny] = true;
                if (ccnt > tcnt)break;
                q.push({ {nx,ny},ccnt + 1 });
            }
        }
        if (tcnt!=1000) cleaner[i] = target;
        rocation[cleaner[i].x][cleaner[i].y] = i;
    }
}

void clean() {
    for (int i = 1; i <= K; ++i) {
        int sum = 0, td;
        for (int dd = 2; dd < 6; ++dd) {
            int tmp = 0;
            for (int d = 0; d < 4; ++d) {
                if (d == (dd % 4))continue;
                int nx = cleaner[i].x + dx[d];
                int ny = cleaner[i].y + dy[d];
                if (!is_range(nx, ny) || grid[nx][ny] == -1)continue;
                if (grid[nx][ny] > 20)tmp += 20;
                else tmp += grid[nx][ny];
            }
            if (sum < tmp) {
                sum = tmp, td = dd % 4;
            }
        }

        if (sum != 0) {
            for (int d = 0; d < 4; ++d) {
                if (d == td )continue;
                int nx = cleaner[i].x + dx[d];
                int ny = cleaner[i].y + dy[d];
                if (!is_range(nx, ny) || grid[nx][ny] == -1)continue;
                sum = grid[nx][ny] > 20 ? 20 : grid[nx][ny];
                grid[nx][ny] -= sum;
            }
        }
        sum = grid[cleaner[i].x][cleaner[i].y] > 20 ? 20 : grid[cleaner[i].x][cleaner[i].y];
        grid[cleaner[i].x][cleaner[i].y] -= sum;
    }
}

void dirt() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] > 0) {
                grid[i][j] += 5;
            }
        }
    }
}

void spread() {
    int temp[31][31] = { 0, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] != 0)continue;
            int sum = 0;
            for (int d = 0; d < 4; ++d) {
                int nx = i + dx[d];
                int ny = j + dy[d];
                if (!is_range(nx, ny) || grid[nx][ny] == -1)continue;
                sum += grid[nx][ny];
            }
            temp[i][j] = (sum / 10);
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            grid[i][j] += temp[i][j];
            if (grid[i][j] != -1)cal += grid[i][j];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K >> L;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    for (int i = 1; i <= K; ++i) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        cleaner[i] = { r,c };
        rocation[r][c] = i;
    }

    for (int tc = 1; tc <= L; ++tc) {
        cal = 0;
        first_step();
        clean();
        dirt();
        spread();
        cout << cal << "\n";
    }

    return 0;
}