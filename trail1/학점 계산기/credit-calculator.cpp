#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // Please write your code here.
    int N;
    cin>>N;
    float sum=0,score;
    for(int i=0;i<N;++i){
        cin>>score;
        sum+=score;
    }
    cout<<fixed;
    cout<<setprecision(1);
    sum/=N;
    cout<<sum<<"\n";
    if(sum>=4.0)cout<<"Perfect";
    else if(sum>=3.0)cout<<"Good";
    else cout<<"Poor";
    return 0;
}