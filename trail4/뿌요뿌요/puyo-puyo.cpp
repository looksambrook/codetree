#include <iostream>

using namespace std;

int n;
int grid[100][100];
int ans=0;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
int stan,bomb;
bool visited[100][100]={false,};

void DFS(int cx,int cy){
    stan++;
    visited[cx][cy]=true;
    for(int i=0;i<4;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=n)continue;
        if(visited[nx][ny])continue;
        if(grid[cx][cy]!=grid[nx][ny])continue;
        DFS(nx,ny);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(visited[i][j])continue;
            stan=0;
            DFS(i,j);
            if(ans<stan){
                ans=stan;
            }
            if(stan>3)bomb++;
        }
    }
    cout<<bomb<<" "<<ans;

    return 0;
}
