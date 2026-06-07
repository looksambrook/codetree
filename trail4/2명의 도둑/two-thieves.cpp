#include <iostream>

using namespace std;

int n, m, c;
int weight[10][10];
int tmp[10]={0,};
int target, start;
int tmp_best;

void DFS(int seq, int sum, int squa){
    if(seq==m){
        if(tmp_best<squa)
            tmp_best=squa;
        if(tmp[start]<squa)
            tmp[start]=squa;
        return;
    }

    if((sum+weight[target][start+seq])<=c)
        DFS(seq+1, sum+weight[target][start+seq], squa+(weight[target][start+seq]*weight[target][start+seq]));

    DFS(seq+1, sum, squa);
    return;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin >> n >> m >> c;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> weight[i][j];
        }
    }

    // Please write your code here.
    int ans=0;
    int previous_best=0;
    for(int i=0;i<n;++i){
        target=i;
        tmp_best=0;

        for(int j=0;j<=n-m;++j){
            start=j;
            tmp[start]=0;
            DFS(0, 0, 0);
        }

        int best=0, good=0, second=0, first=0;
        for(int j=0;j<=n-m;++j){
            first=tmp[j];
            second=0;
            for(int k=0;k<=j-m;++k){
                if(second<tmp[k])second=tmp[k];
            }
            for(int k=j+m;k<=n-m;++k){
                if(second<tmp[k])second=tmp[k];
            }
            if((best+good)<(second+first)){
                if(first<second){
                    best=second;
                    good=first;
                }
                else{
                    best=first;
                    good=second;
                }
            }
        }

        if(ans<(previous_best+tmp_best))
            ans=previous_best+tmp_best;
        if(ans<(best+good))
            ans=best+good;
            
        if(previous_best<tmp_best)previous_best=tmp_best;
    }

    cout<<ans;

    return 0;
}