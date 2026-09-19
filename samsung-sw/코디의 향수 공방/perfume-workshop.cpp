#include <iostream>
#include <algorithm>

using namespace std;

const int MAXP = 1105;   // 향료 최대 1000 + 100 = 1100개
const int MAXS = 3005;   // 향도 최대 3000
const int INF = 987654321;

int Q, v, w;
int perfume[MAXP] = { 0, };   // 0: 존재한 적 없음, -1: 폐기됨, 그 외: 향도
int pcnt;

void init() {
    for (int i = 0; i < w; ++i) {
        cin >> perfume[pcnt++];
    }
}

void add_perfume() {
    perfume[pcnt++] = w;
}

int delete_perfume() {
    if (w > pcnt) return -1;      // 존재하지 않는 번호
    int idx = w - 1;              // 1-based -> 0-based
    if (perfume[idx] < 1) return -1;   // 이미 폐기됨
    int scent = perfume[idx];
    perfume[idx] = -1;
    return scent;
}

int blending() {
    // 사용 가능한 향료의 '서로 다른 향도'만 모은다
    static bool seen[MAXS];
    static int arr[MAXP];
    fill(seen, seen + MAXS, false);

    int tcnt = 0;
    for (int i = 0; i < pcnt; ++i) {
        if (perfume[i] > 0 && !seen[perfume[i]]) {
            arr[tcnt++] = perfume[i];
            seen[perfume[i]] = true;
        }
    }
    sort(arr, arr + tcnt);   // 오름차순 -> 안쪽 루프에서 break 가능

    // dp[s] = 합이 정확히 s가 되게 만드는 최소 향료 개수
    static int dp[MAXS];
    dp[0] = 0;
    for (int s = 1; s <= w; ++s) {
        dp[s] = INF;
        for (int t = 0; t < tcnt; ++t) {
            if (arr[t] > s) break;                 // 이후 향도는 더 크므로 볼 필요 없음
            if (dp[s - arr[t]] + 1 < dp[s])
                dp[s] = dp[s - arr[t]] + 1;
        }
    }

    return dp[w] >= INF ? -1 : dp[w];
}

long long make_up() {
    static int arr[MAXP];
    int tcnt = 0;
    for (int i = 0; i < pcnt; ++i) {
        if (perfume[i] > 0) arr[tcnt++] = perfume[i];
    }
    sort(arr, arr + tcnt);

    // (탑, 미들, 베이스) 순서쌍, 같은 향료 중복 사용 허용, 합 >= w 인 경우의 수
    long long ans = 0;
    for (int i = 0; i < tcnt; ++i) {
        int need = w - arr[i];        // 나머지 두 자리의 합이 need 이상이어야 함
        int k = tcnt;                 // arr[j] + arr[k-1] >= need 를 만족하는 경계
        for (int j = 0; j < tcnt; ++j) {
            // arr[j]가 커질수록 경계는 단조 감소 -> 전체 O(tcnt)
            while (k > 0 && arr[j] + arr[k - 1] >= need) --k;
            ans += tcnt - k;
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> Q;
    for (int i = 0; i < Q; ++i) {
        cin >> v >> w;
        if (v == 1) init();
        else if (v == 2) add_perfume();
        else if (v == 3) cout << delete_perfume() << "\n";
        else if (v == 4) cout << blending() << "\n";
        else cout << make_up() << "\n";
    }

    return 0;
}