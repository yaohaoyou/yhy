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
const int maxn=510;
int n;
int l[maxn],r[maxn];
namespace Graph{
    const int maxm=maxn*maxn;
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
void matt(){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&l[i],&r[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(l[i]<l[j]&&r[j]<r[i])    add(i,j);
    topu();
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}