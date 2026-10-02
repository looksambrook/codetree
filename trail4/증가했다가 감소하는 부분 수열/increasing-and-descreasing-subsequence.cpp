#include <iostream>
#include <algorithm>

using namespace std;

int n;
int sequence[1000];
int bigger[2][1000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
    }

    // Please write your code here.
    int result = 0;
    for (int i = 0; i < n; ++i) {
        bigger[0][i] = 0;
        bigger[1][i] = 0;
        for (int j = 0; j < i; ++j) {
            if (sequence[j] < sequence[i]) {
                bigger[0][i] = max(bigger[0][i], bigger[0][j]);
            }
            if (sequence[j] > sequence[i]) {
                bigger[1][i] = max(max(bigger[1][i], bigger[0][j]), bigger[1][j]);
            }
        }
        bigger[0][i] += 1, bigger[1][i] += 1;
        result = max(result, max(bigger[0][i], bigger[1][i]));
    }
    cout << result;

    return 0;
}
