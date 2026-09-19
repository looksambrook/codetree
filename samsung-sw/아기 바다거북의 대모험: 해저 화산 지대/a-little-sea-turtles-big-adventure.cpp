#include <iostream>
#include <queue>

using namespace std;

struct Info
{
    int x;
    int y;
    int tmp;//turtle:ans
};

struct vInfo
{
    int x;
    int y;
    int P;
    int pressure;
    bool is_erupt;
};

int test_case = 0;
int N, M, K;
int beach[20][20];
int volbeach[20][20];
Info turtle[10];
int tcnt = 0;
vInfo volcano[10];
int vcnt = 0;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { 1,0,-1,0 };
int goals = 0;

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void print_board() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << beach[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void print_vol() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << volbeach[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void first_step() { //이동여부확인후, 단한칸이동
    for (int i = 0; i < tcnt; ++i) {
        bool visited[20][20] = { false, };
        int cx = turtle[i].x;
        int cy = turtle[i].y;
        if (cx == -1)continue;
        visited[cx][cy] = true;
        int is_moved = -1;
        queue<Info> q;
        for (int j = 0; j < 4; ++j) {
            int nx = cx + dx[j];
            int ny = cy + dy[j];
            if (is_range(nx, ny) && !visited[nx][ny] && beach[nx][ny] == 0) {
                if (nx == N - 1 && ny == N - 1) {
                    is_moved = j;
                    break;
                }
                q.push({ nx,ny,j });
                visited[nx][ny] = true;
            }
        }

        if (is_moved == -1) {
            while (!q.empty()) {
                cx = q.front().x;
                cy = q.front().y;
                int dir = q.front().tmp;
                q.pop();

                for (int j = 0; j < 4; ++j) {
                    int nx = cx + dx[j];
                    int ny = cy + dy[j];
                    if (is_range(nx, ny) && !visited[nx][ny] && beach[nx][ny] == 0) {
                        visited[nx][ny] = true;
                        if (nx == N - 1 && ny == N - 1) {
                            is_moved = dir;
                            break;
                        }
                        q.push({ nx,ny,dir });
                    }
                }
                if (is_moved != -1)break;
            }
        }

        if (is_moved != -1) {
            cx = turtle[i].x, cy = turtle[i].y;
            int nx = cx + dx[is_moved];
            int ny = cy + dy[is_moved];
            if ((nx == N - 1) && (ny == N - 1)) {
                turtle[i] = { -1,-1,test_case };
                beach[cx][cy] = 0;
                goals--;
            }
            else {
                beach[nx][ny] = beach[cx][cy];
                turtle[i] = { nx,ny,-1 };
                beach[cx][cy] = 0;
            }
        }
    }
}

void second_step() {//압력 증가 및 순수 압력으로 폭발
    for (int i = 0; i < vcnt; ++i) {
        int cx = volcano[i].x;
        int cy = volcano[i].y;
        volcano[i].pressure += 10;

        if (volcano[i].pressure >= volcano[i].P) {
            volcano[i].is_erupt = true;
            volbeach[cx][cy] += volcano[i].P;
            int nx, ny;
            for (int j = 0; j < 4; ++j) {
                int hot = volcano[i].P;
                nx = cx;
                ny = cy;
                hot /= 2;
                while (hot > 0) {
                    nx += dx[j];
                    ny += dy[j];
                    if (is_range(nx, ny) && beach[nx][ny] != 1)
                        volbeach[nx][ny] += hot;
                    hot /= 2;
                }
            }
        }
    }
}

void third_step() {//연쇄 폭발(압력+열기)
    for (int i = 0; i < vcnt; ++i) {
        if (volcano[i].is_erupt)continue;
        int cx = volcano[i].x;
        int cy = volcano[i].y;
        if ((volcano[i].pressure + volbeach[cx][cy]) >= volcano[i].P) {
            volcano[i].is_erupt = true;
            volbeach[cx][cy] += volcano[i].P;
            int nx, ny;
            for (int j = 0; j < 4; ++j) {
                int hot = volcano[i].P;
                nx = cx;
                ny = cy;
                hot /= 2;
                while (hot > 0) {
                    nx += dx[j];
                    ny += dy[j];
                    if (is_range(nx, ny) && beach[nx][ny] != 1)
                        volbeach[nx][ny] += hot;
                    hot /= 2;
                }
            }
        }
    }
}

void fourth_step() {//터질 것과 안터질 것 정리 및 후속 조치
    for (int i = 0; i < vcnt; ++i) {
        if (volcano[i].is_erupt)volcano[i].pressure = 0;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (beach[i][j] >= 100 && volbeach[i][j] >= 20) {
                turtle[beach[i][j] - 100] = { -1,-1,-1 };
                beach[i][j] = 2;
                goals--;
            }
            volbeach[i][j] = 0;
        }
    }
}

int main() {
    // Please write your code here.
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> beach[i][j];
        }
    }
    for (int i = 0; i < M; ++i) {
        int r, c;;
        cin >> r >> c;
        turtle[tcnt++] = { r,c,-1 };
        beach[r][c] = 100 + i;
    }
    goals = tcnt;
    for (int i = 0; i < K; ++i) {
        int r, c, P;
        cin >> r >> c >> P;
        volcano[vcnt++] = { r,c,P,0,false };
    }

    while (test_case <= 100 && goals > 0) {
        test_case++;
        first_step();
        second_step();
        third_step();
        fourth_step();
    }

    for (int i = 0; i < tcnt; ++i)
        cout << turtle[i].tmp << "\n";

    return 0;
}