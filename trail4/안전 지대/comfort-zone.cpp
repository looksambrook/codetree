#include <iostream>

using namespace std;

int N, M;
int grid[50][50];
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int visited[50][50]={0,};
int lock=0;

void DFS(int cx,int cy){
    visited[cx][cy]=lock;
    for(int i=0;i<4;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=N||ny<0||ny>=M)continue;
        if(grid[nx][ny]<=lock)continue;
        if(visited[nx][ny]==lock)continue;
        DFS(nx,ny);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    int max_height=0;

    cin >> N >> M;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> grid[i][j];
            max_height=max_height<grid[i][j]?grid[i][j]:max_height;
        }
    }

    // Please write your code here.
    int ans=0,idx=1;
    for(int i=1;i<=max_height;++i){
        lock=i;
        int tmp=0;
        for(int row=0;row<N;++row){
            for(int col=0;col<M;++col){
                if(grid[row][col]<=lock)continue;
                if(visited[row][col]==lock)continue;
                DFS(row,col);
                tmp++;
            }
        }
        if(ans<tmp){
            ans=tmp;
            idx=i;
        }
    }
    cout<<idx<<" "<<ans;

    return 0;
}
