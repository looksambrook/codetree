#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Info {
    int r;
    int c;
    int att;
    int acnt;

    bool operator<(const Info& other)const {
        if (att != other.att)return att < other.att;
        if (acnt != other.acnt)return acnt > other.acnt;
        if ((r + c) != (other.r + other.c))return (r + c) > (other.r + other.c);
        return c > other.c;
    }
};

int N, M, K;
int grid[11][11];
vector<Info> po;
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

bool lazer() {
    int cx = po[0].r;
    int cy = po[0].c;
    Info parent[11][11];
    bool visited[11][11] = { false, };
    queue<pair<int, int>> q;
    q.push({ cx,cy });

    while (!q.empty()) {
        cx = q.front().first;
        cy = q.front().second;
        if (cx == po.back().r && cy == po.back().c)break;
        q.pop();

        for (int d = 0; d < 4; ++d) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];
            nx = (nx + N) % N;
            ny = (ny + M) % M;
            if (visited[nx][ny] || grid[nx][ny] == 0)continue;
            visited[nx][ny] = true;
            q.push({ nx,ny });
            parent[nx][ny] = { cx,cy };
        }
    }

    if (q.empty())return false;

    int power = po[0].att;
    grid[cx][cy] -= power;
    power /= 2;
    while (true) {
        Info tmp = parent[cx][cy];
        cx = tmp.r;
        cy = tmp.c;
        if (cx == po[0].r && cy == po[0].c)break;
        grid[cx][cy] -= power;
    }
    return true;
}

void attack() {
    int cx = po.back().r - 1;
    int cy = po.back().c - 1;
    int power = po[0].att / 2;
    grid[cx + 1][cy + 1] -= po[0].att;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int nx = (cx + i + N) % N;
            int ny = (cy + j + M) % M;
            if (nx == po[0].r && ny == po[0].c)continue;
            if (i == 1 && j == 1)continue;
            if (grid[nx][ny] == 0)continue;
            grid[nx][ny] -= power;
        }
    }
}

void check_po() {
    vector<Info>tmp;
    for (int i = 0; i < po.size(); ++i) {
        int cx = po[i].r;
        int cy = po[i].c;
        if (grid[cx][cy] == po[i].att && i != 0) {
            grid[cx][cy] += 1;
        }
        po[i].att = grid[cx][cy];
        if (grid[cx][cy] <= 0)grid[cx][cy] = 0;
        else tmp.push_back(po[i]);
    }
    po.clear();
    for (int i = 0; i < tmp.size(); ++i) {
        po.push_back(tmp[i]);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] != 0) po.push_back({ i,j,grid[i][j],0 });
        }
    }

    for (int tc = 1; tc <= K; ++tc) {
        sort(po.begin(), po.begin() + po.size());
        po[0].att += (N + M);
        grid[po[0].r][po[0].c] = po[0].att;
        po[0].acnt = tc;
        if (!lazer())attack();
        check_po();
        if (po.size() <= 1)break;
    }
    sort(po.begin(), po.begin() + po.size());
    cout << po.back().att;

    return 0;
}