#include <iostream>

using namespace std;

int N;
int arr[20][20];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) cin >> arr[i][j];

    // Please write your code here.
    int ans=0;
    int first=0;
    for(int i=0;i<N;++i){
        int tmp=0;
        for(int j=0;j<N-2;++j){
            int a=arr[i][j]+arr[i][j+1]+arr[i][j+2];
            tmp=tmp<a?a:tmp;
            ans=ans<a+first?a+first:ans;
            for(int k=j+3;k<N-2;++k){
                int b=arr[i][k]+arr[i][k+1]+arr[i][k+2];
                ans=ans<a+b?a+b:ans;
            }
        }
        first=first<tmp?tmp:first;
    }
    cout<<ans;

    return 0;
}