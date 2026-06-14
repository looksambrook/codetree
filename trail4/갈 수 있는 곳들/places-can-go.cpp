#include <iostream>

using namespace std;

int n, k;
int grid[100][100];
int r[10000], c[10000];
int dx[4]={1,0,-1,0};
int dy[4]={0,-1,0,1};
int ans=0;

void DFS(int cx, int cy){
    if(grid[cx][cy]==0){
        ans++;
        grid[cx][cy]=1;
    }
    for(int i=0;i<4;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=n)continue;
        if(grid[nx][ny])continue;
        DFS(nx,ny);
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> grid[i][j];

    for (int i = 0; i < k; i++) {
        cin >> r[i] >> c[i];
        DFS(r[i]-1,c[i]-1);
    }

    // Please write your code here.
    cout<<ans;

    return 0;
}
