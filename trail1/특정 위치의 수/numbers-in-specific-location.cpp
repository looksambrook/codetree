#include <iostream>
using namespace std;

int main() {
    // Please write your code here.
    int sum=0;
    for(int i=0;i<10;++i){
        int tmp;
        cin>>tmp;
        if(i==2||i==4||i==9)sum+=tmp;
    }
    cout<<sum;
    return 0;
}