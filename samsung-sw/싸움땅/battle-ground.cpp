#include <iostream>
#include <queue>

using namespace std;

struct Grid {
    priority_queue<int> gun;
    int player_id;
};
struct Player {
    int x, y;
    int skill;
    int d;
    int gun_skill;
};

int N, M, K;
Grid grid[21][21];
Player player[31];
int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
int point[31] = { 0, };

bool is_range(int x, int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void blank(int x, int y, int id) {
    player[id].x = x;
    player[id].y = y;
    grid[x][y].player_id = id;
    if (!grid[x][y].gun.empty()) {
        grid[x][y].gun.push(player[id].gun_skill);
        player[id].gun_skill = grid[x][y].gun.top();
        grid[x][y].gun.pop();
    }
}

bool fight(int me, int you) {//true:me가 이긴거, false: me가 진거
    if ((player[me].gun_skill + player[me].skill) != (player[you].gun_skill + player[you].skill))
        return (player[me].gun_skill + player[me].skill) > (player[you].gun_skill + player[you].skill);
    return player[me].skill > player[you].skill;
}

void after_fight(int winner, int loser, const int& x, const int& y) {
    point[winner] += abs((player[winner].gun_skill + player[winner].skill) - (player[loser].gun_skill + player[loser].skill));
    
    grid[x][y].gun.push(player[loser].gun_skill);
    player[loser].gun_skill = 0;
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[(player[loser].d + d) % 4];
        int ny = y + dy[(player[loser].d + d) % 4];
        if (!is_range(nx, ny) || grid[nx][ny].player_id != 0)continue;
        player[loser].d = (player[loser].d + d) % 4;
        blank(nx, ny, loser);
        break;
    }
    blank(x, y, winner);
}

void moving() {
    for (int id = 1; id <= M; ++id) {
        grid[player[id].x][player[id].y].player_id = 0;
        int nx = player[id].x + dx[player[id].d];
        int ny = player[id].y + dy[player[id].d];
        if (!is_range(nx, ny)) {
            player[id].d = (player[id].d + 2) % 4;
            nx = player[id].x + dx[player[id].d];
            ny = player[id].y + dy[player[id].d];
        }
        if (grid[nx][ny].player_id != 0) {
            if (fight(id, grid[nx][ny].player_id)) after_fight(id, grid[nx][ny].player_id, nx, ny);
            else after_fight(grid[nx][ny].player_id, id, nx, ny);
        }
        else {
            blank(nx, ny, id);
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M >> K;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int tmp;
            cin >> tmp;
            if (tmp != 0)grid[i][j].gun.push(tmp);
            grid[i][j].player_id = 0;
        }
    }
    for (int id = 1; id <= M; ++id) {
        int x, y, d, s;
        cin >> x >> y >> d >> s;
        x--, y--;
        player[id] = { x,y,s,d,0 };
        grid[x][y].player_id = id;
    }

    for (int test_case = 1; test_case <= K; ++test_case) {
        moving();
    }
    for (int i = 1; i <= M; ++i)cout << point[i] << " ";
    return 0;
}