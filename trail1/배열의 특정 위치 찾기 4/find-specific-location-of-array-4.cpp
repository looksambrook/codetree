#include <iostream>
using namespace std;

int main() {
    // Please write your code here.
    int cnt=0;
    int sum=0;
    bool iszero=false;
    for(int i=0;i<10;++i){
        int tmp;
        cin>>tmp;
        if(tmp==0)iszero=true;
        if(iszero)continue;
        if(tmp%2==0){
            cnt++;
            sum+=tmp;
        }
    }
    cout<<cnt<<" "<<sum;
    return 0;
}