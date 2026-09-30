#include <iostream>

using namespace std;

int n;
int dp[1001] = { 0,1,2, };

int structure_fill(int line) {
    if (line <= 0)return 0;
    if (dp[line] == -1)dp[line] = (structure_fill(line - 1) + structure_fill(line - 2))%10007;
    return dp[line];
}

int main() {
    cin >> n;

    // Please write your code here.
    for (int i =3; i <= n; ++i) {
        dp[i] = -1;
    }
    cout << structure_fill(n);

    return 0;
}
