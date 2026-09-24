#include <iostream>
#include <queue>
#include <climits>

using namespace std;

int n;
int a[1003];
queue<int> q;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Please write your code here.
    int ans = INT_MAX;
    for (int i = 0; i < n; ++i) {//출발 지점
        int tmp = 0;
        for (int j = 0; j < n; ++j) {
            tmp += j * a[(j + i) % n];
        }
        ans = ans > tmp ? tmp : ans;
    }
    cout<<ans;

    return 0;
}