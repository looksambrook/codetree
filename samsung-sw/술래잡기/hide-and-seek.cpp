#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Info {
    int r, c;
    int dir;
};

struct Grid {
    bool tree;
    int person;
};

bool rev = true;
int N, M, H, K;
Info sul_line[10000];
int sul_cnt;
Info runner[10001];
Grid grid[100][100];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
int result = 0;
int ans = 0;

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

int cal_dis(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

void init_sul() {
    bool visited[100][100] = { false, };
    int cx = N / 2;
    int cy = N / 2;
    int cd = 3;
    while (true) {
        sul_line[sul_cnt] = { cx,cy,cd };
        visited[cx][cy] = true;
        sul_cnt += 1;
        if (sul_cnt == N * N)break;
        int nx = cx + dx[(cd + 1) % 4];
        int ny = cy + dy[(cd + 1) % 4];
        if (!is_range(nx, ny) || visited[nx][ny]) {
            cx += dx[cd], cy += dy[cd];
        }
        else {
            cx = nx, cy = ny, cd = (cd + 1) % 4;
            sul_line[sul_cnt - 1].dir = cd;
        }
    }
    sul_line[sul_cnt - 1].dir = (cd + 2) % 4;
    sul_cnt = 0;
    sul_line[sul_cnt].dir = 0;
}

void run() {
    for (int id = 1; id <= M; ++id) {
        if (cal_dis(runner[id].r, runner[id].c, sul_line[sul_cnt].r, sul_line[sul_cnt].c) > 3)continue;
        if (runner[id].dir == -1)continue;

        int nx = runner[id].r + dx[runner[id].dir];
        int ny = runner[id].c + dy[runner[id].dir];
        if (!is_range(nx, ny)) {
            runner[id].dir = (runner[id].dir + 2) % 4;
            nx = runner[id].r + dx[runner[id].dir];
            ny = runner[id].c + dy[runner[id].dir];
        }
        if (nx == sul_line[sul_cnt].r && ny == sul_line[sul_cnt].c)continue;
        grid[runner[id].r][runner[id].c].person -= 1;
        runner[id].r = nx, runner[id].c = ny;
        grid[runner[id].r][runner[id].c].person += 1;
        //cout << id << " " << runner[id].r << " " << runner[id].c << " check\n";
    }
}

void sul() {
    if (sul_cnt == 0 || sul_cnt == (N * N)-1)rev = !rev;
    if (rev)sul_cnt--;
    else sul_cnt++;
    int cd = sul_line[sul_cnt].dir;
    if (rev)cd = (sul_line[sul_cnt-1].dir + 2) % 4;

    for (int sight = 0; sight < 3; ++sight) {
        int cx = sul_line[sul_cnt].r + sight * dx[cd];
        int cy = sul_line[sul_cnt].c + sight * dy[cd];
        //cout << cx << ", " << cy << "\n";
        if (!is_range(cx, cy))break;
        if (grid[cx][cy].tree)continue;
        ans += grid[cx][cy].person;
        grid[cx][cy].person = 0;
        for (int id = 1; id <= M; ++id) {
            if (runner[id].dir == -1)continue;
            if (cx == runner[id].r && cy == runner[id].c)runner[id].dir = -1;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> H >> K;
    init_sul();
    for (int i = 1; i <= M; ++i) {
        int x, y, d;
        cin >> x >> y >> d;
        x--, y--;
        grid[x][y].person += 1;
        runner[i] = { x,y,d };
    }
    for (int i = 0; i < H; ++i) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        grid[x][y].tree = true;
    }

    for (int test_case = 1; test_case <= K; ++test_case) {
        /*for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                    cout << grid[i][j].person << " ";
            }
            cout << "\n";
        }
        cout << "before move\n";*/
        run();
        sul();
        result += test_case * ans;
        ans = 0;
        /*for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j].tree)cout << "t ";
                else
                cout << grid[i][j].person << " ";
            }
            cout << "\n";
        }
        cout << "\n";*/
    }
    cout << result;

    return 0;
}