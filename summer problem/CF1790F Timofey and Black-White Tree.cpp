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
const int maxn=2e5+10,B=1024;
int n;
int a[maxn],b[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){cnt=1;for(int i=1;i<=n;i++)head[i]=0;}
}
using namespace Graph;
int ans;
int fa[maxn],mnd[maxn],sed[maxn],dep[maxn],out[maxn];
int rnk[maxn],tot;
void dfs(int u,int ft){
    rnk[++tot]=u;
    dep[u]=dep[fa[u]=ft]+1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
    }
}
inline int calc(int x){
    if(out[x])return out[x];
    ans=1e9;
    for(int u=1;u<=n;u++)   mnd[u]=b[u]<=x?dep[u]:1e9,sed[u]=1e9;
    for(int i=n;i;i--){
        int u=rnk[i];
        ans=min(ans,mnd[u]+sed[u]-(dep[u]<<1));
        if(mnd[u]<mnd[fa[u]])   sed[fa[u]]=mnd[fa[u]],mnd[fa[u]]=mnd[u];
        else sed[fa[u]]=min(sed[fa[u]],mnd[u]);
    }
    return out[x]=ans;
}
void matt(){
    rebuild();for(int i=1;i<=n;i++)out[i]=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[a[i]]=i;
    for(int i=1,u,v;i<n;i++){scanf("%d%d",&u,&v);adde(u,v);}
    tot=0;dfs(1,0);
    for(int i=2;i<=min(B,n);i++)    calc(i);
    for(int lst=min(B,n);lst<n;){
        int i=calc(lst+1);
        int l=lst+2,r=min(n,2*n/i+1),p=lst+1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(calc(mid)==i)  p=mid,l=mid+1;
            else    r=mid-1;
        }
        for(int j=lst+1;j<=p;j++)   out[j]=i;
        lst=p;
    }
    for(int i=2;i<=n;i++)   printf("%d ",out[i]);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}