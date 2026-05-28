#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Please write your code here.
    cout<<fixed;
    cout<<setprecision(1);
    float score;
    float sum=0;
    for(int i=0;i<8;++i){
        cin>>score;
        sum+=score;
    }
    cout<<sum/8;
    return 0;
}