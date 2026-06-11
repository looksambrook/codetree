#include <iostream>

using namespace std;

int n;
int num[10];
int ans=100;

void backtrack(int x, int idx){
    if(ans<=x)return;
    if(idx>=n-1){
        ans=ans>x?x:ans;
        return;
    }
    for(int i=1;i<=num[idx];++i){
        if(idx+i>n-1)break;
        backtrack(x+1,idx+i);
    }
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    // Please write your code here.
    backtrack(0,0);
    if(ans==100)cout<<-1;
    else cout<<ans;

    return 0;
}
