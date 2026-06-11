#include <iostream>

using namespace std;

int n, m;
int grid[100][100];
bool visited[100][100]={false, };
bool is_escape=false;

int dx[2]={1,0};
int dy[2]={0,1};

void DFS(int cx,int cy){
    if(cx==n-1&&cy==m-1){
        is_escape=true;
        return;
    }
    visited[cx][cy]=true;
    for(int i=0;i<2;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=m)continue;
        if(visited[nx][ny])continue;
        DFS(nx,ny);
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if(grid[i][j]==0)
                visited[i][j]=true;
        }
    }

    // Please write your code here.
    DFS(0,0);
    if(is_escape)cout<<1;
    else cout<<0;

    return 0;
}
