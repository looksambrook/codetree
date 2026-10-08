#include <iostream>
#include <queue>

using namespace std;

struct Info {
    int hr, hc;
    int score;
};

int N, M, K;
int grid[21][21];
int temp[21][21];
Info team[5];
int dx[] = { 0,-1,0,1 };
int dy[] = { 1,0,-1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void moving() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] != 0)temp[i][j] = 4;
            else temp[i][j] = 0;
        }
    }
    for (int team_id = 0; team_id < M; ++team_id) {
        int cx = team[team_id].hr;
        int cy = team[team_id].hc;
        int nx, ny;
        for (int d = 0; d < 4; ++d) {
            nx = cx + dx[d];
            ny = cy + dy[d];
            if (!is_range(nx, ny))continue;
            if (temp[nx][ny] == 4) {
                if (grid[nx][ny] == 2) continue;
                team[team_id].hr = nx;
                team[team_id].hc = ny;
                temp[nx][ny] = grid[cx][cy];
            }
        }

        bool tail = false;
        while (!tail) {
            bool find = false;
            for (int d = 0; d < 4; ++d) {
                nx = cx + dx[d];
                ny = cy + dy[d];
                if (!is_range(nx, ny))continue;
                if (grid[cx][cy] != 1 && grid[nx][ny] == 3) {
                    if (temp[nx][ny] == 4 || temp[nx][ny] == 1) {
                        tail = true;
                        temp[cx][cy] = 3;
                        break;
                    }
                }
                else if (temp[nx][ny] == 4) {
                    if (grid[nx][ny] == 4) continue;
                    temp[cx][cy] = grid[nx][ny];
                    cx = nx, cy = ny;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            grid[i][j] = temp[i][j];
        }
    }
}

void find_head(int x, int y) {
    queue<Info> q;
    bool visited[21][21] = { false, };
    q.push({ x,y,1 });
    visited[x][y] = true;
    int hr, hc, tr, tc, ti;

    while (!q.empty()) {
        int cx = q.front().hr;
        int cy = q.front().hc;
        int cd = q.front().score;
        q.pop();

        if (grid[cx][cy] == 1) {
            for (int team_id = 0; team_id < M; ++team_id) {
                if (cx == team[team_id].hr && cy == team[team_id].hc) {
                    team[team_id].score += cd * cd;
                    ti = team_id;
                    hr = cx, hc = cy;
                    break;
                }
            }
        }
        else if (grid[cx][cy] == 3) {
            tr = cx, tc = cy;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (!is_range(nx, ny) || visited[nx][ny])continue;
            if (grid[nx][ny] == 0 || grid[nx][ny] == 4)continue;
            if (grid[nx][ny] * grid[cx][cy] == 3)continue;
            visited[nx][ny] = true;
            q.push({ nx,ny,cd + 1 });
        }
    }

    grid[tr][tc] = 1;
    grid[hr][hc] = 3;
    team[ti].hr = tr;
    team[ti].hc = tc;
}

void ball(int round) {
    int dir = round / N;
    int target = round % N;

    if (dir == 0) {
        for (int i = 0; i < N; ++i) {
            if (grid[target][i] == 4 || grid[target][i] == 0)continue;
            find_head(target, i);
            break;
        }
    }
    else if (dir == 1) {
        for (int i = N - 1; i >= 0; --i) {
            if (grid[i][target] == 4 || grid[i][target] == 0)continue;
            find_head(i, target);
            break;
        }
    }
    else if (dir == 2) {
        target = N - 1 - target;
        for (int i = N - 1; i >= 0; --i) {
            if (grid[target][i] == 4 || grid[target][i] == 0)continue;
            find_head(target, i);
            break;
        }
    }
    else if (dir == 3) {
        target = N - 1 - target;
        for (int i = 0; i < N; ++i) {
            if (grid[i][target] == 4 || grid[i][target] == 0)continue;
            find_head(i, target);
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    int team_cnt = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 1)team[team_cnt++] = { i,j,0 };
        }
    }

    for (int test_case = 1; test_case <= K; ++test_case) {
        moving();
        ball((test_case - 1) % (4 * N));
    }
    int result = 0;
    for (int team_id = 0; team_id < M; ++team_id) result += team[team_id].score;
    cout << result;

    return 0;
}