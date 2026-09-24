#include <iostream>

using namespace std;

int A, B, C;
int ans=0;
bool visited[1001]={false,};

void func(int sum){
    if(sum>C)return;
    if(visited[sum])return;
    visited[sum]=true;
    if(ans<sum)ans=sum;
    func(sum+A);
    func(sum+B);
}

int main() {
    cin >> A >> B >> C;

    // Please write your code here.
    func(0);
    cout<<ans;

    return 0;
}