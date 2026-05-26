#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // Please write your code here.
    int ans=0;
    int i;
    for(i=0;i<10;++i){
        int tmp;
        cin>>tmp;
        if(tmp>=250)break;
        ans+=tmp;
    }
    cout<<fixed;
    cout<<setprecision(1);
    cout<<ans<<" "<<(float)ans/i;
    return 0;
}