#include <iostream>
#include <stack>
using namespace std;

int main() {
    // Please write your code here.
    int N;
    stack<int> st;
    cin>>N;

    for(int i=0;i<N;++i){
        int num;
        cin>>num;
        if(num%2==0)st.push(num);
    }
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}