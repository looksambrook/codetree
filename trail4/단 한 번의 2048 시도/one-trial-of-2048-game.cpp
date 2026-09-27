#include <iostream>

using namespace std;

int grid[4][4];
char dir;

int main() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> dir;

    // Please write your code here.
    if (dir == 'R') {
        for (int i = 0; i < 4; ++i) {
            int prev = 3;
            //same->plus and zero
            for (int j = 2; j >= 0; --j) {
                if (grid[i][j] == 0)continue;
                if (grid[i][prev] == grid[i][j]) {
                    grid[i][prev] *= 2;
                    grid[i][j] = 0;
                }
                prev = j;
            }
            //gravity
            int tmp[4] = { 0, };
            int tcnt = 3;
            for (int j = 3; j >= 0; --j) {
                if (grid[i][j] == 0)continue;
                tmp[tcnt--] = grid[i][j];
            }
            for (int j = 0; j < 4; ++j)
                grid[i][j] = tmp[j];
        }
    }
    else if (dir == 'D') {
        for (int j = 0; j < 4; ++j) {
            int prev = 3;
            //same->plus and zero
            for (int i = 2; i >= 0; --i) {
                if (grid[i][j] == 0)continue;
                if (grid[prev][j] == grid[i][j]) {
                    grid[prev][j] *= 2;
                    grid[i][j] = 0;
                }
                prev = i;
            }
            //gravity
            int tmp[4] = { 0, };
            int tcnt = 3;
            for (int i = 3; i >= 0; --i) {
                if (grid[i][j] == 0)continue;
                tmp[tcnt--] = grid[i][j];
            }
            for (int i = 0; i < 4; ++i)
                grid[i][j] = tmp[i];
        }
    }
    else if (dir == 'L') {
        for (int i = 0; i < 4; ++i) {
            int prev = 0;
            //same->plus and zero
            for (int j = 1; j < 4; ++j) {
                if (grid[i][j] == 0)continue;
                if (grid[i][prev] == grid[i][j]) {
                    grid[i][prev] *= 2;
                    grid[i][j] = 0;
                }
                prev = j;
            }
            //gravity
            int tmp[4] = { 0, };
            int tcnt = 0;
            for (int j = 0; j < 4; ++j) {
                if (grid[i][j] == 0)continue;
                tmp[tcnt++] = grid[i][j];
            }
            for (int j = 0; j < 4; ++j)
                grid[i][j] = tmp[j];
        }
    }
    else if (dir == 'U') {
        for (int j = 0; j < 4; ++j) {
            int prev = 0;
            //same->plus and zero
            for (int i = 1; i < 4; ++i) {
                if (grid[i][j] == 0)continue;
                if (grid[prev][j] == grid[i][j]) {
                    grid[prev][j] *= 2;
                    grid[i][j] = 0;
                }
                prev = i;
            }

            //gravity
            int tmp[4] = { 0, };
            int tcnt = 0;
            for (int i = 0; i < 4; ++i) {
                if (grid[i][j] == 0)continue;
                tmp[tcnt++] = grid[i][j];
            }
            for (int i = 0; i < 4; ++i)
                grid[i][j] = tmp[i];
        }
    }

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
