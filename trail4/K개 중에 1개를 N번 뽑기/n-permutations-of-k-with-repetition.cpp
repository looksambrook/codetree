#include <iostream>
#include <vector>

using namespace std;

int K, N;
vector<int> v;

void rec(int x){
    if(x==N) {
        for(int i:v)
            cout<<i<<" ";
        cout<<"\n";
        return;
    }
    for(int i=1;i<=K;++i){
        v.push_back(i);
        rec(x+1);
        v.pop_back();
    }
}

int main() {
    cin >> K >> N;

    // Please write your code here.
    rec(0);

    return 0;
}
