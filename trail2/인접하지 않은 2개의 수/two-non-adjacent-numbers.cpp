#include <iostream>

using namespace std;

int n;
int numbers[100];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> numbers[i];
    }

    // Please write your code here.
    int ans=0;
    for(int i=0;i<n-2;++i){
        for(int j=i+2;j<n;++j){
            ans=ans<numbers[i]+numbers[j]?numbers[i]+numbers[j]:ans;
        }
    }
    cout<<ans;

    return 0;
}