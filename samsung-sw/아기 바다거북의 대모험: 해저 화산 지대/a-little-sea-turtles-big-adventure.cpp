#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Turtle {
    int r, c, ans;
};
struct Hot {
    int pressure = 0;
    int P = -1;
    int r, c;
    bool is_fire = false;
};

int N, M, K, test_case;
int grid[21][21];
Turtle turtle[11];
Hot mountain[11];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void tmove(int id) {
    int cx = turtle[id].r;
    int cy = turtle[id].c;
    queue<Turtle> q;
    bool visited[21][21] = { false, };
    visited[cx][cy] = true;
    for (int d = 0; d < 4; ++d) {
        int nx = cx + dx[d];
        int ny = cy + dy[d];
        if (!is_range(nx, ny) || grid[nx][ny] != 0)continue;
        visited[nx][ny] = true;
        q.push({ nx,ny,d });
    }

    while (!q.empty()) {
        Turtle curr = q.front();
        if (curr.r == N - 1 && curr.c == N - 1)break;
        q.pop();


        for (int d = 0; d < 4; ++d) {
            int nx = curr.r + dx[d];
            int ny = curr.c + dy[d];
            if (!is_range(nx, ny) || visited[nx][ny] || grid[nx][ny] != 0)continue;
            visited[nx][ny] = true;
            q.push({ nx,ny,curr.ans });
        }
    }

    if (!q.empty()) {
        turtle[id].r += dx[q.front().ans];
        turtle[id].c += dy[q.front().ans];
    }
}

void moving() {
    for (int id = 1; id <= M; ++id) {
        if (turtle[id].ans != 0)continue;
        grid[turtle[id].r][turtle[id].c] = 0;
        tmove(id);
        if (turtle[id].r == N - 1 && turtle[id].c == N - 1)turtle[id].ans = test_case;
        else grid[turtle[id].r][turtle[id].c] = id;
    }
}

void add_pressure() {
    for (int id = 1; id <= K; ++id) mountain[id].pressure += 10;
}

void erupt() {
    int temp[21][21] = { 0, };//열기 기록
    for (int id = 1; id <= K; ++id) {
        if (mountain[id].pressure < mountain[id].P)continue;

        mountain[id].is_fire = true;
        int cx = mountain[id].r;
        int cy = mountain[id].c;
        temp[cx][cy] += mountain[id].P;
        for (int d = 0; d < 4; ++d) {
            int nx = cx, ny = cy, p = mountain[id].P;
            while (true) {
                nx += dx[d], ny += dy[d], p = p / 2;
                if (!is_range(nx, ny) || p == 0 || grid[nx][ny] == -1)break;
                temp[nx][ny] += p;
            }
        }
    }

    //연쇄
    bool is_erupt = true;
    while (is_erupt) {
        is_erupt = false;
        for (int id = 1; id <= K; ++id) {
            if (mountain[id].is_fire)continue;
            if ((mountain[id].pressure + temp[mountain[id].r][mountain[id].c]) < mountain[id].P)continue;

            mountain[id].is_fire = true;
            is_erupt = true;
            int cx = mountain[id].r;
            int cy = mountain[id].c;
            temp[cx][cy] += mountain[id].P;
            for (int d = 0; d < 4; ++d) {
                int nx = cx, ny = cy, p = mountain[id].P;
                while (true) {
                    nx += dx[d], ny += dy[d], p = p / 2;
                    if (!is_range(nx, ny) || p == 0 || grid[nx][ny] == -1)break;
                    temp[nx][ny] += p;
                }
            }
        }
    }


    for (int id = 1; id <= M; ++id) {
        if (turtle[id].ans != 0)continue;
        if (temp[turtle[id].r][turtle[id].c] >= 20) {
            grid[turtle[id].r][turtle[id].c] = -2;
            turtle[id].ans = -1;
        }
    }
}

void clear_sea() {
    for (int id = 1; id <= K; ++id) {
        if (mountain[id].is_fire)mountain[id].pressure = 0;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            grid[i][j] *= -1;
        }
    }
    for (int id = 1; id <= M; ++id) {
        int r, c;
        cin >> r >> c;
        turtle[id] = { r,c,0 };
        grid[r][c] = id;
    }
    for (int id = 1; id <= K; ++id) {
        int r, c, P;
        cin >> r >> c >> P;
        mountain[id] = { 0,P,r,c,false };
    }

    for (test_case = 1; test_case <= 100; ++test_case) {
        moving();
        add_pressure();
        erupt();
        clear_sea();
    }

    for (int id = 1; id <= M; ++id) {
        if (turtle[id].ans == 0)turtle[id].ans = -1;
        cout << turtle[id].ans << "\n";
    }
    return 0;
}