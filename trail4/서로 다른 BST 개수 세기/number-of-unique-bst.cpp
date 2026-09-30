#include <iostream>

using namespace std;

int n;

int dp[20]={1,1,2,};

int main() {
    cin >> n;

    // Please write your code here.
    for(int i=3;i<=n;++i){
        int sum=0;
        for(int j=0;j<i;++j){
            sum+=dp[j]*dp[i-j-1];
        }
        dp[i]=sum;
    }
    cout<<dp[n];

    return 0;
}
