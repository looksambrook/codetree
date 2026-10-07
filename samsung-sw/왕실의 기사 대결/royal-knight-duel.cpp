#include <iostream>
using namespace std;

struct Info {
    int id, r, c, h, w, k, hurt;
};
int L, N, Q;
int target;
int grid[41][41];
int person[41][41];
Info pdata[101];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };

bool is_range(int x, int y) {
    return x >= 0 && x < L
        && y >= 0 && y < L;
}

bool moving(int id, int dir) {
    for (int i = pdata[id].r; i < pdata[id].r + pdata[id].h; ++i) {
        for (int j = pdata[id].c; j < pdata[id].c + pdata[id].w; ++j) {
            int cx = i + dx[dir];
            int cy = j + dy[dir];
            if (!is_range(cx, cy) || grid[cx][cy] == 2)return false;
            if (person[cx][cy] == id)continue;
            else {
                if (person[cx][cy] != 0)
                    if (!moving(person[cx][cy], dir))return false;
            }
        }
    }
    return true;
}

void push_person(int id, int dir) {
    for (int i = pdata[id].r; i < pdata[id].r + pdata[id].h; ++i) {
        for (int j = pdata[id].c; j < pdata[id].c + pdata[id].w; ++j) {
            int cx = i + dx[dir];
            int cy = j + dy[dir];
            if (person[cx][cy] == id)continue;
            else {
                if (person[cx][cy] != 0) push_person(person[cx][cy], dir);
            }
        }
    }
    int temp[41][41] = { 0, };
    for (int i = pdata[id].r; i < pdata[id].r + pdata[id].h; ++i) {
        for (int j = pdata[id].c; j < pdata[id].c + pdata[id].w; ++j) {
            temp[i + dx[dir]][j + dy[dir]] = person[i][j];
            person[i][j] = 0;
        }
    }
    pdata[id].r += dx[dir];
    pdata[id].c += dy[dir];
    for (int i = pdata[id].r; i < pdata[id].r + pdata[id].h; ++i) {
        for (int j = pdata[id].c; j < pdata[id].c + pdata[id].w; ++j) {
            person[i][j] = temp[i][j];
            if (target != id)if (grid[i][j] == 1)pdata[id].hurt += 1;
        }
    }
    if (pdata[id].k <= pdata[id].hurt) {
        for (int i = pdata[id].r; i < pdata[id].r + pdata[id].h; ++i) {
            for (int j = pdata[id].c; j < pdata[id].c + pdata[id].w; ++j) {
                person[i][j] = 0;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> L >> N >> Q;
    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            cin >> grid[i][j];
        }
    }
    for (int id = 1; id <= N; ++id) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        a--, b--;
        pdata[id] = { id,a,b,c,d,e,0 };
        for (int i = a; i < a + c; ++i) {
            for (int j = b; j < b + d; ++j) {
                person[i][j] = id;
            }
        }
    }

    for (int tc = 1; tc <= Q; ++tc) {
        int a, b;
        cin >> a >> b;
        if (pdata[a].k <= pdata[a].hurt)continue;
        target = a;
        if (moving(a, b)) {
            push_person(a, b);
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        if (pdata[i].k > pdata[i].hurt)ans += pdata[i].hurt;
    }
    cout << ans;

    return 0;
}