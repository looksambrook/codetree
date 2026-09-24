#include <iostream>
#include <string>

using namespace std;

string a;

int main() {
    cin >> a;

    // Please write your code here.
    long long ans=0;
    bool is_change=false;
    for(int i=0;i<a.size();++i){
        if(!is_change&&a[i]=='0'){
            is_change=true;
            a[i]='1';
        }
        if(a[i]=='0')continue;
        int tmp=1;
        for(int j=a.size()-1;j>i;--j)tmp*=2;
        ans+=tmp;
    }
    if(!is_change)ans--;
    cout<<ans;

    return 0;
}