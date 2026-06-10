#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
char grid[20][20];
struct Coin{
    int x;
    int y;
    int val;
};
int point_cnt=0;
int ans=500;
int final_x, final_y;
vector<Coin> arr;

bool cmp(const Coin& a, const Coin& b){
    return a.val<b.val;
}

int get_distance(int ax, int ay, int bx, int by){
    int x=ax>bx?ax-bx:bx-ax;
    int y=ay>by?ay-by:by-ay;
    return x+y;
}

void DFS(int x, int idx, int cscore){
    if(x==3){
        cscore+=get_distance(arr[idx].x,arr[idx].y,final_x,final_y);
        ans=ans>cscore?cscore:ans;
        return;
    }
    for(int i=idx+1;i<=point_cnt;++i){
        if(arr[i].val<=arr[idx].val)continue;
        DFS(x+1,i,cscore+get_distance(arr[idx].x,arr[idx].y,arr[i].x,arr[i].y));
    }
}

int main() {
    int cx,cy;
    cin >> N;

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            cin >> grid[i][j];
            if(grid[i][j]=='.')continue;
            if(grid[i][j]=='S'){
                arr.push_back({i,j,0});
            }
            else if(grid[i][j]=='E'){
                final_x=i,final_y=j;
            }
            else{
                point_cnt++;
                arr.push_back({i,j,grid[i][j]-'0'});
            }
        }

    // Please write your code here.
    if(point_cnt<3)cout<<-1;
    else{
        sort(arr.begin(),arr.end(),cmp);
        DFS(0,0,0);
        if(ans==500)cout<<-1;
        else cout<<ans;
    }

    return 0;
}
