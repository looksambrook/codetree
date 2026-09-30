#include <iostream>

using namespace std;

int n;
int dp[1001] = { 0,0,1,1, };
long long ans = 0;

int stairs(int floor) {
    if (floor < 0)return 0;
    if (dp[floor] == -1) dp[floor] = (stairs(floor - 2) + stairs(floor - 3))%10007;

    return dp[floor];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> n;

    // Please write your code here.
    for (int i = 4; i <= n; ++i) {
        dp[i] = -1;
    }
    stairs(n);
    cout << dp[n];

    return 0;
}