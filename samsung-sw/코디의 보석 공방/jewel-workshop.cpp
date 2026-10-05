#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Info {
    int w;
    int v;

    bool operator<(const Info& other)const {
        return w < other.w;
    }
};

int N;
Info jew[1100];

void init() {
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int w, v;
        cin >> w >> v;
        jew[i] = { w,v };
    }
}

void add_jew() {
    int w, v;
    cin >> w >> v;
    jew[N++] = { w,v };
}

int sale_jew() {
    int idx, tmp = -1;
    cin >> idx;
    if (idx <= N) {
        tmp = jew[idx - 1].v;
        jew[idx - 1].v = -1;
    }
    return tmp;
}

int show_jew() {
    int W, ans = 0;
    cin >> W;
    int dp[3001] = { 0, };
    for (int i = 1; i <= W; ++i)dp[i] = -1;
    for (int i = 0; i < N; ++i) {
        if (jew[i].w > W || jew[i].v == -1)continue;
        for (int j = W; j >=0; --j) {
            if (j - jew[i].w < 0)continue;
            if (dp[j - jew[i].w] == -1)continue;
            dp[j] = max(dp[j], dp[j - jew[i].w] + jew[i].v);
        }
    }
    for (int i = 0; i <= W; ++i)ans = max(ans, dp[i]);
    return ans;
}

int set_jew() {
    int D, ans = 0;
    vector<Info> v;
    cin >> D;
    for (int i = 0; i < N; ++i) {
        if (jew[i].v == -1)continue;
        v.push_back(jew[i]);
    }
    sort(v.begin(), v.begin() + v.size());

    for (int second = 1; second < v.size(); ++second) {
        int first = 0;
        while (first < second) {
            if (v[second].w - v[first].w <= D) {
                ans += second - first;
                break;
            }
            else first++;
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int Q;
    cin >> Q;

    for (int i = 1; i <= Q; ++i) {
        int com;
        cin >> com;
        if (com == 1)init();
        else if (com == 2)add_jew();
        else if (com == 3)cout << sale_jew() << "\n";
        else if (com == 4)cout << show_jew() << "\n";
        else cout << set_jew() << "\n";
    }
    return 0;
}