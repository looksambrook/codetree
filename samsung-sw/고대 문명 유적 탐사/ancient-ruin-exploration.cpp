#include <iostream>
#include <queue>

using namespace std;

int K, M;
int grid[5][5];
queue<int> numq;
int dx[] = { -1,0,1,0 };
int dy[] = { 0,-1,0,1 };

bool is_range(int x, int y) {
    return x >= 0 && x < 5
        && y >= 0 && y < 5;
}

void rotation(int x, int y) {
    int temp[3][3] = { 0,0 };
    int tmp[3][3] = { 0,0 };
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i][j] = grid[x - 1 + i][y - 1 + j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            tmp[j][2 - i] = temp[i][j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j)
            grid[x - 1 + i][y - 1 + j] = tmp[i][j];
    }
}

int cal() {
    int tmp = 0;
    bool visited[5][5] = { false, };
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (visited[i][j])continue;
            visited[i][j] = true;
            if (grid[i][j] == 0)continue;
            queue<pair<int, int>> list;
            list.push({ i,j });
            int relay = 0;

            while (!list.empty()) {
                int cx = list.front().first;
                int cy = list.front().second;
                relay++;
                list.pop();

                for (int d = 0; d < 4; ++d) {
                    int nx = cx + dx[d];
                    int ny = cy + dy[d];
                    if (!is_range(nx, ny) || visited[nx][ny])continue;
                    if (grid[i][j] != grid[nx][ny])continue;
                    visited[nx][ny] = true;
                    list.push({ nx,ny });
                }
            }
            if (relay >= 3)tmp += relay;
        }
    }
    return tmp;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> K >> M;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < M; ++i) {
        int tmp;
        cin >> tmp;
        numq.push(tmp);
    }

    for (int tc = 0; tc < K; ++tc) {
        int ans = 0, tmp = 0, temp[3][5][5] = { 0, }, large[3] = { 0, };
        //step 1
        for (int j = 1; j < 4; ++j) {
            for (int i = 1; i < 4; ++i) {
                for (int d = 0; d < 3; ++d) {
                    rotation(i, j);
                    int tcnt = cal();
                    if (large[d] < tcnt) {
                        large[d] = tcnt;
                        //cout << i << ", " << j << " / " << d << ", " << large[d] << " check\n";
                        for (int p = 0; p < 5; ++p) {
                            for (int q = 0; q < 5; ++q) {
                                temp[d][p][q] = grid[p][q];
                            }
                        }
                    }
                }
                rotation(i, j);
            }
        }
        for (int d = 0; d < 3; ++d) {
            if (large[tmp] < large[d])tmp = d;
        }
        //cout << tmp << "\n";
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                grid[i][j] = temp[tmp][i][j];
                //cout << grid[i][j] << " ";
            }
            //cout << "\n";
        }

        //step 2
        tmp = large[tmp];
        while (tmp != 0) {
            tmp = 0;
            bool visited[5][5] = { false, };
            for (int j = 0; j < 5; ++j) {
                for (int i = 0; i < 5; ++i) {
                    if (visited[i][j])continue;
                    visited[i][j] = true;
                    if (grid[i][j] == 0)continue;
                    int relay = 0;
                    queue<pair<int, int>> list;
                    list.push({ i,j });

                    while (!list.empty()) {
                        int cx = list.front().first;
                        int cy = list.front().second;
                        relay++;
                        if (relay >= 3)break;
                        list.pop();

                        for (int d = 0; d < 4; ++d) {
                            int nx = cx + dx[d];
                            int ny = cy + dy[d];
                            if (!is_range(nx, ny) || visited[nx][ny])continue;
                            if (grid[i][j] != grid[nx][ny] || grid[nx][ny] == 0)continue;
                            visited[nx][ny] = true;
                            list.push({ nx,ny });
                        }
                    }
                    //3개 이상일때,
                    if (!list.empty()) {
                        queue<pair<int, int>> q;
                        q.push({ i,j });
                        int t = grid[i][j];
                        grid[i][j] = 0;

                        while (!q.empty()) {
                            int x = q.front().first;
                            int y = q.front().second;
                            tmp++;
                            q.pop();

                            for (int d = 0; d < 4; ++d) {
                                int nx = x + dx[d];
                                int ny = y + dy[d];
                                if (!is_range(nx, ny) || t != grid[nx][ny])continue;
                                grid[nx][ny] = 0;
                                q.push({ nx,ny });
                                visited[nx][ny] = true;
                            }
                        }
                    }
                }
            }

            for (int j = 0; j < 5; ++j) {
                for (int i = 4; i >= 0; --i) {
                    if (grid[i][j] == 0) {
                        grid[i][j] = numq.front();
                        numq.pop();
                        numq.push(grid[i][j]);
                    }
                }
            }

            ans += tmp;
        }

        if (ans == 0)break;
        cout << ans << " ";
    }
    return 0;
}