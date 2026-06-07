#include <iostream>

using namespace std;

int n, m, k;
int nums[12];
int ans=0;
int point[4]={0,};

void DFS(int cnt){
    if(cnt==n){
        return;
    }
  
    for(int i=0;i<k;++i){
        if(point[i]>m-2)continue;

        bool is_duplicate=false;  
        for(int j=i+1;j<k;++j){
            if(point[i]==point[j]){
                is_duplicate=true;
                break;
            }
        }
        if(is_duplicate)
            continue;

        point[i]+=nums[cnt];
        int tmp=0;
        for(int i=0;i<k;++i){
            if(point[i]>m-2)tmp++;
        }
        ans=ans<tmp?tmp:ans;
        DFS(cnt+1);
        point[i]-=nums[cnt];
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // Please write your code here.
    DFS(0);
    cout<<ans;

    return 0;
}

