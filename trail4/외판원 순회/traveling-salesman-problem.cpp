#include <iostream>

using namespace std;

int n;
int A[10][10];
int ans=100000;
bool visited[10]={true, };

void DFS(int x, int current, int cpoint){
    if(current>=ans)return;
    if(x==n){
        if(A[cpoint][0]==0)return;
        current+=A[cpoint][0];
        ans=ans>current?current:ans;
        return;
    }
    for(int i=1;i<n;++i){
        if(visited[i])continue;
        if(A[cpoint][i]==0)continue;
        visited[i]=true;
        DFS(x+1,current+A[cpoint][i],i);
        visited[i]=false;
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> A[i][j];
        }
    }

    // Please write your code here.
    DFS(1,0,0);
    cout<<ans;

    return 0;
}
