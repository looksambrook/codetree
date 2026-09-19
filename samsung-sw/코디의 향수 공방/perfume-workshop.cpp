#include <iostream>
#include <algorithm>

using namespace std;

int Q, com, val;
int perfume[1101] = { 0, };
int pcnt = 0;

void init() {
    for (int i = 0; i < val; ++i) {
        cin >> perfume[pcnt++];
    }
}

void add_func() {
    perfume[pcnt++] = val;
}

int delete_func() {
    val--;
    if (perfume[val] == 0)return-1;
    int tmp = perfume[val];
    perfume[val] = 0;
    return tmp;
}

int blending() {
    int arr[1101] = { 0, };
    int acnt = 0;
    bool visited[3001] = { false, };
    for (int i = 0; i < pcnt; ++i) {
        if (perfume[i] != 0 && !visited[perfume[i]]) {
            arr[acnt++] = perfume[i];
            visited[perfume[i]] = true;
        }
    }

    int dp[3001];
    dp[0] = 0;
    for (int i = 1; i <= val; ++i) {
        dp[i] = 4000;
        for (int j = 0; j < acnt; ++j) {
            if (i >= arr[j] && (dp[i] > (dp[i - arr[j]] + 1)))
                dp[i] = dp[i - arr[j]] + 1;
        }
    }
    return dp[val] == 4000 ? -1 : dp[val];
}

int make_up() {
    int arr[1001];
    int acnt = 0;
    for (int i = 0; i < pcnt; ++i) {
        if (perfume[i] != 0)
            arr[acnt++] = perfume[i];
    }
    sort(arr, arr + acnt);

    int ans = 0;
    for (int i = 0; i < acnt; ++i) {
        int goals = val - arr[i];
        int k = acnt;
        for (int j = 0; j < acnt; ++j) {
            while (k > 0 && arr[j] + arr[k - 1] >= goals) k--;
            ans += acnt - k;
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
        else if (com == 2)add_func();
        else if (com == 3)cout << delete_func() << "\n";
        else if (com == 4)cout << blending() << "\n";
        else cout << make_up() << "\n";
    }
    return 0;
}