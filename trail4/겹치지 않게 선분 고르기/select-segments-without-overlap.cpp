#include <iostream>

using namespace std;

int n;
int ans=0;
int x1[15], x2[15];
bool check[1000]={false, };

void DFS(int x,int cnt){
    if(x==n){
        if(ans<cnt)ans=cnt;
        return;
    }

    //write true
    bool is_false=true;
    for(int i=x1[x]-1;i<x2[x];++i){
        if(check[i]){
            is_false=false;
            break;
        }
    }
    if(is_false){
        for(int i=x1[x]-1;i<x2[x];++i){
            check[i]=true;
        }
        DFS(x+1,cnt+1);
        //false back
        for(int i=x1[x]-1;i<x2[x];++i){
            check[i]=false;

        }
    }

    //not choice
    DFS(x+1,cnt);
    return;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x1[i] >> x2[i];
    }

    // Please write your code here.
    DFS(0,0);
    cout<<ans;

    return 0;
}
