#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 1e9;
int n;
int grid[105][105];
int dp[105][105];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int min_val = 100, max_val = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            min_val = min(min_val, grid[i][j]);
            max_val = max(max_val, grid[i][j]);
        }
    }

    int ans = INF;

    // 경로 상의 최솟값 L을 min_val부터 max_val까지 고정
    for (int L = min_val; L <= max_val; L++) {
        // 시작점이나 도착점이 L보다 작으면 이 L을 최솟값으로 삼을 수 없음
        if (grid[0][0] < L || grid[n - 1][n - 1] < L) continue;

        // DP 테이블 초기화 (최댓값을 최소화해야 하므로 INF로 초기화)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = INF;
            }
        }

        dp[0][0] = grid[0][0];

        // 0번째 행 채우기
        for (int j = 1; j < n; j++) {
            if (grid[0][j] < L || dp[0][j - 1] == INF) continue;
            dp[0][j] = max(dp[0][j - 1], grid[0][j]);
        }

        // 0번째 열 채우기
        for (int i = 1; i < n; i++) {
            if (grid[i][0] < L || dp[i - 1][0] == INF) continue;
            dp[i][0] = max(dp[i - 1][0], grid[i][0]);
        }

        // 나머지 칸 채우기
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (grid[i][j] < L) continue;

                int prev_min = min(dp[i - 1][j], dp[i][j - 1]);
                if (prev_min != INF) {
                    dp[i][j] = max(prev_min, grid[i][j]);
                }
            }
        }

        // 목적지에 도달 가능한 경우 차이 갱신
        if (dp[n - 1][n - 1] != INF) {
            ans = min(ans, dp[n - 1][n - 1] - L);
        }
    }

    cout << ans << "\n";

    return 0;
}