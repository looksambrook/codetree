#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

int N;
string str;
unordered_set<string> s;

int main() {
    cin >> N;
    cin >> str;

    // Please write your code here.
    bool is_break=true;
    int i=101;
    for(i=1;i<=N;++i){
        for(int j=0;j<=N-i;++j){
            string tmp="";
            for(int k=0;k<i;++k){
                tmp+=str[j+k];
            }
            if(s.find(tmp)!=s.end()){
                is_break=true;
                break;
            }
            s.insert(tmp);
            is_break=false;
        }
        if(!is_break)break;
    }
    cout<<i;

    return 0;
}