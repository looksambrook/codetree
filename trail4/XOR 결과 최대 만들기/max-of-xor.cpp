#include <iostream>

using namespace std;

int n, m;
int A[20];
int val,ans=0;

void DFS(int x, int last){
    if(x==m){
        ans=ans<val?val:ans;
        return;
    }
    if(last==n)return;

    DFS(x, last+1);
    val^=A[last];
    DFS(x+1, last+1);
    val^=A[last];
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    // Please write your code here.
    DFS(0,0);
    cout<<ans;
    return 0;
}