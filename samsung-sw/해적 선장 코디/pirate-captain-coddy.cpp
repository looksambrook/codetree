#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

struct Info {
    int id, p, r, delay;
};

int T;
Info ship[60001];
int scnt = 0;
unordered_map<int, int> m;
set<pair<int, int>> s;   // {-공격력, id} : 공격력 큰 순, 같으면 id 작은 순

void add(int id, int p, int r) {
    ship[scnt] = { id,p,r,-60000 };
    m[id] = scnt++;
    s.insert({ -p, id });
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
    Info& sh = ship[m[id]];
    s.erase({ -sh.p, id });   // 옛 공격력 항목은 바로 지움
    sh.p = pw;
    s.insert({ -pw, id });
}

void attack(int cur) {
    int ids[5], sum = 0, point = 0;
    for (auto it = s.begin(); it != s.end() && point < 5; ++it) {
        Info& sh = ship[m[it->second]];
        if (cur - sh.delay >= sh.r) {
            ids[point++] = sh.id;
            sum += sh.p;
            sh.delay = cur;
        }
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