#include <iostream>
#include <queue>

using namespace std;

int N, cr, cc, cd, K;
int grid[51][51];
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int dm[4][4] = {
    {0,2,3,1},
    {1,3,2,1},
    {2,1,0,3},
    {3,0,1,2}
};
int ds[] = { 2,1,3,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> cr >> cc >> cd;
    cr--, cc--, cd--;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
            grid[i][j] *= -1;
            if (grid[i][j] == 0)K++;
        }
    }

    for (int tc = 1; tc <= K; ++tc) {
        cout << cr + 1 << " " << cc + 1 << "\n";
        if (tc == K)continue;
        grid[cr][cc] = tc;
        bool is_move = false;
        for (int d = 0; d < 4; ++d) {
            int nx = cr + dx[dm[cd][d]];
            int ny = cc + dy[dm[cd][d]];
            if (!is_range(nx, ny) || grid[nx][ny] != 0)continue;
            is_move = true;
            cr = nx;
            cc = ny;
            cd = dm[cd][d];
            break;
        }
        if (is_move)continue;

        queue<pair<int, int>> q;
        int visited[52][52] = { 0, };
        int tx = 51, ty = 51, td = cd;
        q.push({ cr,cc });
        visited[cr][cc] = 1;
        visited[tx][ty] = 3000;
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            for (int d = 0; d < 4; ++d) {
                int nx = r + dx[ds[d]];
                int ny = c + dy[ds[d]];
                if (!is_range(nx, ny) || visited[nx][ny] != 0 || grid[nx][ny] < 0)continue;
                visited[nx][ny] = visited[r][c] + 1;
                if (visited[tx][ty] < visited[nx][ny])continue;
                if (grid[nx][ny] == 0) {
                    if (visited[nx][ny] == visited[tx][ty]) {
                        if (tx == nx) {
                            if (ty > ny) {
                                ty = ny, td = ds[d];
                            }
                        }
                        else if (tx > nx) {
                            tx = nx, ty = ny, td = ds[d];

                        }
                    }
                    else if (visited[nx][ny] < visited[tx][ty]) {
                        tx = nx, ty = ny, td = ds[d];
                    }
                }
                else q.push({ nx,ny });
            }
        }
        cr = tx, cc = ty, cd = td;
    }

    return 0;
}