#include <iostream>

using namespace std;

int n;
int grid[10][10];
int ans=0;
bool visited[10]={false, };

void DFS(int x,int cnt){
    if(x==n){
        ans=ans<cnt?cnt:ans;
        return;
    }
    for(int i=0;i<n;++i){
        if(visited[i])continue;
        visited[i]=true;
        DFS(x+1,cnt+grid[x][i]);
        visited[i]=false;
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
    DFS(0,0);
    cout<<ans;
    
    return 0;
}
