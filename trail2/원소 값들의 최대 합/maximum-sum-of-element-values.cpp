#include <iostream>

using namespace std;

int n, m;
int arr[101];
int dp[10001][101];//count, index

void move(int cnt, int idx, int sum){
    if(dp[cnt][idx]>sum)return;
    dp[cnt][idx]=sum;
    if(cnt==m)return;
    move(cnt+1,arr[idx],sum+arr[idx]);
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    // Please write your code here.
    int ans=0;
    for(int i=1;i<=n;++i){
        move(1,arr[i],arr[i]);
        ans=ans<dp[m][i]?dp[m][i]:ans;
    }
    cout<<ans;

    return 0;
}