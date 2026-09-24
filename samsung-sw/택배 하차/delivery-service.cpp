#include <iostream>
using namespace std;

struct Info
{
    int r;      // 택배의 맨 위 행 (추가)
    int c;
    int w;
    int h;
    bool alive; // 아직 격자에 남아 있는지 (추가)
};
int N, M, target;
Info box[101];
int board[50][50];

// k번 택배를 더 이상 못 내려갈 때까지 한 칸씩 내린다
void drop(int k) {
    Info& b = box[k];
    while (b.r + b.h < N) {                 // 바로 아래 행이 격자 안일 때만
        int below = b.r + b.h;
        bool can = true;
        for (int j = b.c; j < b.c + b.w; ++j) {
            if (board[below][j] != 0) {     // 아래에 다른 택배가 있으면
                can = false;
                break;
            }
        }
        if (!can) break;

        for (int j = b.c; j < b.c + b.w; ++j) {
            board[b.r][j] = 0;              // 맨 윗줄을 비우고
            board[below][j] = k;            // 한 칸 아래 줄을 채운다
        }
        b.r++;
    }
}

// 남아 있는 모든 택배에 중력 적용
// 아래에 있는 택배(바닥 행 번호가 큰 택배)부터 떨어뜨려야 한 번에 정리된다
void gravity() {
    for (int bottom = N - 1; bottom >= 0; --bottom) {
        for (int k = 1; k <= 100; ++k) {
            if (box[k].alive && box[k].r + box[k].h - 1 == bottom) {
                drop(k);
            }
        }
    }
}

// k번 택배를 격자에서 지운다
void remove_box(int k) {
    for (int i = box[k].r; i < box[k].r + box[k].h; ++i) {
        for (int j = box[k].c; j < box[k].c + box[k].w; ++j) {
            board[i][j] = 0;
        }
    }
    box[k].alive = false;
}

void left_out() {
    int cnt[101] = { 0 };   // cnt[k] : k번 택배가 "왼쪽에서 제일 먼저 보이는" 행의 수
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (board[i][j] != 0) {
                cnt[board[i][j]]++;
                break;
            }
        }
    }
    // 자기 행 h개 모두에서 제일 먼저 보이면 왼쪽으로 뺄 수 있음
    for (int k = 1; k <= 100; ++k) {
        if (box[k].alive && cnt[k] == box[k].h) {
            target = k;     // 번호 작은 것부터 보므로 처음 찾은 게 정답
            break;
        }
    }
    remove_box(target);
}

void right_out() {
    int cnt[101] = { 0 };
    for (int i = 0; i < N; ++i) {
        for (int j = N - 1; j >= 0; --j) {
            if (board[i][j] != 0) {
                cnt[board[i][j]]++;
                break;
            }
        }
    }
    for (int k = 1; k <= 100; ++k) {
        if (box[k].alive && cnt[k] == box[k].h) {
            target = k;
            break;
        }
    }
    remove_box(target);
}

int main() {
    // Please write your code here.
    int k, h, w, c;
    cin >> N >> M;
    for (int i = 0; i < M; ++i) {
        cin >> k >> h >> w >> c;
        c--;
        box[k] = { 0, c, w, h, true };      // 맨 위(0행)에 놓고
        for (int j = 0; j < h; ++j) {
            for (int z = 0; z < w; ++z) {
                board[j][c + z] = k;
            }
        }
        drop(k);                            // 바닥이나 다른 택배에 닿을 때까지 떨어뜨림
    }

    for (int i = 0; i < M; ++i) {
        left_out();
        cout << target << "\n";
        gravity();

        if (i != M - 1) {
            i++;
            right_out();
            cout << target << "\n";
            gravity();
        }
    }

    return 0;
}