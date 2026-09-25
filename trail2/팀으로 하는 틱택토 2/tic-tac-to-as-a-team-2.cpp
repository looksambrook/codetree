#include <iostream>
#include <string>

using namespace std;

string inp[3];
int dx[8] = { 0,1,-1,-1,0,-1,1,1 };
int dy[8] = { -1,-1,0,-1,1,1,0,1 };
bool visited[10][10] = { false, };

int main() {
    for (int i = 0; i < 3; i++) cin >> inp[i];

    // Please write your code here.
    int ans = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (i == 1 || j == 1) {
                for (int d = 0; d < 4; ++d) {
                    int ax = i + dx[d], ay = j + dy[d];
                    int cx = i + dx[d + 4], cy = j + dy[d + 4];
                    if (ax < 0 || ax>2 || ay < 0 || ay>2 || cx < 0 || cx>2 || cy < 0 || cy>2)continue;
                    if (inp[ax][ay] == inp[cx][cy] && inp[ax][ay] != inp[i][j]) {
                        if (!visited[inp[ax][ay]][inp[i][j]]) {
                            visited[inp[ax][ay]][inp[i][j]] = true;
                            visited[inp[i][j]][inp[ax][ay]] = true;
                            ans++;
                        }
                    }
                    if (inp[ax][ay] == inp[i][j] && inp[ax][ay] != inp[cx][cy]) {
                        if (!visited[inp[ax][ay]][inp[cx][cy]]) {
                            visited[inp[ax][ay]][inp[cx][cy]] = true;
                            visited[inp[cx][cy]][inp[ax][ay]] = true;
                            ans++;
                        }
                    }
                    if (inp[i][j] == inp[cx][cy] && inp[ax][ay] != inp[i][j]) {
                        if (!visited[inp[ax][ay]][inp[i][j]]) {
                            visited[inp[ax][ay]][inp[i][j]] = true;
                            visited[inp[i][j]][inp[ax][ay]] = true;
                            ans++;
                        }
                    }
                }
            }
        }
    }

    cout << ans;

    return 0;
}