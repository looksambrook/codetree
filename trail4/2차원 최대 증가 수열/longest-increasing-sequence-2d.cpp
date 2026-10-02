#include <iostream>

using namespace std;

int n, m;
int grid[50][50];
    int dp[50][50];

int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    int result=0;
    for(int i=0;i<n;++i){
        for(int j=0;j<m;++j){
            if(i==0&&j!=0||i!=0&&j==0)continue;
            if(i!=0&&j!=0&&dp[i][j]==0)continue;
            for(int r=i+1;r<n;++r){
                for(int c=j+1;c<m;++c){
                    if(grid[r][c]>grid[i][j])dp[r][c]=dp[r][c]<dp[i][j]+1?dp[i][j]+1:dp[r][c];
                }
            }
            result=result<dp[i][j]?dp[i][j]:result;
    }
    }
    cout<<result+1;

    return 0;
}
