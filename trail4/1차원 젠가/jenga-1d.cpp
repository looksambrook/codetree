#include <iostream>

using namespace std;

int n;
int blocks[100];
int s1, e1;
int s2, e2;

void erase_array(int start,int end){
    int tmp[100];
    int tcnt=0;

    for(int i=0;i<n;++i){
        if(i<start-1||i>=end){
            tmp[tcnt++]=blocks[i];
        }
    }
    n=tcnt;
    for(int i=0;i<tcnt;++i){
        blocks[i]=tmp[i];
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> blocks[i];
    }
    cin >> s1 >> e1;
    cin >> s2 >> e2;
    // Please write your code here.
    erase_array(s1,e1);
    erase_array(s2,e2);

    cout<<n<<"\n";
    for(int i=0;i<n;++i)
        cout<<blocks[i]<<"\n";

    return 0;
}
