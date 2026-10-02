#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Info {
    int first;
    int second;
    int earn;
    bool operator<(const Info& other)const {
        if (second != other.second) return second < other.second;
        if (first != other.first) return first < other.first;
        return earn > other.earn;
    }
};

int N;
int s[1000], e[1000], p[1000];
vector<Info> v;
int dp[1000];

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> s[i] >> e[i] >> p[i];
        v.push_back({ s[i],e[i],p[i] });
    }
    sort(v.begin(), v.begin() + N);

    // Please write your code here.
    int result = 0;
    for (int i = 0; i < N; ++i) {
        dp[i] = 0;
        for (int j = 0; j < i; ++j) {
            if (v[j].second < v[i].first)dp[i] = dp[i] < dp[j] ? dp[j] : dp[i];
        }
        dp[i] += v[i].earn;
        result = result < dp[i] ? dp[i] : result;
    }
    cout << result;

    return 0;
}
