#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Info {
    int r, c, d, v;
};

int N, M, F;
int cr, cc, cw;
int sr, sc;
int tj, tw;
int grid[21][21];
int black[21][21];
int wall[6][11][11];
vector<Info> dirt;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };

bool is_range(int x, int y,int r) {
    return x >= 0 && x < r
        && y >= 0 && y < r;
}

void spread(Info data) {
    grid[data.r][data.c] = 5;
    black[data.r][data.c] = 1;
    int cx = data.r;
    int cy = data.c;
    int tc = 0;
    while (true) {
        cx += dx[data.d];
        cy += dy[data.d];
        tc += data.v;
        if (!is_range(cx, cy,N) || (grid[cx][cy] != 0 && grid[cx][cy] < 5))break;
        grid[cx][cy] = 5;
        if (black[cx][cy] == 0 || black[cx][cy] > tc)black[cx][cy] = tc;
    }
}

int time_wall() {
    bool visited[6][11][11] = { false, };
    queue<Info> q;
    q.push({ cr,cc,cw,0 });
    visited[cw][cr][cc] = true;
    while (!q.empty()) {
        cr = q.front().r;
        cc = q.front().c;
        cw = q.front().d;
        int ccnt = q.front().v;
        q.pop();

        if (tw == cw && cr == M-1 && cc == tj) {
            return ccnt;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = cr + dx[d];
            int ny = cc + dy[d];
            if (is_range(nx, ny,M)) {
                if (visited[cw][nx][ny] || wall[cw][nx][ny] == 1)continue;
                visited[cw][nx][ny] = true;
                q.push({ nx,ny,cw,ccnt + 1 });
            }
            else {
                if (cw < 4 && nx == M)continue;
                if (cw == 0) {
                    if (nx == -1) {
                        int tmp = M - 1 - ny;
                        if (visited[4][tmp][M-1] || wall[4][tmp][M-1] == 1)continue;
                        visited[4][tmp][M-1] = true;
                        q.push({ tmp,M-1,4,ccnt + 1 });
                    }
                    else if (ny == -1) {
                        if (visited[2][nx][M-1] || wall[2][nx][M-1] == 1)continue;
                        visited[2][nx][M - 1] = true;
                        q.push({ nx,M - 1,2,ccnt + 1 });
                    }
                    else if (ny == M) {
                        if (visited[3][nx][0] || wall[3][nx][0] == 1)continue;
                        visited[3][nx][0] = true;
                        q.push({ nx,0,3,ccnt + 1 });
                    }
                }
                else if (cw == 1) {
                    if (nx == -1) {
                        if (visited[4][ny][0] || wall[4][ny][0] == 1)continue;
                        visited[4][ny][0] = true;
                        q.push({ ny,0,4,ccnt + 1 });
                    }
                    else if (ny == -1) {
                        if (visited[3][nx][M - 1] || wall[3][nx][M - 1] == 1)continue;
                        visited[3][nx][M - 1] = true;
                        q.push({ nx,M - 1,3,ccnt + 1 });
                    }
                    else if (ny == M) {
                        if (visited[2][nx][0] || wall[2][nx][0] == 1)continue;
                        visited[2][nx][0] = true;
                        q.push({ nx,0,2,ccnt + 1 });
                    }
                }
                else if (cw == 2) {
                    if (nx == -1) {
                        if (visited[4][M - 1][ny] || wall[4][M - 1][ny] == 1)continue;
                        visited[4][M - 1][ny] = true;
                        q.push({ M - 1,ny,4,ccnt + 1 });
                    }
                    else if (ny == -1) {
                        if (visited[1][nx][M - 1] || wall[1][nx][M - 1] == 1)continue;
                        visited[1][nx][M - 1] = true;
                        q.push({ nx,M - 1,1,ccnt + 1 });
                    }
                    else if (ny == M) {
                        if (visited[0][nx][0] || wall[0][nx][0] == 1)continue;
                        visited[0][nx][0] = true;
                        q.push({ nx,0,0,ccnt + 1 });
                    }
                }
                else if (cw == 3) {
                    if (nx == -1) {
                        int tmp = M - 1 - ny;
                        if (visited[4][0][tmp] || wall[4][0][tmp] == 1)continue;
                        visited[4][0][tmp] = true;
                        q.push({ 0,tmp,4,ccnt + 1 });
                    }
                    else if (ny == -1) {
                        if (visited[0][nx][M - 1] || wall[0][nx][M - 1] == 1)continue;
                        visited[0][nx][M - 1] = true;
                        q.push({ nx,M - 1,0,ccnt + 1 });
                    }
                    else if (ny == M) {
                        if (visited[1][nx][0] || wall[1][nx][0] == 1)continue;
                        visited[1][nx][0] = true;
                        q.push({ nx,0,1,ccnt + 1 });
                    }
                }
                else if (cw == 4) {
                    if (nx == -1) {
                        int tmp = M - 1 - ny;
                        if (visited[3][0][tmp] || wall[3][0][tmp] == 1)continue;
                        visited[3][0][tmp] = true;
                        q.push({ 0,tmp,3,ccnt + 1 });
                    }
                    if (nx == M) {
                        if (visited[2][0][ny] || wall[2][0][ny] == 1)continue;
                        visited[2][0][ny] = true;
                        q.push({ 0,ny,2,ccnt + 1 });
                    }
                    else if (ny == -1) {
                        if (visited[1][0][nx] || wall[1][0][nx] == 1)continue;
                        visited[1][0][nx] = true;
                        q.push({ 0,nx,1,ccnt + 1 });
                    }
                    else if (ny == M) {
                        int tmp = M - 1 - nx;
                        if (visited[0][0][tmp] || wall[0][0][tmp] == 1)continue;
                        visited[0][0][tmp] = true;
                        q.push({ 0,tmp,0,ccnt + 1 });
                    }
                }
            }
        }
    }
    return -1;
}

int moving(int tc) {
    bool visited[21][21] = { false, };
    int ans = 50000;
    queue<Info> q;
    q.push({ sr,sc,tc+1 });
    visited[sr][sc] = true;
    if (grid[sr][sc] == 5 && black[sr][sc] <= tc+1)return -1;

    while (!q.empty()) {
        int cx = q.front().r;
        int cy = q.front().c;
        int ccnt = q.front().d;
        q.pop();

        if (grid[cx][cy] == 4) {
            if (ans > ccnt)ans = ccnt;
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (!is_range(nx, ny,N) || visited[nx][ny])continue;
            if (grid[nx][ny] == 1 || grid[nx][ny] == 3)continue;
            if (grid[nx][ny] == 5 && black[nx][ny] <= ccnt+1)continue;
            visited[nx][ny] = true;
            q.push({ nx,ny,ccnt + 1 });
        }
    }
    if (ans != 50000)return ans;
    return -1;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> F;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            if (i != 0 && grid[i - 1][j] == 0 && grid[i][j] == 3) {
                tw = 3, sr = i - 1, sc = j, tj = M - 1;
                for (int k = 1; k < M; ++k) {
                    if (is_range(i, j - k, N) && grid[i][j - k] == 3) {
                        tj--;
                    }
                    else break;
                }
            }
            else if (j != 0 && grid[i][j - 1] == 0 && grid[i][j] == 3) {
                tw = 1, sr = i, sc = j - 1, tj = 0;
                for (int k = 1; k < M; ++k) {
                    if (is_range(i - k, j, N) && grid[i - k][j] == 3) {
                        tj++;
                    }
                    else break;
                }
            }
            else if (i != 0 && grid[i - 1][j] == 3 && grid[i][j] == 0) {
                tw = 2, sr = i, sc = j, tj = 0;
                for (int k = 1; k < M; ++k) {
                    if (is_range(i - 1, j-k, N) && grid[i - 1][j-k] == 3) {
                        tj++;
                    }
                    else break;
                }
            }
            else if (j != 0 && grid[i][j - 1] == 3 && grid[i][j] == 0) {
                tw = 0, sr = i, sc = j, tj = M - 1;
                for (int k = 1; k < M; ++k) {
                    if (is_range(i - k, j-1, N) && grid[i - k][j-1] == 3) {
                        tj--;
                    }
                    else break;
                }
            }
        }
    }
    for (int w = 0; w < 5; ++w) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < M; ++j) {
                cin >> wall[w][i][j];
                if (wall[w][i][j] == 2) {
                    cr = i, cc = j, cw = w;
                }
                if (tw == w && i == M-1 && j == tj)if (wall[w][i][j] == 1)cout << "[debug] tj바꿔야함!!!!\n";
            }
        }
    }
    for (int i = 0; i < F; ++i) {
        int r, c, d, v;
        cin >> r >> c >> d >> v;
        dirt.push_back({ r,c,d,v });
        spread(dirt[i]);
    }

    int test_case = time_wall();
    //cout << test_case<<" ey\n";
    test_case = moving(test_case);
    cout << test_case;

    return 0;
}