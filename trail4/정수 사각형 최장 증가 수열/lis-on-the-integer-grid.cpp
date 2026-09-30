#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>

using namespace std;

struct Info {
    int x;
    int y;
    int val;
    bool operator<(const Info& other)const {
        return val > other.val;
    }
};

int n;
int grid[500][500];
int value[500][500];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };
int ans = 0;
priority_queue<Info> pq;

bool is_range(int x, int y) {
    return x >= 0 && x < n
        && y >= 0 && y < n;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            value[i][j] = -1;
            pq.push({ i,j,grid[i][j] });
        }
    }

    // Please write your code here.
    while (!pq.empty()) {
        int cx = pq.top().x;
        int cy = pq.top().y;
        int cval = pq.top().val;
        pq.pop();

        queue<Info> q;
        q.push({ cx,cy,cval });
        while (!q.empty()) {
            int ccx = q.front().x;
            int ccy = q.front().y;
            int ccval = q.front().val;
            q.pop();

            for (int d = 0; d < 4; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (!is_range(nx, ny))continue;
                if (grid[nx][ny] >= grid[ccx][ccy])continue;
                value[ccx][ccy] = max(value[ccx][ccy], value[nx][ny] + 1);
                if (value[nx][ny] == -1) {
                    q.push({ nx,ny,ccval + 1 });
                }
            }
        }
        value[cx][cy]=max(value[cx][cy],0);
        ans=max(value[cx][cy],ans);
    }
    cout << ans+1;

    return 0;
}
