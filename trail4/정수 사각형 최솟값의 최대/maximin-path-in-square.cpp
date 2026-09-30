#include <iostream>
#include <algorithm>

using namespace std;

int n;
int grid[100][100];
int value[100][100];

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(i==0){
                if(j==0) value[0][0]=grid[0][0];
                else {
                    value[i][j]=min(value[i][j-1],grid[i][j]);
                }
            }
            else{
                if(j==0)value[i][j]=min(value[i-1][j],grid[i][j]);
                else value[i][j]=min(max(value[i-1][j],value[i][j-1]),grid[i][j]);
            }
        }
    }
    cout<<value[n-1][n-1];

    return 0;
}
