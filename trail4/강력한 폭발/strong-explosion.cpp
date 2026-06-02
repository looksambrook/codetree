#include <iostream>
#include <vector>

using namespace std;

int n;
int grid[20][20];
int ans=0;
struct point{
    int x;
    int y;
};
vector<point> p;
int df[4]={-2,-1,1,2};
int dx[8]={-1, 1, 0, 0, -1, -1, 1, 1};
int dy[8]={0, 0, -1, 1, -1, 1, -1, 1};

void DFS(int data){
    if(data==p.size()){
        int tmp=0;
        for(int i=0;i<n;++i){
            for(int j=0;j<n;++j){
                if(grid[i][j]==1){
                    tmp++;
                }
            }
        }
        if(ans<tmp)ans=tmp;
        return;
    }
    int cx=p[data].x, cy=p[data].y;
    vector<point> tmp_boom;

    //1 square
    for(int i=0;i<4;++i){
        int nx=cx+df[i];
        if(nx<0||nx>=n||grid[nx][cy])continue;
        grid[nx][cy]=1;
        tmp_boom.push_back({nx,cy});
    }
    DFS(data+1);
    //1 square back
    for(auto i:tmp_boom){
        grid[i.x][i.y]=0;
    }
    tmp_boom.clear();

    //2 square
    for(int i=0;i<4;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=n||grid[nx][ny])continue;
        grid[nx][ny]=1;
        tmp_boom.push_back({nx,ny});
    }
    DFS(data+1);
    //2 square back
    for(auto i:tmp_boom){
        grid[i.x][i.y]=0;
    }
    tmp_boom.clear();

    //3 square
    for(int i=4;i<8;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=n||grid[nx][ny])continue;
        grid[nx][ny]=1;
        tmp_boom.push_back({nx,ny});
    }
    DFS(data+1);
    //3 square back
    for(auto i:tmp_boom){
        grid[i.x][i.y]=0;
    }
    tmp_boom.clear();

    return;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if(grid[i][j]==1)
                p.push_back({i,j});
        }
    }

    // Please write your code here.
    ans=p.size();
    DFS(0);
    cout<<ans;
    return 0;
}
