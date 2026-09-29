#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Microbe {
    int id;
    int size;
    vector<pair<int, int> > shape; // (0, 0) 기준 상대 좌표

    bool operator<(const Microbe& other) const {
        if (size != other.size) return size < other.size; // 넓이 큰 순
        return id > other.id;                            // 투입 빠른 순
    }
};

int N, Q;
int board[20][20];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

// 1. 미생물 투입 및 영역 분리 검사
void add_mi(int id, int r1, int c1, int r2, int c2) {
    unordered_set<int> touched;

    // 영역 덮어쓰기
    for (int i = r1; i < r2; ++i) {
        for (int j = c1; j < c2; ++j) {
            if (board[i][j] != 0 && board[i][j] != id) {
                touched.insert(board[i][j]);
            }
            board[i][j] = id;
        }
    }

    // 피해를 입은 미생물들이 2개 이상의 영역으로 쪼개졌는지 BFS 검사
    for (unordered_set<int>::iterator it = touched.begin(); it != touched.end(); ++it) {
        int target = *it;
        int comp_count = 0;
        bool visited[20][20] = {false};

        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (board[i][j] == target && !visited[i][j]) {
                    comp_count++;
                    queue<pair<int, int> > q;
                    q.push(make_pair(i, j));
                    visited[i][j] = true;

                    while (!q.empty()) {
                        pair<int, int> cur = q.front();
                        q.pop();
                        int cx = cur.first;
                        int cy = cur.second;

                        for (int d = 0; d < 4; ++d) {
                            int nx = cx + dx[d];
                            int ny = cy + dy[d];
                            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
                            if (!visited[nx][ny] && board[nx][ny] == target) {
                                visited[nx][ny] = true;
                                q.push(make_pair(nx, ny));
                            }
                        }
                    }
                }
            }
        }

        // 영역이 2개 이상으로 분리되었다면 완전히 소멸
        if (comp_count >= 2) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    if (board[i][j] == target) board[i][j] = 0;
                }
            }
        }
    }
}

// 2. 배양 용기 이동
void move() {
    // 현재 보드에 존재하는 모든 미생물의 셀 수집
    vector<pair<int, int> > cells[55];
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] > 0) {
                cells[board[i][j]].push_back(make_pair(i, j));
            }
        }
    }

    priority_queue<Microbe> pq;
    for (int i = 1; i <= Q; ++i) {
        if (cells[i].empty()) continue;

        int min_r = 1e9, min_c = 1e9;
        for (size_t k = 0; k < cells[i].size(); ++k) {
            min_r = min(min_r, cells[i][k].first);
            min_c = min(min_c, cells[i][k].second);
        }

        vector<pair<int, int> > shape;
        for (size_t k = 0; k < cells[i].size(); ++k) {
            shape.push_back(make_pair(cells[i][k].first - min_r, cells[i][k].second - min_c));
        }
        Microbe m;
        m.id = i;
        m.size = (int)cells[i].size();
        m.shape = shape;
        pq.push(m);
    }

    int temp[20][20] = {0};

    while (!pq.empty()) {
        Microbe cur = pq.top();
        pq.pop();

        int best_r = -1, best_c = -1;
        bool placed = false;

        // x(행) 작은 순 -> y(열) 작은 순 탐색
        for (int r = 0; r < N && !placed; ++r) {
            for (int c = 0; c < N && !placed; ++c) {
                bool can_place = true;

                for (size_t s = 0; s < cur.shape.size(); ++s) {
                    int nr = r + cur.shape[s].first;
                    int nc = c + cur.shape[s].second;
                    if (nr < 0 || nr >= N || nc < 0 || nc >= N || temp[nr][nc] != 0) {
                        can_place = false;
                        break;
                    }
                }

                if (can_place) {
                    best_r = r;
                    best_c = c;
                    placed = true;
                }
            }
        }

        // 배치 가능한 경우에만 새 보드에 기록 (불가능하면 자연 소멸)
        if (placed) {
            for (size_t s = 0; s < cur.shape.size(); ++s) {
                temp[best_r + cur.shape[s].first][best_c + cur.shape[s].second] = cur.id;
            }
        }
    }

    // 새 보드로 교체
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = temp[i][j];
        }
    }
}

// 3. 실험 결과 점수 계산
int get_score() {
    int area[55] = {0};
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] > 0) area[board[i][j]]++;
        }
    }

    bool checked[55][55] = {false};
    int total_score = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] == 0) continue;
            int u = board[i][j];

            for (int d = 0; d < 4; ++d) {
                int ni = i + dx[d];
                int nj = j + dy[d];
                if (ni < 0 || ni >= N || nj < 0 || nj >= N) continue;
                if (board[ni][nj] == 0) continue;

                int v = board[ni][nj];
                if (u != v && !checked[u][v]) {
                    checked[u][v] = checked[v][u] = true;
                    total_score += area[u] * area[v];
                }
            }
        }
    }

    return total_score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;
    for (int tc = 1; tc <= Q; ++tc) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        add_mi(tc, r1, c1, r2, c2);
        move();
        cout << get_score() << "\n";
    }

    return 0;
}