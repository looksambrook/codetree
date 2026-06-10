#include <iostream>

using namespace std;

int n;
int num[20];
int total=0;
int oppo=0;
int ans=20000;

void DFS(int x,int idx){
    if(x==n){
        int tmp=oppo>total?oppo-total:total-oppo;
        ans=ans>tmp?tmp:ans;
        return;
    }
    for(int i=idx+1;i<2*n;++i){
        oppo+=num[i];
        total-=num[i];
        DFS(x+1,i);
        total+=num[i];
        oppo-=num[i];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        cin >> num[i];
        total+=num[i];
    }

    // Please write your code here.
    DFS(0,-1);
    cout<<ans;
    return 0;
}
