#include <iostream>
#include <algorithm>

using namespace std;

int n;
int grid[100][100];
int value[100][100];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= 0; --j) {
            if (i == 0) {
                if (j != n - 1)grid[i][j] += grid[i][j + 1];
            }
            else {
                if (j == n - 1)grid[i][j] += grid[i - 1][j];
                else grid[i][j] += min(grid[i - 1][j], grid[i][j + 1]);
            }
        }
    }
    cout << grid[n - 1][0];

    return 0;
}
