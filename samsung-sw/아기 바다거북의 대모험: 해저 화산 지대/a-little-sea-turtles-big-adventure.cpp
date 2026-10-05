#include <iostream>
#include <queue>

using namespace std;

struct Info {
    int r, c, val;
};

int N, M, K;
int beach[21][21];
int fire_power[21][21];
Info turtle[11];
Info fire[11];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> beach[i][j];
            beach[i][j] *= -1;
        }
    }
    for (int i = 1; i <= M; ++i) {
        int r, c;
        cin >> r >> c;
        turtle[i] = { r,c,0 };
        beach[r][c] = i;
    }
    for (int i = 0; i < K; ++i) {
        int r, c, p;
        cin >> r >> c >> p;
        fire[i] = { r,c,p };
    }

    for (int tc = 1; tc <= 100; ++tc) {
        //step 1
        for (int i = 1; i <= M; ++i) {
            if (turtle[i].val != 0)continue;
            bool visited[21][21] = { false, };
            visited[turtle[i].r][turtle[i].c] = true;
            queue<Info> q;
            for (int d = 0; d < 4; ++d) {
                int nx = turtle[i].r + dx[d];
                int ny = turtle[i].c + dy[d];
                if (!is_range(nx, ny)||beach[nx][ny]!=0||visited[nx][ny])continue;
                q.push({ nx,ny,d });
                visited[nx][ny] = true;
            }
            while (!q.empty()) {
                Info curr = q.front();
                q.pop();
                if (curr.r == N - 1 && curr.c == N - 1) {
                    beach[turtle[i].r][turtle[i].c] = 0;
                    turtle[i].r += dx[curr.val];
                    turtle[i].c += dy[curr.val];
                    beach[turtle[i].r][turtle[i].c] = i;
                    break;
                }

                for (int d = 0; d < 4; ++d) {
                    int nx = curr.r + dx[d];
                    int ny = curr.c + dy[d];
                    if (!is_range(nx, ny) || beach[nx][ny] != 0 || visited[nx][ny])continue;
                    q.push({ nx,ny,curr.val });
                    visited[nx][ny] = true;
                }
            }
            if (turtle[i].r == N - 1 && turtle[i].c == N - 1) {
                beach[turtle[i].r][turtle[i].c] = 0;
                turtle[i].val = tc;
            }
        }

        int list[11];
        int lcnt = 0;
        //step 2
        for (int i = 0; i < K; ++i) {
            fire_power[fire[i].r][fire[i].c] += 10;
            if (fire_power[fire[i].r][fire[i].c] >= fire[i].val) {
                list[lcnt++] = i;
                fire_power[fire[i].r][fire[i].c] = 0;
            }
        }

        bool visited[11] = { false, };
        int hot_beach[21][21] = { 0, };
        for (int i = 0; i < lcnt; ++i) {
            visited[list[i]] = true;
            hot_beach[fire[list[i]].r][fire[list[i]].c] += fire[list[i]].val;
            for (int d = 0; d < 4; ++d) {
                int cx = fire[list[i]].r;
                int cy = fire[list[i]].c;
                int heater = fire[list[i]].val;
                while (true) {
                    cx += dx[d];
                    cy += dy[d];
                    heater /= 2;
                    if (!is_range(cx,cy)||beach[cx][cy] == -1 || heater == 0)break;
                    hot_beach[cx][cy] += heater;
                }
            }
        }
        bool is_fire = true;
        while (is_fire) {
            is_fire = false;
            for (int i = 0; i < K; ++i) {
                if (visited[i])continue;
                if ((fire_power[fire[i].r][fire[i].c] + hot_beach[fire[i].r][fire[i].c]) >= fire[i].val) {
                    visited[i] = true;
                    is_fire = true;
                    hot_beach[fire[i].r][fire[i].c] += fire[i].val;
                    fire_power[fire[i].r][fire[i].c] = 0;
                    for (int d = 0; d < 4; ++d) {
                        int cx = fire[i].r;
                        int cy = fire[i].c;
                        int heater = fire[i].val;
                        while (true) {
                            cx += dx[d];
                            cy += dy[d];
                            heater /= 2;
                            if (!is_range(cx, cy) || beach[cx][cy] == -1 || heater == 0)break;
                            hot_beach[cx][cy] += heater;
                        }
                    }
                }
            }
        }
        bool is_done = true;
        for (int i = 1; i <= M; ++i) {
            if (turtle[i].val != 0)continue;
            is_done = false;
            if (hot_beach[turtle[i].r][turtle[i].c] >= 20) {
                beach[turtle[i].r][turtle[i].c] = -2;
                turtle[i].val = -1;
            }
        }
        if (is_done)break;
    }
    for (int i = 1; i <= M; ++i) {
        if (turtle[i].val == 0)turtle[i].val = -1;
        cout << turtle[i].val << "\n";
    }
    return 0;
}