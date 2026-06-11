#include <iostream>
#include <vector>

using namespace std;

int n, m;
int ans=0;
int from[10000], to[10000];
bool visited[10000]={false, };
vector<int> v[10000];

void DFS(int x){
    visited[x]=true;
    for(int i:v[x]){
        if(visited[i])continue;
        DFS(i);
        ans++;
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        cin >> from[i] >> to[i];
        v[from[i]-1].push_back(to[i]-1);
        v[to[i]-1].push_back(from[i]-1);
    }

    // Please write your code here.
    DFS(0);
    cout<<ans;

    return 0;
}
