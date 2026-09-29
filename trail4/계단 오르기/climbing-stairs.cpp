#include <iostream>

using namespace std;

int dp[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 초기값 세팅
    dp[0] = 1;
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 1;

    // 4층부터 N층까지 점화식 적용
    for (int i = 4; i <= n; i++) {
        dp[i] = (dp[i - 2] + dp[i - 3]) % 10007;
    }

    cout << dp[n] << "\n";

    return 0;
}