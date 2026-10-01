#include <iostream>
#include <algorithm>

using namespace std;

int n;
int grid[100][100];
int value[100][100];
int ans = 101;

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    for (int small = 1; small <= 100; ++small) {
        if (small > min(grid[0][0], grid[n - 1][n - 1]))continue;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] < small) {
                    value[i][j] = 101;
                    continue;
                }
                if (i == 0) {
                    if (j == 0) value[i][j] = grid[i][j];
                    else value[i][j] = max(value[i][j - 1], grid[i][j]);
                }
                else {
                    if (j == 0) value[i][j] = max(value[i - 1][j], grid[i][j]);
                    else value[i][j] = max(grid[i][j], min(value[i - 1][j], value[i][j - 1]));
                }
            }
        }
        if (value[n - 1][n - 1] == 101)continue;
        if (value[n - 1][n - 1] - small < ans)ans = value[n - 1][n - 1] - small;
    }
    cout << ans;

    return 0;
}
