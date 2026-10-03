#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int N, M;
int coin[105];
int dp[10005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> coin[i];
    }

    // DP 테이블 초기화
    for (int i = 1; i <= M; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    // 1원부터 M원까지 최소 동전 개수 갱신
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < N; j++) {
            if (i >= coin[j] && dp[i - coin[j]] != INF) {
                dp[i] = min(dp[i], dp[i - coin[j]] + 1);
            }
        }
    }

    // 도달 불가능하면 -1, 가능하면 최솟값 출력
    if (dp[M] == INF) {
        cout << -1 << "\n";
    } else {
        cout << dp[M] << "\n";
    }

    return 0;
}