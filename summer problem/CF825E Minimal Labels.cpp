#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1e5+10;
int n,m;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){cnt=1;mems(head,0);mems(deg,0);}
}
using namespace Graph;
int ans[maxn];
priority_queue<int> q;
void topu(){
    int tot=n;
    for(int i=1;i<=n;i++)
        if(!deg[i]) q.ep(i);
    while(!q.empty()){
        int u=q.top();q.pop();
        ans[u]=tot--;
        go(u,i){
            int t=e[i].to;
            if(!(--deg[t])) q.ep(t);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(v,u);}
    topu();
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}