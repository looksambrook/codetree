#include <iostream>
#include <stack>
using namespace std;

int main() {
    // Please write your code here.
    stack<int> st;
    for(int i=0;i<10;++i){
        int tmp;
        cin>>tmp;
        if(tmp==0)break;
        st.push(tmp);
    }
    while(!st.empty()){
        cout<<st.top()<<" ";
        st.pop();
    }
    return 0;
}