#include <iostream>

using namespace std;

int N, M;
int arr[10]={0,};

void DFS(int x,int last){
    if(x==M){
        for(int i=0;i<M;++i){
            cout<<arr[i]<<" ";
        }
        cout<<"\n";
        return;
    }
    
    for(int i=last+1;i<=N;++i){
        arr[x]=i;
        DFS(x+1,i);
    }
}

int main() {
    cin >> N >> M;

    // Please write your code here.
    DFS(0,0);

    return 0;
}
