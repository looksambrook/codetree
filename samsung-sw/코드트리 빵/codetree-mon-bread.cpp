#include <iostream>
#include <queue>

using namespace std;

struct Info {
    int x, y;
    int tx, ty;
    int done;
};

int N, M;
int grid[20][20] = { 0, };
int test_case = 0;
Info person[35];
int dx[] = { -1,0,0,1 };
int dy[] = { 0,-1,1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void moving() {
    int stan;
    if (test_case <= M)stan = test_case;
    else stan = M + 1;
    for (int p = 1; p < stan; ++p) {
        if (person[p].done != 0)continue;
        bool visited[20][20] = { false, };
        queue<Info> q;
        for (int d = 0; d < 4; ++d) {
            int nx = person[p].x + dx[d];
            int ny = person[p].y + dy[d];
            if (!is_range(nx, ny))continue;
            if (grid[nx][ny] < 0)continue;
            visited[nx][ny] = true;
            q.push({ nx, ny, d });
        }

        while (!q.empty()) {
            int cx = q.front().x;
            int cy = q.front().y;
            int cd = q.front().tx;
            if (cx == person[p].tx && cy == person[p].ty) break;
            q.pop();

            for (int d = 0; d < 4; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (!is_range(nx, ny) || visited[nx][ny])continue;
                if (grid[nx][ny] < 0)continue;
                visited[nx][ny] = true;
                q.push({ nx, ny, cd });
            }
        }

        person[p].x += dx[q.front().tx];
        person[p].y += dy[q.front().tx];
    }
}

bool check() {
    bool is_done = true;
    int stan;
    if (test_case <= M) {
        stan = test_case;
        is_done = false;
    }
    else stan = M + 1;
    for (int p = 1; p < stan; ++p) {
        if (person[p].done != 0)continue;
        if (person[p].x == person[p].tx && person[p].y == person[p].ty) {
            person[p].done = test_case;
            grid[person[p].x][person[p].y] = -1;
        }
        is_done = false;
    }
    return is_done;
}

void init(int id) {
    Info ans = { N,N,300 };
    queue<Info> q;
    bool visited[20][20] = { false, };
    q.push({ person[id].tx,person[id].ty,0 });
    visited[person[id].tx][person[id].ty] = true;

    while (!q.empty()) {
        int cx = q.front().x;
        int cy = q.front().y;
        int cd = q.front().tx;
        q.pop();

        if (grid[cx][cy] == 1) {
            if ((cd < ans.tx) || (cd == ans.tx && (cx < ans.x || (cx == ans.x && cy == ans.y)))) {
                ans = { cx,cy,cd };
            }
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (!is_range(nx, ny) || visited[nx][ny])continue;
            if (grid[nx][ny] < 0)continue;
            if (cd + 1 > ans.tx)break;
            visited[nx][ny] = true;
            q.push({ nx,ny,cd + 1 });
        }
    }

    grid[ans.x][ans.y] = -1;
    person[id].x = ans.x;
    person[id].y = ans.y;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < M; ++i) {
        int r, c;
        cin >> r >> c;
        grid[r - 1][c - 1] = 2;
        person[i + 1] = { 0,0,r - 1,c - 1,0 };
    }

    for (test_case = 1;; ++test_case) {
        moving();
        if (check()) {
            cout << test_case - 1;
            break;
        }
        if (test_case <= M) init(test_case);
    }

    return 0;
}