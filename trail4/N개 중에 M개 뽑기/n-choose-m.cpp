#include <iostream>

using namespace std;

int N, M;
int arr[10];

void backtracking(int n, int prev) {
    if (n == M) {
        for (int i = 0; i < M; ++i) {
            cout << arr[i] << " ";
        }
        cout << "\n";
        return;
    }

    for (int i = prev+1; i <= N; ++i) {
        arr[n] = i;
        backtracking(n + 1,i);
    }
}

int main() {
    cin >> N >> M;

    // Please write your code here.
    backtracking(0,0);

    return 0;
}
