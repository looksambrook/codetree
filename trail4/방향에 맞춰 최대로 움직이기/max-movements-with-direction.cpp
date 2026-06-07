#include <iostream>

using namespace std;

int n;
int num[4][4];
int move_dir[4][4];
int r, c;
int ans=0;
int dx[8]={-1,-1,0,1,1,1,0,-1};
int dy[8]={0,1,1,1,0,-1,-1,-1};

void DFS(int cx,int cy,int cnt){
    int nx=cx,ny=cy;
    for(int i=0;i<n;++i){
        nx+=dx[move_dir[cx][cy]-1];
        ny+=dy[move_dir[cx][cy]-1];
        if(nx<0||nx>=n||ny<0||ny>=n){
            ans=ans<cnt?cnt:ans;
            continue;
        }
        if(num[nx][ny]<=num[cx][cy]){
            ans=ans<cnt?cnt:ans;
            continue;
        }
        DFS(nx,ny,cnt+1);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> num[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) cin >> move_dir[i][j];

    cin >> r >> c;

    // Please write your code here.
    DFS(r-1,c-1,0);
    cout<<ans;

    return 0;
}
