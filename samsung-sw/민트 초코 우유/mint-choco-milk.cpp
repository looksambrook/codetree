#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Info {
    int type;
    int B;
    int r;
    int c;
    int core;
    bool operator<(const Info& other)const {
        if (core != other.core)return core > other.core;
        if (B != other.B)return B < other.B;
        if (r != other.r)return r > other.r;
        return c > other.c;
    }
};
int N, T;
Info grid[51][51];
priority_queue<Info> pq;
int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void breakfast() {
}

void lunch() {
    bool visited[51][51] = { false, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (visited[i][j])continue;
            visited[i][j] = true;
            queue<Info> v;
            int vcnt = 0;
            priority_queue<Info> best;
            v.push(grid[i][j]);
            while (!v.empty()) {
                int cx = v.front().r;
                int cy = v.front().c;
                best.push(v.front());
                v.pop();
                for (int d = 0; d < 4; ++d) {
                    int nx = cx + dx[d];
                    int ny = cy + dy[d];
                    if (!is_range(nx, ny) || visited[nx][ny] || grid[nx][ny].type != grid[cx][cy].type)continue;
                    v.push(grid[nx][ny]);
                    visited[nx][ny] = true;
                }
                vcnt++;
            }
            grid[best.top().r][best.top().c].B += vcnt;
            pq.push(grid[best.top().r][best.top().c]);
        }
    }
}

void dinner() {
    bool visited[51][51] = { false, };
    while (!pq.empty()) {
        Info curr = pq.top();
        pq.pop();
        int cx = curr.r;
        int cy = curr.c;
        if (visited[cx][cy])continue;

        int P = curr.B - 1;
        int d = curr.B % 4;
        grid[cx][cy].B = 1;
        int nx = cx + dx[d];
        int ny = cy + dy[d];
        while (P > 0 && is_range(nx, ny)) {
            if (grid[nx][ny].type != grid[cx][cy].type) {
                visited[nx][ny] = true;
                if (P > grid[nx][ny].B) {
                    grid[nx][ny] = { grid[cx][cy].type,grid[nx][ny].B + 1,nx,ny,grid[cx][cy].core };
                    P -= grid[nx][ny].B;
                }
                else {
                    int tmp = grid[nx][ny].type;
                    int ctmp = grid[nx][ny].core;
                    if (tmp == 1) {
                        if (grid[cx][cy].type >= 6)tmp = 7, ctmp = 3;
                        else if (grid[cx][cy].type > 3)tmp = grid[cx][cy].type, ctmp = 2;
                        else tmp += grid[cx][cy].type + 1, ctmp = 2;
                    }
                    else if (tmp == 2) {
                        if (grid[cx][cy].type == 5 || grid[cx][cy].type == 7)tmp = 7, ctmp = 3;
                        else if (grid[cx][cy].type > 3)tmp = grid[cx][cy].type, ctmp = 2;
                        else tmp += grid[cx][cy].type + 1, ctmp = 2;
                    }
                    else if (tmp == 3) {
                        if (grid[cx][cy].type == 4 || grid[cx][cy].type == 7)tmp = 7, ctmp = 3;
                        else if (grid[cx][cy].type > 3)tmp = grid[cx][cy].type, ctmp = 2;
                        else tmp += grid[cx][cy].type + 1, ctmp = 2;
                    }
                    else if (tmp == 4) {
                        if (!(grid[cx][cy].type == 1 || grid[cx][cy].type == 2)) ctmp = 3, tmp = 7;
                    }
                    else if (tmp == 5) {
                        if (!(grid[cx][cy].type == 1 || grid[cx][cy].type == 3)) ctmp = 3, tmp = 7;
                    }
                    else if (tmp == 6) {
                        if (!(grid[cx][cy].type == 3 || grid[cx][cy].type == 2)) ctmp = 3, tmp = 7;
                    }
                    grid[nx][ny] = { tmp, P + grid[nx][ny].B,nx,ny,ctmp };
                    P = 0;
                }
            }
            nx += dx[d];
            ny += dy[d];
        }
    }

    int cal[8] = { 0, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cal[grid[i][j].type] += grid[i][j].B;
        }
    }
    cout << cal[7] << " " << cal[4] << " " << cal[5] << " " << cal[6] << " " << cal[3] << " " << cal[2] << " " << cal[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> T;
    for (int i = 0; i < N; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < N; ++j) {
            if (s[j] == 'T')grid[i][j] = { 1,0,i,j,1 };
            else if (s[j] == 'C')grid[i][j] = { 2,0,i,j,1 };
            else grid[i][j] = { 3,0,i,j,1 };
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int tmp;
            cin >> tmp;
            grid[i][j].B = tmp;
        }
    }

    for (int tc = 1; tc <= T; ++tc) {
        breakfast();
        lunch();
        dinner();
    }
    return 0;
}