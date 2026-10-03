#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Info {
    int birth;
    int sum;
    vector<vector<bool>> shape;

    bool operator<(const Info& other)const {
        if (sum != other.sum)return sum < other.sum;
        return birth > other.birth;
    }
};
int N, Q;
int grid[16][16];
Info mi[51];
bool is_deleted[51] = { false, };
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

bool is_range(int x,int y) {
    return x >= 0 && x < N
        && y >= 0 && y < N;
}

void check_grid() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void input(int sx,int ex,int sy,int ey,int num) {
    bool visited[51] = { false, };
    mi[num] = { num,(ex - sx) * (ey - sy),{} };
    mi[num].shape.resize(N);
    for (int i = sx; i < ex; ++i) {
        mi[num].shape[i].clear();
        for (int j = sy; j < ey; ++j) {
            if (grid[i][j] != 0) {
                mi[grid[i][j]].sum -= 1;
                if(!visited[grid[i][j]]) visited[grid[i][j]]=true;
            }
            grid[i][j] = num;
            mi[num].shape[i - sx].push_back(true);
        }
    }
    //list delete and check 2-piece / update shape
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j]!=0&&visited[grid[i][j]]) {
                visited[grid[i][j]] = false;

                int sr = i, sc = j, er = i, ec = j, cnt = 0;
                bool check[51][51] = { false, };
                queue<pair<int, int>> q;

                q.push({ i,j });
                check[i][j] = true;
                while (!q.empty()) {
                    int cx = q.front().first;
                    int cy = q.front().second;
                    q.pop();

                    sr = sr > cx ? cx : sr;
                    sc = sc > cy ? cy : sc;
                    er = er < cx ? cx : er;
                    ec = ec < cy ? cy : ec;
                    cnt++;
                    for (int d = 0; d < 4; ++d) {
                        int nx = cx + dx[d];
                        int ny = cy + dy[d];
                        if (!is_range(nx, ny)||check[nx][ny])continue;
                            check[nx][ny] = true;
                        if (grid[i][j] == grid[nx][ny]) {
                            q.push({ nx,ny });
                        }
                    }
                }
                //cout <<grid[i][j]<<": "<< sr << " " << er << " / " << sc << " " << ec << "\n";
                if (cnt != mi[grid[i][j]].sum)is_deleted[grid[i][j]] = true;

                else {
                    mi[grid[i][j]].shape.clear();
                    mi[grid[i][j]].shape.resize(N);
                    for (int r = 0; r < N; ++r) {
                        mi[grid[i][j]].shape[r].clear();
                        if (r > er - sr)continue;
                        for (int c = 0; c <=ec-sc; ++c) {
                            if (!is_range(r + sr, c + sc))continue;
                            mi[grid[i][j]].shape[r].push_back(grid[r + sr][c + sc] == grid[i][j] ? true : false);
                        }
                    }
                }
            }
        }
    }
}

void moving() {
    int temp[16][16] = { 0, };
    bool visited[51] = { false, };
    priority_queue<Info> pq;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j]!=0&&!visited[grid[i][j]]&&!is_deleted[grid[i][j]]) {
                visited[grid[i][j]] = true;
                pq.push(mi[grid[i][j]]);
            }
        }
    }
    while (!pq.empty()) {
        Info curr = pq.top();
        //cout << "check: " << curr.birth << "\n";
        pq.pop();
        /*for (int i = 0; i < curr.shape.size(); ++i) {
            for (int j = 0; j < curr.shape[i].size(); ++j) {
                cout << curr.shape[i][j] << " ";
            }
            cout << "\n";
        }*/

        for (int j = 0; j < N; ++j) {
            for (int i = N - 1; i >= 0; --i) {
                bool is_write = true;
                int cnt = 0;
                for (int r = i; r < i+curr.shape.size(); ++r) {
                    for (int c = j; c < j+ curr.shape[r - i].size(); ++c) {
                        if (!is_range(r,c)||(curr.shape[r-i][c-j]&&temp[r][c]!=0)) {
                            is_write = false;
                            r = i+curr.shape.size();
                            break;
                        }
                        if(is_range(r-i,c-j)&&curr.shape[r-i][c-j]) cnt++;
                    }
                }
                if (cnt != curr.sum)is_write = false;
                if (is_write) {
                    //cout << "cehck plz\n";
                    for (int r = 0; r <curr.shape.size(); ++r) {
                        for (int c = 0; c < curr.shape[r].size(); ++c) {
                            if(curr.shape[r][c])temp[i+r][j+c] = curr.birth;
                        }
                    }
                    j = N;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            grid[i][j] = temp[i][j];
        }
    }
}

int cal() {
    int ans = 0;
    bool visited[51][51] = { false, };
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0)continue;
            int curr = grid[i][j];
            int next;
            if (i != N - 1) {
                next = grid[i + 1][j];
                if (next != 0 && curr != next && !visited[curr][next]) {
                    visited[curr][next] = true;
                    visited[next][curr] = true;
                    ans += mi[curr].sum * mi[next].sum;
                }
            }
            if (j != N - 1) {
                next = grid[i][j + 1];
                if (next != 0 && curr != next && !visited[curr][next]) {
                    visited[curr][next] = true;
                    visited[next][curr] = true;
                    ans += mi[curr].sum * mi[next].sum;
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> Q;
    for (int tc = 1; tc <= Q; ++tc) {
        int r1, r2, c1, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        input(N-c2,N-c1,r1,r2,tc);
        //check_grid();
        moving();
        //check_grid();
        cout << cal() << "\n";
    }

    return 0;
}