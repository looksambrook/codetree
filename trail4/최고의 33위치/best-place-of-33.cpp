#include <iostream>

using namespace std;

int N;
int grid[20][20];
int coin[17][17];

int main() {
    cin >> N;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
        }
    }

    // Please write your code here.
    int ans=0;
    for(int i=0;i<N-2;++i){
        for(int j=0;j<N-2;++j){
            int tmp=0;
            for(int n=0;n<3;++n){
                for(int m=0;m<3;++m){
                    tmp+=grid[n+i][m+j];
                }
            }
            if(ans<tmp)ans=tmp;
        }
    }
    cout<<ans;

    return 0;
}
