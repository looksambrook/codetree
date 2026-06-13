#include <iostream>

using namespace std;

int n, m;
int a[100][100];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
bool visited[100][100]={false,};
int ans=10001;

void DFS(int cx,int cy,int score){
    if(ans<=score)return;
    if(cx==n-1&&cy==m-1){
        ans=score;
        return;
    }
    visited[cx][cy]=true;
    for(int i=0;i<4;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=m)continue;
        if(visited[nx][ny])continue;
        DFS(nx,ny,score+1);
    }
}
int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            if(a[i][j]==0)visited[i][j]=true;
        }
    }

    // Please write your code here.
    DFS(0,0,0);
    if(ans==10001)cout<<'0';
    else cout<<'1';

    return 0;
}
