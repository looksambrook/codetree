#include <iostream>
#include <climits>

using namespace std;

int n;
int arr[100];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Please write your code here.
    int ans = INT_MAX;
    for (int i = 0; i < n; ++i) {//*2
        arr[i] *= 2;
        for (int j = 0; j < n; ++j) {//delete
            int prev = -1;
            int tmp = 0;
            for (int k = 0; k < n; ++k) {
                if (k == j)continue;
                if (prev == -1) {
                    prev = k;
                    continue;
                }
                tmp += abs(arr[prev] - arr[k]);
                prev = k;
            }
            ans = ans < tmp ? ans : tmp;
        }
        arr[i] /= 2;
    }
    cout << ans;

    return 0;
}