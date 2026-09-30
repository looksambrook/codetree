#include <iostream>

using namespace std;

int n;
int dp[1001]={1,1,3,};
int func(int x){
    if(dp[x]==-1)dp[x]=(func(x-1)+func(x-2)*2)%10007;
    return dp[x];
}

int main() {
    cin >> n;

    // Please write your code here.
    for(int i=3;i<=n;++i) dp[i]=-1;
    cout<<func(n);

    return 0;
}
