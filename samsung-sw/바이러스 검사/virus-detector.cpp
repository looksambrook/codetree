#include <iostream>
#include <vector>
using namespace std;

int main() {
    int restaurant;
    vector<int> client;
    int tmp;

    cin>>restaurant;
    for(int i=0;i<restaurant;++i){
        cin>>tmp;
        client.push_back(tmp);
    }

    int leader, member;
    cin>>leader>>member;

    long long sum=0;
    for(int i=0;i<restaurant;++i){
        int people = client[i]-leader;
        sum++;
        if(people<=0)continue;
        sum+=(1+people/member);
        if(people%member==0)sum--;
    }    
    cout<<sum;

    return 0;
}