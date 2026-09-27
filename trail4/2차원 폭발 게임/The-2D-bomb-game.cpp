#include <iostream>
#include <algorithm>

using namespace std;

int N, M, K;
int numbers_2d[101][101];

int count_bombs() {
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (numbers_2d[i][j] != 0)ans++;
        }
    }
    return ans;
}

void bomb() {
    for (int j = 0; j < N; ++j) {
        bool is_bomb = true;
        while (is_bomb) {
            is_bomb = false;
            int prev = numbers_2d[0][j];
            int cnt = 1;
            for (int i = 1; i < N; ++i) {
                if (numbers_2d[i][j] == 0)continue;
                if (prev != numbers_2d[i][j]) {
                    if (cnt >= M) {
                        for (int k = 1; k <= cnt; ++k) {
                            numbers_2d[i - k][j] = 0;
                        }
                        is_bomb = true;
                    }
                    prev = numbers_2d[i][j];
                    cnt = 1;
                }
                else {
                    cnt++;
                }
            }
            if (cnt >= M) {
                if (!(cnt == 1 && prev == 0)) {
                    for (int k = 1; k <= cnt; ++k) {
                        numbers_2d[N - k][j] = 0;
                    }
                    is_bomb = true;
                }
            }
            if (!is_bomb)break;

            int tmp[101] = { 0, };
            int tcnt = N - 1;
            for (int i = N - 1; i >= 0; --i) {
                if (numbers_2d[i][j] == 0)continue;
                tmp[tcnt--] = numbers_2d[i][j];
            }
            for (int i = 0; i < N; ++i) {
                numbers_2d[i][j] = tmp[i];
            }
        }
    }
}

void rotate() {
    int tmp[100][100] = { 0, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            tmp[j][N - 1 - i] = numbers_2d[i][j];
        }
    }
    for (int j = 0; j < N; ++j) {
        int tcnt = N - 1;
        for (int i = N - 1; i >= 0; --i) {
            if (tmp[i][j] == 0)continue;
            numbers_2d[tcnt--][j] = tmp[i][j];
        }
        for (int i = tcnt; i >= 0; --i) {
            numbers_2d[i][j] = 0;
        }
    }
}

int main() {
    cin >> N >> M >> K;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> numbers_2d[i][j];
        }
    }

    // Please write your code here.
    if (N)
        for (int i = 0; i < K; ++i) {
            bomb();
            rotate();
        }
    bomb();
    cout << count_bombs() << "\n";

    return 0;
}
