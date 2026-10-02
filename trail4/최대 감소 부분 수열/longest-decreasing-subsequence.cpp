#include <iostream>

using namespace std;

const int MAX_N = 1000;

int N;
int M[MAX_N];
int dp[MAX_N];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> M[i];
    }

    // Please write your code here.
    int result=0;
    for(int i=0;i<N;++i){
        dp[i]=1;
        int ans=0;
        for(int j=0;j<i;++j){
            if(M[j]>M[i])ans=ans<dp[j]?dp[j]:ans;
        }
            dp[i]+=ans;
        result=result<dp[i]?dp[i]:result;
    }
    cout<<result;

    return 0;
}
