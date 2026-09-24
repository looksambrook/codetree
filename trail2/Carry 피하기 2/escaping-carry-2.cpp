#include <iostream>

using namespace std;

int n;
int arr[20];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Please write your code here.
    int ans = -1;
    for (int i = 0; i < n - 2; ++i) {
        for (int j = i + 1; j < n - 1; ++j) {
            for (int k = j + 1; k < n; ++k) {
                bool is_carry = false;
                int tmp = 0;
                int sip = 1;
                int a = arr[i], b = arr[j], c = arr[k];
                while (!is_carry && !(a == 0 && b == 0 && c == 0)) {
                    if (a % 10 + b % 10 + c % 10 >= 10)is_carry = true;
                    tmp += (a % 10 + b % 10 + c % 10) * sip;
                    sip *= 10;
                    a /= 10; b /= 10; c /= 10;
                }
                if (!is_carry) {
                    ans = ans < tmp ? tmp : ans;
                }
            }
        }
    }
    cout << ans;

    return 0;
}