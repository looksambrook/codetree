#include <iostream>

using namespace std;

int n;
int A[100];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    // Please write your code here.
    int ans = 300000;
    for (int i = 0; i < n; ++i) {
        int tmp = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j)continue;
            if (i < j) {
                tmp += (j - i) * A[j];
            }
            else {
                tmp += (i - j) * A[j];
            }
        }
        ans = ans > tmp ? tmp : ans;
    }
    cout << ans;

    return 0;
}