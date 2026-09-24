#include <iostream>
#include <climits>

using namespace std;

int n;
int x[100];
int y[100];
int ans = INT_MAX;

void move(int cnt, int sum, int a, int b, bool skip) {
    if (cnt == n - 1) {
        ans = ans > sum ? sum : ans;
        return;
    }
    move(cnt + 1, sum + abs(a - x[cnt + 1]) + abs(b - y[cnt + 1]), x[cnt + 1], y[cnt + 1], skip);
    if (!skip && cnt != n - 2) {
        move(cnt + 1, sum, a, b, true);
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // Please write your code here.
    move(0, 0, x[0], y[0], false);
    cout << ans;

    return 0;
}