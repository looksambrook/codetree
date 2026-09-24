#include <iostream>
#include <string>
#include <stack>

using namespace std;

string A;
stack<char> s;

int main() {
    cin >> A;

    // Please write your code here.
    int ans = 0;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] == '(')s.push(A[i]);
        else {
            ans += s.size();
        }
    }
    cout << ans;
    return 0;
}