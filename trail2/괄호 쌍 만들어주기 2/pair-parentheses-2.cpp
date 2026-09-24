#include <iostream>
#include <string>

using namespace std;

string A;

int main() {
    int cnt=0;
    int ans=0;
    cin >> A;

    // Please write your code here.
    for(int i=0;i<A.size()-1;++i){
        if(A[i]==A[i+1]){
            if(A[i]=='(')cnt++;
            else ans+=cnt;
        }
    }
    cout<<ans;

    return 0;
}