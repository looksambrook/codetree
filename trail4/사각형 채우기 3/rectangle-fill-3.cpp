#include <iostream>

using namespace std;

int n;
long long dp[1001] = { 1,2,7,22,};
long long sum[1001] = { 0,0,0,1,3,10,};

long long func(int x) {
    if (dp[x] == -1)dp[x] = (func(x - 2) * 3 + func(x - 1) * 2 + 2 * sum[x]) % 1000000007;
    sum[x+3] = (sum[x+2] + dp[x]) % 1000000007;
    return dp[x];
}

int main() {
    cin >> n;

    // Please write your code here.
    for (int i = 3; i <= n; ++i) {
        dp[i] = -1;
        sum[i] = -1;
    }
    sum[3]=1;
    cout << func(n);

    return 0;
}
