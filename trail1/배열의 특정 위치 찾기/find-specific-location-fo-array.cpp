#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Please write your code here.
    int sum=0,mean=0;
    for(int i=0;i<10;++i){
        int tmp;
        cin>>tmp;
        if(i%2)sum+=tmp;
        if((i+1)%3==0)mean+=tmp;
    }
    cout<<fixed;
    cout<<setprecision(1);
    cout<<sum<<" "<<(float)mean/3;
    return 0;
}