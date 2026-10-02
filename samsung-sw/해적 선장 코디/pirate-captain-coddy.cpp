#include <iostream>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Info {
    int p, r, delay;
};
struct Data {
    int id, p;

    bool operator<(const Data& other)const {
        if (p != other.p)return p < other.p;
        return id > other.id;
    }
};

int T;
unordered_map<int, Info> ship_id;
priority_queue<Data> pq;

void init() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int id, p, r;
        cin >> id >> p >> r;
        ship_id[id] = { p,r,-60000 };
        pq.push({ id,p });
    }
}

void add_ship() {
    int id, p, r;
    cin >> id >> p >> r;
    ship_id[id] = { p,r,-60000 };
    pq.push({ id,p });
}

void change_ship() {
    int id, pw;
    cin >> id >> pw;
    ship_id[id].p = pw;
    pq.push({ id,pw });
}

void attack(int cur) {
    int attack_size[6] = { 0,0,0,0,0,0 };
    int point = 0;
    queue<Data>q;
    while (!pq.empty()) {
        if (point == 5)break;
        Data curr = pq.top();
        pq.pop();
        if (ship_id[curr.id].p != curr.p) continue;
        if (cur - ship_id[curr.id].delay >= ship_id[curr.id].r) {
            attack_size[point] = curr.id;
            attack_size[5] += curr.p;
            ship_id[curr.id].delay = cur;
            point++;
        }
        q.push(curr);
    }
    while (!q.empty()) {
        pq.push(q.front());
        q.pop();
    }
    cout << attack_size[5] << " " << point << " ";
    for (int i = 0; i < point; ++i) cout << attack_size[i] << " ";
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