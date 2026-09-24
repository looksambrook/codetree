#include <iostream>

using namespace std;

int n;
int x[20], y[20];
int arr[3];

bool func(int prev, int cnt){
    if(cnt==3){
        //확인했을때 다 들어돠?
        bool visited[21]={false,};
        int point=0;
        for(int i=0;i<3;++i){
            if(arr[i]<11){
                for(int j=0;j<n;++j){
                    if(visited[j])continue;
                    if(arr[i]==x[j]){
                        point++;
                        visited[j]=true;
                    }
                }
            }
            else{
                for(int j=0;j<n;++j){
                    if(visited[j])continue;
                    if(arr[i]-11==y[j]){
                        point++;
                        visited[j]=true;
                    }
                }
            }
        }
        if(point==n)return true;
        return false;
    }
    for(int i=prev+1;i<22;++i){
        arr[cnt]=i;
        if(func(i, cnt+1))return true;
    }
    return false;
}

int main() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }

    // Please write your code here.
    cout<<(int)func(-1,0);

    return 0;
}