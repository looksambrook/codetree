#include <iostream>
#include <queue>
#include <utility>
using namespace std;

const int MAX_N = 50;

// 상, 우, 하, 좌
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

// 직진, 좌회전, 우회전, 뒤돌기
const int turnOrder[4] = {0, 3, 1, 2};

// BFS 경로 우선순위: 좌, 하, 우, 상
const int pathOrder[4] = {3, 2, 1, 0};

int n;
int board[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

int dist[MAX_N][MAX_N];
int enterDir[MAX_N][MAX_N];

bool canMove(int r, int c) {
    return 0 <= r && r < n &&
           0 <= c && c < n &&
           board[r][c] == 0;
}

void bfs(int sr, int sc) {
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            dist[r][c] = -1;
            enterDir[r][c] = -1;
        }
    }

    queue<pair<int, int>> q;
    q.push({sr, sc});
    dist[sr][sc] = 0;

    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        // 같은 길이의 경로는 좌, 하, 우, 상 순서를 따른다.
        for (int nd : pathOrder) {
            int nr = r + dr[nd];
            int nc = c + dc[nd];

            if (!canMove(nr, nc)) continue;
            if (dist[nr][nc] != -1) continue;

            dist[nr][nc] = dist[r][c] + 1;
            enterDir[nr][nc] = nd;
            q.push({nr, nc});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, inputDir;
    cin >> n >> r >> c >> inputDir;
    --r;
    --c;

    // 입력: 1=상, 2=하, 3=좌, 4=우
    // 내부: 0=상, 1=우, 2=하, 3=좌
    const int dirMap[5] = {0, 0, 2, 3, 1};
    int dir = dirMap[inputDir];

    int remaining = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 0) ++remaining;
        }
    }

    while (remaining > 0) {
        visited[r][c] = true;
        cout << r + 1 << ' ' << c + 1 << '\n';

        --remaining;
        if (remaining == 0) break;

        // 1단계: 인접한 미방문 바다로 이동
        bool moved = false;

        for (int turn : turnOrder) {
            int nd = (dir + turn) % 4;
            int nr = r + dr[nd];
            int nc = c + dc[nd];

            if (!canMove(nr, nc)) continue;
            if (visited[nr][nc]) continue;

            r = nr;
            c = nc;
            dir = nd;
            moved = true;
            break;
        }

        if (moved) continue;

        // 2단계: BFS 한 번으로 거리와 도착 방향 계산
        bfs(r, c);

        int targetR = -1;
        int targetC = -1;
        int bestDist = n * n + 1;

        // 행, 열 오름차순으로 확인한다.
        // 같은 거리에서는 먼저 선택한 후보를 유지한다.
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (visited[i][j] || dist[i][j] == -1) continue;

                if (dist[i][j] < bestDist) {
                    bestDist = dist[i][j];
                    targetR = i;
                    targetC = j;
                }
            }
        }

        if (targetR == -1) break;

        r = targetR;
        c = targetC;
        dir = enterDir[r][c];
    }

    return 0;
}