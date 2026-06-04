#include <iostream>

using namespace std;

string expression;
int blank[6]={0,};
int ans=-1000;
//+:0,-:1,*:2

void DFS(int x, int c, int summ){
    if(x==expression.size()){
        if(ans<summ)ans=summ;
        return;
    }
    if(expression[x]=='+'){
        DFS(x+1,0,summ);
        return;
    }
    if(expression[x]=='-'){
        DFS(x+1,1,summ);
        return;
    }
    if(expression[x]=='*'){
        DFS(x+1,2,summ);
        return;
    }
    if(blank[expression[x]-'a']!=0){
        if(c==0)
            DFS(x+1,c,summ+blank[expression[x]-'a']);
        else if(c==1)
            DFS(x+1,c,summ-blank[expression[x]-'a']);
        else
            DFS(x+1,c,summ*blank[expression[x]-'a']);
        return;
    }
    if(c==0){
        for(int i=1;i<=4;++i){
            blank[expression[x]-'a']=i;
            DFS(x+1,c,summ+i);
            blank[expression[x]-'a']=0;
        }
    }
    else if(c==1){
        for(int i=1;i<=4;++i){
            blank[expression[x]-'a']=i;
            DFS(x+1,c,summ-i);
            blank[expression[x]-'a']=0;
        }
    }
    else if(c==2){
        for(int i=1;i<=4;++i){
            blank[expression[x]-'a']=i;
            DFS(x+1,c,summ*i);
            blank[expression[x]-'a']=0;
        }
    }
}

int main() {
    cin >> expression;

    // Please write your code here.
    DFS(0,0,0);
    cout<<ans;

    return 0;
}
