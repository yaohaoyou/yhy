#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e3+10,maxk=4e3+10;
int n,m,k;
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxk<<1;
    int cnt=1;
    int head[maxn<<1];
    struct edge{int nxt,to,w;}e[maxm];
    inline void adde(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void add(int u,int v,int w){adde(u,v,w);adde(v,u,w);}
}
using namespace Graph;
int c[maxn],d[maxn];
int col[maxn<<1];
bool dfs(int u,int fa){
    // printf("%d %d\n",u,fa);
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        if(~col[t]){
            if(col[t]!=(col[u]^e[i].w)){puts("NO");return false;}
        }
        else{
            col[t]=col[u]^e[i].w;
            if(!dfs(t,u))   return false;
        }
    }
    return true;
}
void solve(){
    scanf("%d%d%d",&n,&m,&k);
    int tot=0;cnt=1;
    for(int i=1;i<=n+m;i++)   col[i]=-1,head[i]=0;
    for(int i=1;i<n;i++)   c[i]=++tot;
    for(int i=1;i<m;i++)   d[i]=++tot;
    for(int i=1;i<=k;i++){
        int x,y,xx,yy;
        scanf("%d%d%d%d",&x,&y,&xx,&yy);
        x=min(x,xx);
        if(yy==y+1) add(c[x],d[min(y,yy)],1);
        else    add(c[x],d[min(y,yy)],0);
    }
    for(int i=1;i<=tot;i++){
        if(!~col[i]){col[i]=1;if(!dfs(i,0))return;}
    }
    puts("YES");
}
main(){int t;scanf("%d",&t);while(t--)solve();}