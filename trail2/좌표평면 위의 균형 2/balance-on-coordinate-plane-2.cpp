#include <iostream>

using namespace std;

int n;
int x[100], y[100];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // Please write your code here.
    int result = 1000;
    for (int nx = 2; nx < 101; nx += 2) {
        for (int ny = 2; ny < 101; ny += 2) {
            int ans[4] = { 0, };
            for (int j = 0; j < n; ++j) {
                if (x[j] < nx) {
                    if (y[j] < ny)ans[1]++;
                    else ans[0]++;
                }
                else {
                    if (y[j] < ny)ans[2]++;
                    else ans[3]++;
                }
            }
            int tmp = ans[0];
            for (int j = 1; j < 4; ++j)tmp = tmp < ans[j] ? ans[j] : tmp;
            result = result > tmp ? tmp : result;
        }
    }
    cout << result;

    return 0;
}