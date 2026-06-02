#include <iostream>

using namespace std;

int n;
int ans=0;

void rec(int x){
    if(x<=0){
        if(x==0)ans++;
        return;
    }
    rec(x-1);
    rec(x-2);
    rec(x-3);
    rec(x-4);
}

int main() {
    cin >> n;

    // Please write your code here.
    rec(n);
    cout<<ans;
    return 0;
}
