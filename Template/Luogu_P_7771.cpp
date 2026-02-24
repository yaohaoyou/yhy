//  P7771 【模板】欧拉路径
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10,maxm=4e5+10;
int n,m;
vector<int> son[maxn];
#define eb emplace_back
int in[maxn],out[maxn];
inline void add(int u,int v){son[u].eb(v);out[u]++;in[v]++;}
int S,T;
inline void NO(){exit(puts("No")&0);}
int now[maxn];
stack<int>stk;
int output[maxn];
void dfs(int u){
    for(int i=now[u];i<son[u].size();i=now[u]){
        now[u]=i+1;
        int t=son[u][i];
        dfs(t);
    }
    stk.push(u);
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++){
        scanf("%d%d",&u,&v);add(u,v);
    }
    for(int i=1;i<=n;i++){
        sort(son[i].begin(),son[i].end());
        if(out[i]-in[i]==1){if(S)NO();S=i;}
        else if(in[i]-out[i]==1){if(T)NO();T=i;}
        else if(abs(in[i]-out[i])>1)    NO();
    }
    if(!S)  S=1,T=1;
    dfs(S);
    if(stk.size()!=m+1) NO();
    while(stk.size())   printf("%d ",stk.top()),stk.pop();
    puts("");
}