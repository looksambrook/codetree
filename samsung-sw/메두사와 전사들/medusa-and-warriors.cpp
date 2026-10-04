#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Info
{
    int x;
    int y;
};

int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int N, M;
int sx, sy, ex, ey;
bool grid[51][51];
int visited[51][51];
int ans[3];
vector<Info> soldier;
vector<Info> route;

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void check(int x, int y) {
    Info parent[51][51] = {{0,0},};
    queue<Info> q;
    q.push({ x,y });
    visited[x][y] = 1;
    parent[x][y] = { x,y };
    while (!q.empty()) {
        int cx = q.front().x;
        int cy = q.front().y;
        q.pop();

        if (cx == ex && cy == ey)break;

        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (is_range(nx, ny) && visited[nx][ny] == 0 && grid[nx][ny] == 0) {
                visited[nx][ny] = visited[cx][cy] + 1;
                parent[nx][ny] = { cx,cy };
                q.push({ nx,ny });
            }
        }
    }
    route.resize(visited[ex][ey]);
    if (route.size() == 0)return;
    route.back() = {ex, ey};
    int a = ex, b = ey;
    for (int i = visited[ex][ey] - 1; i > 0; --i) {
        route[i-1] = parent[a][b];
        a = route[i-1].x, b = route[i-1].y;
    }
}

void me_moving() {
    for (int i = 0; i < soldier.size(); ++i) {
        if (soldier[i].x == sx && soldier[i].y == sy) {
            soldier.erase(soldier.begin() + i);
            i--;
        }
    }
}

void watching() {
    //시선
    bool watch_board[5][51][51] = { false, };
    int soldier_count[51][51] = {};
    int unable = 0;
    int cnt = -1;//tmp중 max가 ans[1],unable
    //각 방향마다 영향 받는 전사는 벡터에 저장 - 메두사가 보고 있는 곳은 watch_board로 확인
    for (int i = 0; i < soldier.size(); ++i) {
        watch_board[4][soldier[i].x][soldier[i].y] = true;
        soldier_count[soldier[i].x][soldier[i].y]++;
    }
    for (int d = 0; d < 4; ++d) {
        if (d == 0) {
            int tmp = 0;
            for (int i = sx - 1; i >= 0; --i) {
                for (int j = sy - sx + i; j <= sy + sx - i; ++j) {
                    if (!is_range(i, j))continue;
                    watch_board[d][i][j] = true;
                    tmp += soldier_count[i][j];
                    if (sx - 1 == i)continue;
                    if (j < sy) {
                        if (!is_range(i + 1, j + 1))continue;
                        if (j+1!=sy && (watch_board[d][i + 1][j + 1] == false || watch_board[4][i + 1][j + 1]))watch_board[d][i][j] = false;
                        if (j != sy - sx + i) {
                            if (watch_board[d][i + 1][j] == false|| watch_board[4][i + 1][j])watch_board[d][i][j] = false;
                        }
                    }
                    else if (j == sy) {
                        if (!is_range(i + 1, j))continue;
                        if (watch_board[d][i + 1][j] == false || watch_board[4][i + 1][j])watch_board[d][i][j] = false;
                    }
                    else {
                        if (!is_range(i + 1, j - 1))continue;
                        if (j - 1 != sy && (watch_board[d][i + 1][j - 1] == false || watch_board[4][i + 1][j - 1]))watch_board[d][i][j] = false;
                        if (j != sy + sx - i) {
                            if (watch_board[d][i + 1][j] == false||watch_board[4][i+1][j])watch_board[d][i][j] = false;
                        }
                    }

                    if (!watch_board[d][i][j])tmp -= soldier_count[i][j];
                }
            }
            if (cnt < tmp) {
                cnt = tmp;
                unable = d;
            }
        }
        if (d == 1) {
            int tmp = 0;
            for (int i = sx + 1; i < N; ++i) {
                for (int j = sy + sx - i; j <= sy - sx + i; ++j) {
                    if (!is_range(i, j))continue;
                    //cout << "check: " << i << ", " << j << " / " << watch_board[4][i][j] << "\n";
                    watch_board[d][i][j] = true;
                    tmp += soldier_count[i][j];
                    if (sx + 1 == i)continue;
                    if (j < sy) {
                        if (!is_range(i - 1, j + 1))continue;
                        if (j+1!=sy && (watch_board[d][i - 1][j + 1] == false || watch_board[4][i - 1][j + 1]))watch_board[d][i][j] = false;
                        if (j != sy + sx - i) {
                            if (watch_board[d][i - 1][j] == false || watch_board[4][i - 1][j])watch_board[d][i][j] = false;
                        }
                    }
                    else if (j == sy) {
                        if (!is_range(i - 1, j))continue;
                        if (watch_board[d][i - 1][j] == false || watch_board[4][i - 1][j])watch_board[d][i][j] = false;
                    }
                    else {
                        if (!is_range(i - 1, j - 1))continue;
                        if (j-1!=sy && (watch_board[d][i - 1][j - 1] == false || watch_board[4][i - 1][j - 1]))watch_board[d][i][j] = false;
                        if (j != sy - sx + i) {
                            if (watch_board[d][i - 1][j] == false || watch_board[4][i - 1][j])watch_board[d][i][j] = false;
                        }
                    }
                    if (!watch_board[d][i][j])tmp -= soldier_count[i][j];
                }
            }
            if (cnt < tmp) {
                cnt = tmp;
                unable = d;
            }
        }
        if (d == 2) {
            int tmp = 0;
            for (int j = sy - 1; j >= 0; --j) {
                for (int i = sx - sy + j; i <= sx + sy - j; ++i) {
                    if (!is_range(i, j))continue;
                    watch_board[d][i][j] = true;
                    tmp += soldier_count[i][j];
                    if (sy - 1 == j)continue;
                    if (i < sx) {
                        if (!is_range(i + 1, j + 1))continue;
                        if (i+1!=sx && (watch_board[d][i + 1][j + 1] == false || watch_board[4][i + 1][j + 1]))watch_board[d][i][j] = false;
                        if (i != sx - sy + j) {
                            if (watch_board[d][i][j + 1] == false || watch_board[4][i][j + 1])watch_board[d][i][j] = false;
                        }
                    }
                    else if (i == sx) {
                        if (!is_range(i, j + 1))continue;
                        if (watch_board[d][i][j + 1] == false || watch_board[4][i][j + 1])watch_board[d][i][j] = false;
                    }
                    else {
                        if (!is_range(i - 1, j + 1))continue;
                        if (i-1!=sx && (watch_board[d][i - 1][j + 1] == false || watch_board[4][i - 1][j + 1]))watch_board[d][i][j] = false;
                        if (i != sy + sx - j) {
                            if (watch_board[d][i][j + 1] == false || watch_board[4][i][j + 1])watch_board[d][i][j] = false;
                        }
                    }
                    if (!watch_board[d][i][j])tmp -= soldier_count[i][j];
                }
            }
            if (cnt < tmp) {
                cnt = tmp;
                unable = d;
            }
        }
        if (d == 3) {
            int tmp = 0;
            for (int j = sy + 1; j < N; ++j) {
                for (int i = sx - sy + j; i >= sx + sy - j; --i) {
                    if (!is_range(i, j))continue;
                    watch_board[d][i][j] = true;
                    tmp += soldier_count[i][j];
                    if (sy + 1 == j)continue;
                    if (i < sx) {
                        if (!is_range(i + 1, j - 1))continue;
                        if (i+1!=sx && (watch_board[d][i + 1][j - 1] == false || watch_board[4][i + 1][j - 1]))watch_board[d][i][j] = false;
                        if (i != sx + sy - j) {
                            if (watch_board[d][i][j - 1] == false || watch_board[4][i][j - 1])watch_board[d][i][j] = false;
                        }
                    }
                    else if (i == sx) {
                        if (!is_range(i, j - 1))continue;
                        if (watch_board[d][i][j - 1] == false || watch_board[4][i][j - 1])watch_board[d][i][j] = false;
                    }
                    else {
                        if (!is_range(i - 1, j - 1))continue;
                        if (i-1!=sx && (watch_board[d][i - 1][j - 1] == false || watch_board[4][i - 1][j - 1]))watch_board[d][i][j] = false;
                        if (i != sx - sy + j) {
                            if (watch_board[d][i][j - 1] == false || watch_board[4][i][j - 1])watch_board[d][i][j] = false;
                        }
                    }
                    if (!watch_board[d][i][j])tmp -= soldier_count[i][j];
                }
            }
            if (cnt < tmp) {
                cnt = tmp;
                unable = d;
            }
        }
        /*cout << d << " / "<<sx<<", "<<sy<<" <-check\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << watch_board[d][i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";*/
    }
    ans[1] = cnt;

    //전사 이동
    //cout << "unable: " << unable << "\n";
    for (int i = 0; i < soldier.size(); ++i) {
        //cout << soldier[i].x << ", " << soldier[i].y << "\n";
        if (watch_board[unable][soldier[i].x][soldier[i].y]) {
            continue;
        }
        //cout << "pass\n";
        bool is_dead = false;
        for (int d = 0; d < 4; ++d) {
            int x = soldier[i].x + dx[d];
            int y = soldier[i].y + dy[d];
            if (!is_range(x, y))continue;
            if (watch_board[unable][x][y])continue;
            if ((abs(sx - soldier[i].x) + abs(sy - soldier[i].y)) <= (abs(sx - x) + abs(sy - y))) continue;
            soldier[i].x = x;
            soldier[i].y = y;
            ans[0]++;
            if (sx == x && sy == y) {
                soldier.erase(soldier.begin() + i);
                i--;
                ans[2]++;
                is_dead = true;
            }
            break;
        }
        if (is_dead)continue;
        for (int d = 2; d < 6; ++d) {
            int x = soldier[i].x + dx[d % 4];
            int y = soldier[i].y + dy[d % 4];
            if (!is_range(x, y))continue;
            if (watch_board[unable][x][y])continue;
            if (abs(sx - soldier[i].x) + abs(sy - soldier[i].y) <= abs(sx - x) + abs(sy - y)) continue;
            soldier[i].x = x;
            soldier[i].y = y;
            ans[0]++;
            if (sx == x && sy == y) {
                soldier.erase(soldier.begin() + i);
                i--;
                ans[2]++;
                is_dead = true;
            }
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    cin >> sx >> sy >> ex >> ey;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        soldier.push_back({ a,b });
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> grid[i][j];
        }
    }
    check(sx, sy);
    /*for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << visited[i][j] << " ";
        }
        cout << "\n";
    }*/
    //for (int i = 0; i < route.size(); ++i)cout << route[i].x << ", " << route[i].y << "\n";
    for (int tc = 1; tc+1 < route.size() ; ++tc) {
        ans[0] = 0, ans[1] = 0, ans[2] = 0;
        if (soldier.size()) {
            sx = route[tc].x, sy = route[tc].y;
            me_moving();
            watching();
        }
        for (int i = 0; i < 3; ++i)cout << ans[i] << " ";
        cout << "\n";
    }
    if (route.size() == 0)  cout << -1;
    else cout << 0;

    return 0;
}