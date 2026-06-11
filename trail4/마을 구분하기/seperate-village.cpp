#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
int grid[25][25];
bool visited[25][25];
int cnt=0;
int dx[4]={1,0,-1,0};
int dy[4]={0,1,0,-1};
vector<int> v;

void DFS(int cx, int cy){
    visited[cx][cy]=true;
    cnt++;
    for(int i=0;i<4;++i){
        int nx=cx+dx[i];
        int ny=cy+dy[i];
        if(nx<0||nx>=n||ny<0||ny>=n)continue;
        if(visited[nx][ny])continue;
        DFS(nx,ny);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if(grid[i][j]==0)visited[i][j]=true;
        }
    }

    // Please write your code here.
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(visited[i][j]==false){
                cnt=0;
                DFS(i,j);
                v.push_back(cnt);
            }
        }
    }
    sort(v.begin(),v.end());
    cout<<v.size()<<"\n";
    for(int i:v){
        cout<<i<<"\n";
    }

    return 0;
}
