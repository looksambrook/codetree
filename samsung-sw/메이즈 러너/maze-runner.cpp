#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Info {
    int r, c, dis;
};
int N, M, K;
int grid[11][11];
int result = 0;
int ex, ey;
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

int cal_dist(int x, int y) {
    return abs(x - ex) + abs(y - ey);
}

bool moving() {
    bool is_alive = false;
    int temp[11][11] = { 0, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] < 0) {
                is_alive = true;
                int dist = cal_dist(i, j);
                int tdir = -1;
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    if (!is_range(nx, ny))continue;
                    if (grid[nx][ny] > 0)continue;
                    int tdist = cal_dist(nx, ny);
                    if (dist > tdist) {
                        tdist = dist;
                        tdir = d;
                        break;
                    }
                }
                if (tdir != -1) {
                    temp[i + dx[tdir]][j + dy[tdir]] += grid[i][j];
                    grid[i][j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (temp[i][j] != 0) {
                if(!(i==ex&&j==ey)) grid[i][j] += temp[i][j];
                result -= temp[i][j];
            }
        }
    }
    return is_alive;
}

void rotate() {
    int temp[11][11] = { 0, };
    int tx = N, ty = N;
    int n=20000;
    bool visited[11][11] = { false, };
    queue<pair<int,int>> q;
    q.push({ ex,ey });
    visited[ex][ey] = true;
    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        if (grid[cx][cy] < 0) {
            int cd = max(abs(cx - ex), abs(cy - ey));
            cx = max(cx, ex) - cd < 0 ? 0 : max(cx, ex) - cd;
            cy = max(cy, ey) - cd < 0 ? 0 : max(cy, ey) - cd;
            if ((cd < n)||(cd==n&& ((cx < tx) || (cx == tx && cy < ty)))) {
                tx = cx, ty = cy, n = cd;
            }
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = cx+dx[d];
            int ny = cy+dy[d];
            if (!is_range(nx, ny)||visited[nx][ny])continue;
            visited[nx][ny]=true;
            q.push({ nx,ny});
        }
    }

    if (tx == N)return;
    n++;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (ex == tx + i && ey == ty + j) temp[j][n - 1 - i] = -100;
            else temp[j][n - 1 - i] = grid[tx + i][ty + j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (temp[i][j] > 0) grid[tx + i][ty + j] = temp[i][j] - 1;
            else {
                if (temp[i][j] ==-100) {
                    ex = tx + i;
                    ey = ty + j;
                    temp[i][j] = 0;
                }
                grid[tx + i][ty + j] = temp[i][j];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    for (int i = 1; i <= M; ++i) {
        int r, c;
        cin >> r >> c;
        grid[r-1][c-1] -= 1;
    }
    cin >> ex >> ey;
    ex--; ey--;

    for (int tc = 1; tc <= K; ++tc) {
        if (!moving())break;
        rotate();
    }
    cout << result << "\n" << ex+1 << " " << ey+1;

    return 0;
}