#include <iostream>
#include <vector>

using namespace std;

struct Info
{
    int r, c, h, w;
};
int N, M, tmp;
int grid[51][51];
Info box[101];

void input(int num) {
    tmp = 0;
    for (int i = box[num].h+box[num].r; i < N; ++i) {
        for (int j = box[num].c; j < box[num].c + box[num].w; ++j) {
            if (grid[i][j] != 0) {
                i = N;
                break;
            }
        }
        if (i != N)
            tmp++;
    }
    box[num].r += tmp;
    for (int i = 0; i < box[num].h; ++i) {
        for (int j = 0; j < box[num].w; ++j) {
            grid[i + box[num].r][box[num].c + j] = num;
        }
    }
}

void remove(int num) {
    cout << num << "\n";
    int target = num;
    vector<int> v;
    for (int i = box[target].r; i < box[target].r + box[target].h; ++i) {
        for (int j = box[target].c; j < box[target].c + box[target].w; ++j) {
            grid[i][j] = 0;
        }
    }

    for (int i = box[target].c; i < box[target].c + box[target].w; ++i) {
        if (box[target].r>0&&grid[box[target].r - 1][i] != 0) {
            bool is_down = true;
            for (int j = box[grid[box[target].r - 1][i]].c; j < box[grid[box[target].r - 1][i]].c + box[grid[box[target].r - 1][i]].w; ++j) {
                if (grid[box[target].r][j] != 0) {
                    is_down = false;
                    break;
                }
            }
            if (is_down)v.push_back(grid[box[target].r - 1][i]);
            i = box[grid[box[target].r - 1][i]].c + box[grid[box[target].r - 1][i]].w-1;
        }
    }

    for (int vc = 0; vc < v.size(); ++vc) {
        target = v[vc];
        int cx = box[target].r;
        int cy = box[target].c;
        int cw = box[target].w;

        for (int i = cx; i < cx + box[target].h; ++i) {
            for (int j = cy; j < cy + cw; ++j) {
                grid[i][j] = 0;
            }
        }
        input(target);

        for (int i = cy; i < cy + cw; ++i) {
            if (cx>0&&grid[cx - 1][i] != 0) {
                bool is_down = true;
                for (int j = box[grid[cx - 1][i]].c; j < box[grid[cx - 1][i]].c + box[grid[cx - 1][i]].w; ++j) {
                    if (grid[cx][j] != 0) {
                        is_down = false;
                        break;
                    }
                }
                if (is_down)v.push_back(grid[cx - 1][i]);
                i = box[grid[cx - 1][i]].c + box[grid[cx - 1][i]].w-1;
            }
        }

    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    cin >> N >> M;
    for (int tc = 0; tc < M; ++tc) {
        int k, h, w, c;
        cin >> k >> h >> w >> c;
        box[k] = { 0,c - 1,h,w };
        input(k);
    }

    for (int tc = 0; tc < M; ++tc) {
        /*cout << "hi:\n";
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }*/
        int target = 2000;
        int check[51] = { 0, };
        if (tc % 2 == 0) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {  //left
                    if (grid[i][j] != 0) {
                        check[i] = grid[i][j];
                        break;
                    }
                }
            }
            int len = 1;
            for (int i = 0; i < N; ++i) {
                if (i == N-1) {
                    if (check[i] != 0 && box[check[i]].h == len)target = target > check[i] ? check[i] : target;
                    break;
                }
                if (check[i] == check[i+1])len++;
                else {
                    if (check[i]!= 0 && box[check[i]].h == len)target = target > check[i] ? check[i] : target;
                        len = 1;
                }
            }
        }
        else {
            for (int i = 0; i < N; ++i) {
                for (int j = N-1; j >=0; --j) {  //right
                    if (grid[i][j] != 0) {
                        check[i] = grid[i][j];
                        break;
                    }
                }
            }
            int len = 1;
            for (int i = 0; i < N; ++i) {
                if (i == N - 1) {
                    if (check[i] != 0 && box[check[i]].h == len)target = target > check[i] ? check[i] : target;
                    break;
                }
                if (check[i] == check[i + 1])len++;
                else {
                    if (check[i] != 0 && box[check[i]].h == len)target = target > check[i] ? check[i] : target;
                    len = 1;
                }
            }
        }
        remove(target);
    }

    return 0;
}