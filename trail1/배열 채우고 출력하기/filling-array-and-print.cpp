#include <iostream>
#include <stack>
using namespace std;

int main() {
    // Please write your code here.
    stack<char> st;
    for(int i=0;i<10;++i){
        char tmp;
        cin>>tmp;
        st.push(tmp);
    }
    for(int i=0;i<10;++i){
        cout<<st.top();
        st.pop();
    }
    return 0;
}