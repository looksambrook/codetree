#include <iostream>
using namespace std;

struct Info {
    int r;
    int c;
    int down;
    int sum;
};

int N, M, P, C, D;
int rr, rc;
int tc;
int grid[51][51];
int dx[] = { -1,0,1,0,-1,1,1,-1 };
int dy[] = { 0,1,0,-1,1,1,-1,-1 };
Info san[32];

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

int find_dist(int r1, int c1, int r2, int c2) {
    return (r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2);
}

void commu(int id, int dir) {
    int cx = san[id].r + dx[dir];
    int cy = san[id].c + dy[dir];
    if (!is_range(cx, cy)) {
        san[id].down = M + 1;
        return;
    }
    if (grid[cx][cy] != 0) {
        commu(grid[cx][cy], dir);
    }
    grid[cx][cy] = id;
    san[id].r = cx;
    san[id].c = cy;
}

void crash(int id, int dir, int val) {
    int cx = san[id].r + dx[dir] * val;
    int cy = san[id].c + dy[dir] * val;
    if (!is_range(cx, cy)) {
        san[id].down = M + 1;
        return;
    }
    if (grid[cx][cy] != 0) {
        commu(grid[cx][cy], dir);
    }
    grid[cx][cy] = id;
    san[id].down = tc;
    san[id].r = cx;
    san[id].c = cy;
}

void ru_moving() {
    int dist = 3000, target;
    for (int i = 1; i <= P; ++i) {
        if (san[i].down != M + 1) {
            int tdist = find_dist(san[i].r, san[i].c, rr, rc);
            if (dist < tdist) continue;
            else if (dist == tdist) {
                if (san[target].r > san[i].r)continue;
                else if (san[target].r == san[i].r) {
                    if (san[target].c > san[i].c)continue;
                }
            }
            target = i;
            dist = tdist;
        }
    }

    int dir;
    dist= find_dist(san[target].r, san[target].c, rr, rc);
    for (int d = 0; d < 8; ++d) {
        int tdist = find_dist(san[target].r, san[target].c, rr + dx[d], rc + dy[d]);
        if (tdist < dist) {
            dist = tdist;
            dir = d;
        }
    }

    grid[rr][rc] = 0;
    rr += dx[dir], rc += dy[dir];
    if (grid[rr][rc] != 0) {
        san[grid[rr][rc]].sum += C;
        crash(grid[rr][rc], dir, C);
    }
    grid[rr][rc] = -1;
}

void san_moving() {
    for (int i = 1; i <= P; ++i) {
        if (san[i].down + 1 >= tc)continue;
        int dist = find_dist(san[i].r, san[i].c, rr, rc), dir = -1;
        for (int d = 0; d < 4; ++d) {
            int nx = san[i].r + dx[d];
            int ny = san[i].c + dy[d];
            if (!is_range(nx, ny))continue;
            if (grid[nx][ny] > 0)continue;
            int tdist = find_dist(nx, ny, rr, rc);
            if (tdist < dist) {
                dist = tdist;
                dir = d;
            }
        }
        if (dir == -1)continue;
        grid[san[i].r][san[i].c] = 0;
        san[i].r += dx[dir];
        san[i].c += dy[dir];
        if (grid[san[i].r][san[i].c] == -1) {
            san[i].sum += D;
            crash(i, (dir + 2) % 4, D);
        }
        else grid[san[i].r][san[i].c] = i;
    }
}

void check() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> P >> C >> D;
    cin >> rr >> rc;
    rr--, rc--;
    grid[rr][rc] = -1;
    for (int i = 1; i <= P; ++i) {
        int id, a, b;
        cin >> id >> a >> b;
        a--, b--;
        grid[a][b] = id;
        san[id] = { a,b,-1,0 };
    }

    for (tc = 1; tc <= M; ++tc) {
        //cout << "\n"<< tc << " start\n";
        //check();
        ru_moving();
        //cout <<"\nrudorp moving\n";
        //check();
        san_moving();
        //cout << "\nsanta moving\n";
        //check();
        bool is_alive = false;
        for (int i = 1; i <= P; ++i) {
            if (san[i].down != M + 1) {
                is_alive = true;
                san[i].sum += 1;
            }
        }
        if (!is_alive)break;
    }

    for (int i = 1; i <= P; ++i)cout << san[i].sum << " ";

    return 0;
}