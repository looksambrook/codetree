#include <iostream>

using namespace std;

int n, m;
int a[15], b[15];
int r=0;
int ans=150;
bool user[15][11]={false,};
int me[11];

int radder(int cx,int cy){
    if(cx==r)return cy;
    if(user[cx][cy])return radder(cx+1,cy+1);
    if(cy>0&&user[cx][cy-1])return radder(cx+1,cy-1);
    return radder(cx+1,cy);
}

void my_seq(){
    for(int i=0;i<n;++i){
        me[i]=radder(0,i);
    }
}

bool other_seq(){
    for(int i=0;i<n;++i){
        if(me[i]!=radder(0,i))
            return false;
    }
    return true;
}

void DFS(int x, int cnt){   //x==i번째 사다리, cnt==사다리 선택 횟수
    if(x==m){
        if(cnt==m){
            my_seq();
            ans=cnt;
            return;
        }
        if(other_seq())
            if(ans>cnt)ans=cnt;
        return;
    }
    //choose
    user[b[x]-1][a[x]-1]=true;
    DFS(x+1,cnt+1);
    user[b[x]-1][a[x]-1]=false;

    //not choose
    DFS(x+1,cnt);
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        if(r<b[i])r=b[i];
    }

    // Please write your code here.
    DFS(0,0);
    cout<<ans;

    return 0;
}
