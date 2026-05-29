#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Please write your code here.
    int iszero=10;
    int sum=0;
    for(int i=0;i<10;++i){
        int tmp;
        cin>>tmp;
        if(iszero!=10)continue;
        if(tmp==0)iszero=i;
        sum+=tmp;
    }
    cout<<fixed;
    cout<<setprecision(1);
    cout<<sum<<" "<<(float)sum/iszero;
    return 0;
}