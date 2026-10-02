#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info{
    int first;
    int second;
    bool operator<(const Info&other)const{
        if(second!=other.second) return second>other.second;
        return first>other.first;
    }
};

int n;
int x1[1000];
int x2[1000];
vector<Info> data;
int dp[1000];

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x1[i] >> x2[i];
        data.push_back({x1[i],x2[i]});
    }
sort(data.begin(),data.begin()+n);
    // Please write your code here.
    int result=0;
    for(int i=0;i<n;++i){
        dp[i]=1;
        int ans=0;
        for(int j=0;j<i;++j){
            if(data[j].second<data[i].first||data[j].first>data[i].second)ans=ans<dp[j]?dp[j]:ans;
        }
        dp[i]+=ans;
        result=result<dp[i]?dp[i]:result;
    }
cout<<result;

    return 0;
}
