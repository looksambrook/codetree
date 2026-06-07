#include <iostream>

using namespace std;

int K, N;
int pri[8]={0,};

void DFS(int cnt, int prev, bool is_continue){
    if(cnt==N){
        for(int i=0;i<N;++i)
            cout<<pri[i]<<" ";
        cout<<"\n";
        return;
    }
    for(int i=1;i<=K;++i){
        bool fake_continue=is_continue;
        if(prev==i){
            if(is_continue)
                continue;
            else
                fake_continue=true;
        }
        else
            fake_continue=false;
        pri[cnt]=i;
        DFS(cnt+1, i, fake_continue);
    }
}

int main() {
    cin >> K >> N;

    // Please write your code here.
    DFS(0,0,false);

    return 0;
}
