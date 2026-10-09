#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct Grid {
    int val;
    bool clean;
};
struct Info {
    int x, y;
};
struct Data {
    int x, y;
    int dis;
};

int N, K, L;
Grid grid[40][40];
Info cleaner[60];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void cmoving(int id) {
    bool visited[40][40] = { false, };
    queue<Data> q;
    q.push({ cleaner[id].x,cleaner[id].y,0 });
    visited[cleaner[id].x][cleaner[id].y] = true;
    Data ans = { N,N,10000 };

    while (!q.empty()) {
        Data curr = q.front();
        q.pop();

        if (grid[curr.x][curr.y].val > 0) {
            if (curr.dis < ans.dis || (curr.dis == ans.dis && (curr.x < ans.x || (curr.x == ans.x && curr.y < ans.y)))) ans = curr;
            continue;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = curr.x + dx[d];
            int ny = curr.y + dy[d];
            if (!is_range(nx, ny) || visited[nx][ny] || grid[nx][ny].clean || grid[nx][ny].val < 0)continue;
            if ((curr.dis + 1) > ans.dis)break;
            visited[nx][ny] = true;
            q.push({ nx,ny,curr.dis + 1 });
        }
    }

    if (ans.dis == 10000) {
        grid[cleaner[id].x][cleaner[id].y].clean = true;
        return;
    }
    cleaner[id] = { ans.x,ans.y };
    grid[ans.x][ans.y].clean = true;
}

void moving() {
    for (int id = 1; id <= K; ++id) {
        if (grid[cleaner[id].x][cleaner[id].y].val > 0)continue;
        grid[cleaner[id].x][cleaner[id].y].clean = false;
        cmoving(id);
    }
}

int cal(int val) {
    return val > 20 ? 20 : val;
}

void cleaning() {
    for (int id = 1; id <= K; ++id) {
        int cx = cleaner[id].x;
        int cy = cleaner[id].y;
        Info ans = { 0,-1 }; //합, 방향

        for (int d = 0; d < 4; ++d) {
            int val = 0;
            for (int i = -1; i < 2; ++i) {
                int dir = (d + i + 4) % 4;
                int nx = cx + dx[dir];
                int ny = cy + dy[dir];
                if (!is_range(nx, ny) || grid[nx][ny].val < 0)continue;
                val += cal(grid[nx][ny].val);
            }
            if (ans.x < val)ans = { val,d };
        }

        grid[cx][cy].val -= cal(grid[cx][cy].val);
        for (int i = -1; i < 2; ++i) {
            int dir = (ans.y + i + 4) % 4;
            int nx = cx + dx[dir];
            int ny = cy + dy[dir];
            if (!is_range(nx, ny) || grid[nx][ny].val < 0)continue;
            grid[nx][ny].val -= cal(grid[nx][ny].val);
        }
    }
}

void dirt() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j].val > 0)grid[i][j].val += 5;
        }
    }
}

void spread() {
    int temp[40][40] = { 0, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j].val != 0)continue;
            int val = 0;
            int cx = i, cy = j;
            for (int d = 0; d < 4; ++d) {
                int nx = cx + dx[d];
                int ny = cy + dy[d];
                if (!is_range(nx, ny) || grid[nx][ny].val < 0)continue;
                val += grid[nx][ny].val;
            }
            temp[i][j] = val / 10;
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            grid[i][j].val += temp[i][j];
        }
    }
}

int pdirt() {
    int res = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j].val > 0)res += grid[i][j].val;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> K >> L;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int val;
            cin >> val;
            grid[i][j] = { val,false };
        }
    }
    for (int id = 1; id <= K; ++id) {
        int r, c;
        cin >> r >> c;
        r--, c--;
        grid[r][c].clean = true;
        cleaner[id] = { r,c };
    }

    for (int test_case = 1; test_case <= L; ++test_case) {
        moving();
        cleaning();
        dirt();
        spread();
        int result = pdirt();
        cout << result << "\n";
        if (result == 0)break;
    }

    return 0;
}