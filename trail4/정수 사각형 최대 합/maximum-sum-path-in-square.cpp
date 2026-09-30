#include <iostream>

using namespace std;

int n;
int grid[100][100];
int value[100][100];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    value[0][0] = grid[0][0];
    for(int i=0;i<n;++i){
        for(int j=0;j<n;++j){
            if(i==0){
                if(j!=0){
                    value[i][j]=value[i][j-1]+grid[i][j];
                }
            }
            else{
                if(j==0){
                    value[i][j]=value[i-1][j]+grid[i][j];
                }
                else{
                    int tmp=value[i-1][j]<value[i][j-1]?value[i][j-1]:value[i-1][j];
                    value[i][j]=tmp+grid[i][j];
                }
            }
        }
    }
    cout << value[n - 1][n - 1];

    return 0;
}
