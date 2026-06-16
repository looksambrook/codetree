#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int n, k;
int grid[100][100];
int r, c;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
struct Info{
    int x;
    int y;
};
Info ans;

bool cmp(const Info& a,const Info& b){ 
    if(grid[a.x][a.y]!=grid[b.x][b.y])
        return grid[a.x][a.y] > grid[b.x][b.y];
    if(a.x!=b.x)return a.x<b.x;
    return a.y<b.y;
}

bool BFS(Info& current){
    queue<Info> q;
    Info stan;
    bool is_stan=false;
    bool visited[100][100]={false, };
    q.push(current);
    visited[current.x][current.y]=true;

    while(!q.empty()){
        int cx = q.front().x;
        int cy = q.front().y;
        q.pop();

        for(int i=0;i<4;++i){
            int nx=cx+dx[i];
            int ny=cy+dy[i];
            if(nx<0||nx>=n||ny<0||ny>=n)continue;
            if(visited[nx][ny])continue;
            if(grid[ans.x][ans.y]<=grid[nx][ny])continue;
            visited[nx][ny]=true;
            q.push({nx,ny});
            if(!is_stan||cmp({nx,ny}, stan)){
                stan={nx,ny};
                is_stan=true;
            }
        }
    }
    if(!is_stan)return false;

    ans=stan;
    return true;
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    cin >> r >> c;

    // Please write your code here.
    ans={r-1,c-1};
    for(int i=0;i<k;++i){
        if(!BFS(ans))
            break;        
    }
    cout<<ans.x+1<<" "<<ans.y+1;

    return 0;
}
