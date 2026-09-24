#include <iostream>

using namespace std;

int N;
int a[100], b[100], c[100];
int ans[3] = {0,};

int main() {
    cin >> N;
    int arr[3] = { 0,1,2 };

    for (int i = 0; i < N; i++) {
        cin >> a[i] >> b[i] >> c[i];
        int tmp = arr[a[i] - 1];
        arr[a[i] - 1] = arr[b[i] - 1];
        arr[b[i] - 1] = tmp;
        ans[arr[c[i] - 1]]++;
    }

    int result = 0;
    for (int i = 0; i < 3; ++i) {
        result = result < ans[i] ? ans[i] : result;
    }
    cout << result;

    return 0;
}