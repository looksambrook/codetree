#include <iostream>

using namespace std;

int n;
int grid[10][10];
int ans=0;
bool visited[10]={false, };

void DFS(int x, int tmp_ans){
    if(ans>tmp_ans)return;
    if(x==n){
        ans=ans<tmp_ans?tmp_ans:ans;
        return;
    }
    for(int i=0;i<n;++i){
        if(visited[i])continue;
        visited[i]=true;
        int tmp=tmp_ans>grid[x][i]?grid[x][i]:tmp_ans;
        DFS(x+1,tmp);
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
    DFS(0, 10000);
    cout<<ans;

    return 0;
}
