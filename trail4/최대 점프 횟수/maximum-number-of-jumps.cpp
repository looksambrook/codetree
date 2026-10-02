#include <iostream>

using namespace std;

int n;
int arr[1000];
int dp[1000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Please write your code here.
    int result=0;
    for(int i=0;i<n;++i){
        dp[i]=0;
        int ans=0;
        for(int j=0;j<i;++j){
            if(i-j<=arr[j])ans=ans<=dp[j]?dp[j]+1:ans;
        }
        dp[i]+=ans;
        if(dp[i]==0&&i!=0)break;
        result=result<dp[i]?dp[i]:result;
    }
    cout<<result;

    return 0;
}
