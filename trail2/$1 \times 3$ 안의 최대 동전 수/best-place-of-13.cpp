#include <iostream>

using namespace std;

int N;
int grid[20][20];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) cin >> grid[i][j];

    // Please write your code here.
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int tmp = grid[i][0] + grid[i][1] + grid[i][2];
        ans = ans < tmp ? tmp : ans;
        for (int j = 1; j < N - 2; ++j) {
            tmp = tmp - grid[i][j - 1] + grid[i][j + 2];
            ans = ans < tmp ? tmp : ans;
        }
        if (ans == 3)break;
    }
    cout << ans;

    return 0;
}