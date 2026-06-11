#include <iostream>

using namespace std;

int n;
int arr[80];

bool backtrack(int x){
    if(x==n){   //만약에 arr이 제대로 저장되지 않는다면 bool을 넣어서 그대로 멈추게 해야함
        return true;
    }

    for(int i=0;i<3;++i){
        arr[x]=i;
        //들어갔을 때 가능한 수열인지 확인하는 함수 필요
        if(x!=0){
            bool is_unable=true;
            for(int digits=1;(x-2*digits+1)>=0;++digits){
                is_unable=true;
                for(int d=x-2*digits+1;d<x-digits+1;++d){
                    if(arr[d]!=arr[d+digits]){
                        is_unable=false;
                        break;
                    }
                }
                if(is_unable)break;
            }
            if(is_unable)continue;
        }   
        if(backtrack(x+1))return true;
    }
    return false;
}

int main() {
    cin >> n;

    // Please write your code here.
    backtrack(0);
    for(int i=0;i<n;++i){
        cout<<arr[i]+4;
    }

    return 0;
}
