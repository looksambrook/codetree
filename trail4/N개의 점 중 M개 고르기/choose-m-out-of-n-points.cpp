#include <iostream>

using namespace std;

int n, m;
int x[20], y[20];
int candidate[20];
int ans=20000;

void back_track(int cnt, int idx){
    if(cnt==m){
        int tmp_min=0;
        for(int i=0;i<m;++i){
            for(int j=i+1;j<m;++j){
                int dx=x[candidate[i]]-x[candidate[j]];
                int dy=y[candidate[i]]-y[candidate[j]];
                int tmp=dx*dx+dy*dy;
                tmp_min=tmp_min<tmp?tmp:tmp_min;
            }            
        }
        ans=ans>tmp_min?tmp_min:ans;
        return;
    }
    for(int i=idx+1;i<n;++i){
        candidate[cnt]=i;
        back_track(cnt+1, i);
    }
}

int main() {
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // Please write your code here.
    back_track(0,-1);
    cout<<ans;

    return 0;
}
