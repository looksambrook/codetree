#include <iostream>
#include <queue>
#include <climits>

using namespace std;

struct Info
{
    int x;
    int y;
    int tmp = 0;
};

int N, K, L;
int room[30][30];
Info clean_bot[50];

int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void moving(int num) {
    int cx = clean_bot[num].x;
    int cy = clean_bot[num].y;
    if (room[cx][cy] > 0) return;

    queue<Info> q;
    q.push({ cx,cy,0 });
    bool visited[30][30] = { false, };
    for (int i = 0; i < K; ++i) {
        visited[clean_bot[i].x][clean_bot[i].y] = true;
    }
    Info ans = { N,N,INT_MAX };

    while (!q.empty()) {
        cx = q.front().x;
        cy = q.front().y;
        int cnt = q.front().tmp;
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (!is_range(nx, ny))continue;
            if (visited[nx][ny])continue;
            if (room[nx][ny] == -1)continue;

            visited[nx][ny] = true;
            if (room[nx][ny] == 0)
                q.push({ nx,ny,cnt + 1 });
            else if (ans.tmp == cnt + 1) {
                if (ans.x > nx || (ans.x == nx && ans.y > ny))ans = { nx,ny,cnt + 1 };
            }
            else if (ans.tmp > cnt + 1) {
                ans = { nx,ny,cnt + 1 };
            }
        }
    }
    if (ans.tmp == INT_MAX)return;
    clean_bot[num] = ans;
}

void cleaning(int num) {
    int cx = clean_bot[num].x;
    int cy = clean_bot[num].y;
    int ans = 0;
    int check = -1;
    for (int del = 0; del < 4; ++del) {
        int sum = 0;
        for (int d = 0; d < 4; ++d) {
            if (d == del)continue;
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            if (!is_range(nx, ny))continue;
            if (room[nx][ny] == -1)continue;
            int tmp = room[nx][ny] <= 20 ? room[nx][ny] : 20;
            sum += tmp;
        }
        if (ans < sum) {
            ans = sum;
            check = del;
        }
    }

    room[cx][cy] = room[cx][cy] < 20 ? 0 : room[cx][cy] - 20;
    if (check == -1)return;
    for (int d = 0; d < 4; ++d) {
        if (d == check)continue;
        int nx = cx + dx[d];
        int ny = cy + dy[d];
        if (!is_range(nx, ny))continue;
        if (room[nx][ny] == -1)continue;

        room[nx][ny] = room[nx][ny] < 20 ? 0 : room[nx][ny] - 20;
    }
}

void dusty() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (room[i][j] > 0)
                room[i][j] += 5;
        }
    }
}

void spread() {
    bool visited[30][30] = { false, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (room[i][j] == 0) {
                int sum = 0;
                visited[i][j] = true;
                for (int d = 0; d < 4; ++d) {
                    int nx = i + dx[d];
                    int ny = j + dy[d];
                    if (!is_range(nx, ny))continue;
                    if (visited[nx][ny])continue;
                    if (room[nx][ny] > 0)sum += room[nx][ny];
                }
                room[i][j] = sum / 10;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K >> L;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> room[i][j];
        }
    }
    for (int i = 0; i < K; ++i) {
        int r, c;
        cin >> r >> c;
        clean_bot[i] = { r - 1,c - 1 };
    }

    for (int tc = 1; tc <= L; ++tc) {
        for (int i = 0; i < K; ++i)
            moving(i);
        for (int i = 0; i < K; ++i)
            cleaning(i);
        dusty();
        spread();

        int sum = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (room[i][j] > 0)sum += room[i][j];
            }
        }
        cout << sum << "\n";
    }
    return 0;
}