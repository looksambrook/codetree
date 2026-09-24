#include <iostream>

using namespace std;

int board[19][19];
int dx[8] = { 1,0,-1,0,1,1,-1,-1 };
int dy[8] = { 0,1,0,-1,1,-1,1,-1 };

int main() {
    for (int i = 0; i < 19; i++)
        for (int j = 0; j < 19; j++) cin >> board[i][j];

    // Please write your code here.
    for (int i = 0; i < 19; ++i) {
        for (int j = 0; j < 19; ++j) {
            if (board[i][j] == 0)continue;
            for (int d = 0; d < 8; ++d) {
                bool is_finish = true;
                for (int k = 1; k < 5; ++k) {
                    if (board[i][j] != board[i + dx[d] * k][j + dy[d] * k]) {
                        is_finish = false;
                    }
                }
                if (is_finish) {
                    cout << board[i][j] << "\n" << i + 1 + dx[d] * 2 << " " << j + 1 + dy[d] * 2;
                    return 0;
                }
            }
        }
    }
    cout<<0;

    return 0;
}