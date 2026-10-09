#include <iostream>
#include <queue>

using namespace std;

struct Info {
    int x, y, d;
};

int N, M;
Info curr;
int grid[21][21];
int score[21][21] = { 0, };
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
int dir[4][3] = { {3,0,1},{0,1,2},{1,2,3},{2,3,0} };
int dice[6] = { 1,2,3,5,4,6 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void score_init() {
    bool visited[21][21] = { false, };
    queue<pair<int, int>> temp;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (visited[i][j])continue;
            queue<pair<int, int>> q;
            q.push({ i,j });
            temp.push({ i,j });
            visited[i][j] = true;
            int cnt = 0;
            while (!q.empty()) {
                int cx = q.front().first;
                int cy = q.front().second;
                cnt += 1;
                q.pop();

                for (int d = 0; d < 4; ++d) {
                    int nx = cx + dx[d];
                    int ny = cy + dy[d];
                    if (!is_range(nx, ny) || visited[nx][ny])continue;
                    if (grid[i][j] == grid[nx][ny]) {
                        q.push({ nx,ny });
                        temp.push({ nx,ny });
                        visited[nx][ny] = true;
                    }
                }
            }
            while (!temp.empty()) {
                score[temp.front().first][temp.front().second] = grid[i][j] * cnt;
                temp.pop();
            }
        }
    }
}

void dice_moving() {
    int temp[6] = {};
    if (curr.d == 0) {
        temp[0] = dice[4], temp[1] = dice[1], temp[2] = dice[0], temp[3] = dice[3], temp[4] = dice[5], temp[5] = dice[2];
    }
    else if (curr.d == 1) {
        temp[0] = dice[3], temp[1] = dice[0], temp[2] = dice[2], temp[3] = dice[5], temp[4] = dice[4], temp[5] = dice[1];
    }
    else if (curr.d == 2) {
        temp[0] = dice[2], temp[1] = dice[1], temp[2] = dice[5], temp[3] = dice[3], temp[4] = dice[0], temp[5] = dice[4];
    }
    else if (curr.d == 3) {
        temp[0] = dice[1], temp[1] = dice[5], temp[2] = dice[2], temp[3] = dice[0], temp[4] = dice[4], temp[5] = dice[3];
    }
    for (int i = 0; i < 6; ++i)dice[i] = temp[i];
}

void moving() {
    if (dice[5] < grid[curr.x][curr.y]) {
        int tmp_d = (curr.d + 3) % 4;
        int nx = curr.x + dx[tmp_d];
        int ny = curr.y + dy[tmp_d];
        if (!is_range(nx, ny)) {
            tmp_d = (tmp_d + 2) % 4;
            nx = curr.x + dx[tmp_d];
            ny = curr.y + dy[tmp_d];
        }
        curr = { nx,ny,tmp_d };
    }
    else if (dice[5] == grid[curr.x][curr.y]) {
        int tmp_d = curr.d;
        int nx = curr.x + dx[tmp_d];
        int ny = curr.y + dy[tmp_d];
        if (!is_range(nx, ny)) {
            tmp_d = (tmp_d + 2) % 4;
            nx = curr.x + dx[tmp_d];
            ny = curr.y + dy[tmp_d];
        }
        curr = { nx,ny,tmp_d };
    }
    else {
        int tmp_d = (curr.d + 1) % 4;
        int nx = curr.x + dx[tmp_d];
        int ny = curr.y + dy[tmp_d];
        if (!is_range(nx, ny)) {
            tmp_d = (tmp_d + 2) % 4;
            nx = curr.x + dx[tmp_d];
            ny = curr.y + dy[tmp_d];
        }
        curr = { nx,ny,tmp_d };
    }

    dice_moving();
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
    score_init();
    
    int result = 0;
    for (int test_case = 1; test_case <= M; ++test_case) {
        if (test_case == 1) {
            curr = { 0,1,0 };
            dice_moving();
        }
        else moving();
        result += score[curr.x][curr.y];
    }
    cout << result;

    return 0;
}