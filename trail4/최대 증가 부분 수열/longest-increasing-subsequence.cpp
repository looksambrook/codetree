#include <iostream>

using namespace std;

int N;
int M[1000];
int val[1000];

int main() {
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> M[i];
    }

    // Please write your code here.
    int result=0;
    for(int i=0;i<N;++i){
        val[i]=1;
        int ans=0;
        for(int j=0;j<i;++j){
if(M[i]>M[j])ans=ans<val[j]?val[j]:ans;
        }
        val[i]+=ans;
        result=result<val[i]?val[i]:result;
    }
    cout << result;

    return 0;
}
