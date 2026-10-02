#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

struct Info {
    int id, p, r;
};
struct Node {
    int p, id, idx, ver;

    bool operator<(const Node& other)const {
        if (p != other.p)return p < other.p;   // 공격력 큰 게 top
        return id > other.id;                  // 같으면 id 작은 게 top
    }
};

int T;
Info ship[60001];
int ver[60001];        // 배마다 가장 최근에 넣은 항목 번호
bool cooling[60001];   // 재장전 중인지
int scnt = 0;
unordered_map<int, int> m;
priority_queue<Node> ready;   // 공격 가능한 배 (옛 항목 섞여 있음)
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> cool;   // {재장전 끝나는 시각, idx}

void push_ready(int idx) {
    ++ver[idx];   // 이전에 넣은 항목은 전부 무효가 됨
    ready.push({ ship[idx].p, ship[idx].id, idx, ver[idx] });
}

void add(int id, int p, int r) {
    ship[scnt] = { id,p,r };
    m[id] = scnt;
    push_ready(scnt++);
}

void init() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int id, p, r;
        cin >> id >> p >> r;
        add(id, p, r);
    }
}

void add_ship() {
    int id, p, r;
    cin >> id >> p >> r;
    add(id, p, r);
}

void change_ship() {
    int id, pw;
    cin >> id >> pw;
    int idx = m[id];
    ship[idx].p = pw;
    if (!cooling[idx])push_ready(idx);   // 재장전 중이면 끝날 때 새 공격력으로 들어감
}

void attack(int cur) {
    // 재장전이 끝난 배를 공격 가능 큐로 옮김
    while (!cool.empty() && cool.top().first <= cur) {
        int idx = cool.top().second;
        cool.pop();
        cooling[idx] = false;
        push_ready(idx);
    }

    int ids[5], sum = 0, point = 0;
    while (!ready.empty() && point < 5) {
        Node t = ready.top();
        ready.pop();
        if (t.ver != ver[t.idx])continue;   // 옛 항목은 버림
        ids[point++] = t.id;
        sum += t.p;
        cooling[t.idx] = true;
        cool.push({ cur + ship[t.idx].r, t.idx });
    }
    cout << sum << " " << point << " ";
    for (int i = 0; i < point; ++i)cout << ids[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        int com;
        cin >> com;
        if (com == 100)init();
        else if (com == 200)add_ship();
        else if (com == 300)change_ship();
        else attack(tc);
    }
    return 0;
}