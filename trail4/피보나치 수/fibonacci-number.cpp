#include <iostream>

using namespace std;

int N;
int fib[46]={0,1,};

int found(int x){
    if(fib[x]==0&&x!=0)fib[x]= found(x-2)+found(x-1);
    return fib[x];
}

int main() {
    cin >> N;

    // Please write your code here.
    cout<<found(N);

    return 0;
}
