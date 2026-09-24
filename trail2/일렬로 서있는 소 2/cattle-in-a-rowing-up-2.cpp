#include <iostream>

using namespace std;

int N;
int A[100];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }

    // Please write your code here.
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = i+1; j < N; ++j) {
            if (A[i] > A[j])continue;
            for (int k = j+1; k < N; ++k) {
                if (A[j] > A[k])continue;
                ans++;
            }
        }
    }
    cout << ans;

    return 0;
}