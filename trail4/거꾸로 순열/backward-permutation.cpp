#include <iostream>

using namespace std;

int n;
int arr[8]={0,};
bool visited[8]={false, };

void DFS(int x){
    if(x==n){
        for(int i=0;i<n;++i){
            cout<<arr[i]<<" ";
        }
        cout<<"\n";
    }
    for(int i=n;i>0;--i){
        if(visited[i-1])continue;
        visited[i-1]=true;
        arr[x]=i;
        DFS(x+1);
        visited[i-1]=false;
    }
}

int main() {
    cin >> n;

    // Please write your code here.
    DFS(0);

    return 0;
}
