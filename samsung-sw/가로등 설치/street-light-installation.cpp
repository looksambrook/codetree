#include <iostream>
#include <queue>
#include <unordered_set>

using namespace std;

int N, M;
struct Data
{
    int val;
    int left;
    int right;
} light[200005];
unordered_set<int> s;

struct Info
{
    long long dis;
    int left;
    int right;

    bool operator<(const Info& other)const {
        if (dis != other.dis) return dis < other.dis;
        return light[left].val > light[other.left].val;
    }
};
priority_queue<Info> pq;

void init() {
    cin >> N >> M;
    for (int i = 1; i <= M; ++i) {
        int tmp;
        cin >> tmp;
        light[i] = { tmp,i - 1,i + 1 };
    }
    light[M].right = -1;
    for (int i = 1; i < M; ++i) {
        pq.push({ light[i + 1].val - light[i].val,i,i + 1 });
    }
    pq.push({ (light[1].val - 1) * 2,0,1 });
    pq.push({ (N - light[M].val) * 2,M,-1 });
}

void add_light() {
    Info tmp[2];
    int tcnt = 0;
    while (true) {
        if (s.count(pq.top().left) > 0 || s.count(pq.top().right) > 0) {
            pq.pop();
            continue;
        }
        if (pq.top().left == 0 || pq.top().right == -1) {
            tmp[tcnt++] = pq.top();
            pq.pop();
            continue;
        }

        int left = pq.top().left, right = pq.top().right, idx = ++M;
        pq.pop();
        light[M] = { (light[left].val + light[right].val+1) / 2,left,right };
        light[left].right = M;
        light[right].left = M;
        pq.push({ light[M].val-light[light[M].left].val,left,M });
        pq.push({ light[light[M].right].val - light[M].val,M, right });
        break;
    }
    for (int i = 0; i < tcnt; ++i) {
        pq.push(tmp[i]);
    }
}

void delete_light() {
    int tmp;
    cin >> tmp;
    s.insert(tmp);
    if (light[tmp].left == 0) {
        light[light[tmp].right].left = 0;
        pq.push({ (light[light[tmp].right].val-1) * 2,0,light[tmp].right });
    }
    else if (light[tmp].right == -1) {
        light[light[tmp].left].right = -1;
        pq.push({ (N-light[light[tmp].left].val) * 2,light[tmp].left,-1 });
    }
    else {
        pq.push({ light[light[tmp].right].val - light[light[tmp].left].val,light[tmp].left,light[tmp].right });
        light[light[tmp].left].right = light[tmp].right;
        light[light[tmp].right].left = light[tmp].left;
    }
}

int cal() {
    while (true) {
        if (s.count(pq.top().left) > 0 || s.count(pq.top().right) > 0) {
            pq.pop();
            continue;
        }
        break;
    }
    return pq.top().dis;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int test_case;
    cin >> test_case;
    for (int tc = 1; tc <= test_case; ++tc) {
        int com;
        cin >> com;
        if (com == 100)init();
        else if (com == 200)add_light();
        else if (com == 300)delete_light();
        else if (com == 400)cout << cal() << "\n";
    }
    return 0;
}