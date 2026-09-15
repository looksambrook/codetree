#include <iostream>
#include <queue>
using namespace std;

const int MAX_N = 50;

// 상, 우, 하, 좌
const int dr[4] = {-1, 0, 1, 0};
const int dc[4] = {0, 1, 0, -1};

// 직진, 좌회전, 우회전, 뒤돌기
const int turnOrder[4] = {0, 3, 1, 2};

// BFS 경로 우선순위: 좌, 하, 우, 상
const int searchOrder[4] = {3, 2, 1, 0};

struct State {
    int r;
    int c;
    int dir;
};

int n;
int board[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];

bool canMove(int r, int c) {
    return 0 <= r && r < n &&
           0 <= c && c < n &&
           board[r][c] == 0;
}

// 1단계: 인접한 미방문 바다로 이동
bool moveAdjacent(State& whale) {
    for (int i = 0; i < 4; ++i) {
        int nd = (whale.dir + turnOrder[i]) % 4;
        int nr = whale.r + dr[nd];
        int nc = whale.c + dc[nd];

        if (!canMove(nr, nc) || visited[nr][nc]) continue;

        whale = {nr, nc, nd};
        return true;
    }

    return false;
}

// 2단계: 다음 목적지와 도착 방향 반환
State findNext(const State& whale) {
    bool searched[MAX_N][MAX_N] = {};
    queue<State> q;

    q.push(whale);
    searched[whale.r][whale.c] = true;

    while (!q.empty()) {
        int levelSize = static_cast<int>(q.size());
        State target = {-1, -1, -1};

        // 현재 큐에 있는 같은 거리의 칸들을 모두 처리
        for (int i = 0; i < levelSize; ++i) {
            State current = q.front();
            q.pop();

            for (int j = 0; j < 4; ++j) {
                int nd = searchOrder[j];
                int nr = current.r + dr[nd];
                int nc = current.c + dc[nd];

                if (!canMove(nr, nc) || searched[nr][nc]) continue;
                searched[nr][nc] = true;

                State next = {nr, nc, nd};

                if (!visited[nr][nc]) {
                    // 같은 거리의 후보 중 행, 열이 작은 칸 선택
                    if (target.r == -1 ||
                        nr < target.r ||
                        (nr == target.r && nc < target.c)) {
                        target = next;
                    }
                } else {
                    // 이미 방문한 바다는 통과 가능
                    q.push(next);
                }
            }
        }

        // 같은 거리의 후보를 모두 비교한 뒤 종료
        if (target.r != -1) return target;
    }

    return {-1, -1, -1};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c, inputDir;
    cin >> n >> r >> c >> inputDir;

    // 입력: 1=상, 2=하, 3=좌, 4=우
    // 내부: 0=상, 1=우, 2=하, 3=좌
    const int dirMap[5] = {0, 0, 2, 3, 1};
    State whale = {r - 1, c - 1, dirMap[inputDir]};

    int remaining = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (board[i][j] == 0) ++remaining;
        }
    }

    while (remaining > 0) {
        visited[whale.r][whale.c] = true;
        cout << whale.r + 1 << ' ' << whale.c + 1 << '\n';

        --remaining;
        if (remaining == 0) break;

        if (moveAdjacent(whale)) continue;

        whale = findNext(whale);
        if (whale.r == -1) break;
    }

    return 0;
}