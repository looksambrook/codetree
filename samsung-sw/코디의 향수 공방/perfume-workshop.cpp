#include <iostream>
#include <algorithm>

using namespace std;

int Q, com, val;
int perfume[1101];
int pcnt = 0;

void init() {
    for (int i = 0; i < val; ++i) {
        cin >> perfume[pcnt++];
    }
}

void padd() {
    perfume[pcnt++] = val;
}

int pdelete() {
    int tmp = perfume[val - 1];
    perfume[val - 1] = 0;
    return tmp == 0 ? -1 : tmp;
}

int blending() {
    int dp[3001];
    dp[0] = 0;
    for (int i = 1; i <= val; ++i) {
        dp[i] = 4000;
        for (int j = 0; j < pcnt; ++j) {
            if (perfume[j] == 0)continue;
            if (i >= perfume[j] && (dp[i] > (dp[i - perfume[j]] + 1)))
                dp[i] = dp[i - perfume[j]] + 1;
        }
    }
    return dp[val] == 4000 ? -1 : dp[val];
}

int make_up() {
    int arr[1101];
    int acnt = 0;
    for (int i = 0; i < pcnt; ++i) {
        if (perfume[i] != 0) {
            arr[acnt++] = perfume[i];
        }
    }
    sort(arr, arr + acnt);

    int ans = 0;
    for (int i = 0; i < acnt; ++i) {
        int right = acnt;
        for (int left = 0; left < acnt; ++left) {
            while(right > 0 && ((arr[i] + arr[left] + arr[right - 1]) >= val))right--;
            ans += acnt - right;
        }
    }
    return ans;
}

int main() {
    // Please write your code here.
    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> com >> val;
        if (com == 1)init();
        else if (com == 2)padd();
        else if (com == 3)cout << pdelete() << "\n";
        else if (com == 4)cout << blending() << "\n";
        else cout << make_up() << "\n";
    }
    return 0;
}