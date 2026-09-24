#include <iostream>
#include <string>

using namespace std;

int N, M;
string arr[50];
int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
int dy[8] = { 1,1,0,-1,-1,-1,0,1 };

int main() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    // Please write your code here.
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            if (arr[i][j] != 'L')continue;
            for (int d = 0; d < 8; ++d) {
                bool is_ans = true;
                for (int k = 1; k < 3; ++k) {
                    if ((i + dx[d] * k) < 0 || (i + dx[d] * k) >= N || (j + dy[d] * k) < 0 || (j + dy[d] * k) >= M) {
                        is_ans = false;
                        k = 3;
                        break;
                    }
                    if (arr[i + dx[d] * k][j + dy[d] * k] != 'E') {
                        is_ans = false;
                        k = 3;
                        break;
                    }
                }
                if (is_ans)
                    ans++;
            }
        }
    }
    cout << ans;

    return 0;
}