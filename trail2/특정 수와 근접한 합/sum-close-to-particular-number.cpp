#include <iostream>
#include <climits>

using namespace std;

int N, S;
int sum;
int arr[100];

int main() {
    cin >> N >> S;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        sum+=arr[i];
    }

    // Please write your code here.
    int ans=INT_MAX;
    for(int i=0;i<N-1;++i){
        for(int j=i+1;j<N;++j){
            int tmp=sum-arr[i]-arr[j];
            ans=ans>abs(tmp-S)?abs(tmp-S):ans;
        }
    }
    cout<<ans;

    return 0;
}