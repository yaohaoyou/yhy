#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define piiii pair<pii,pii>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=1010,maxm=5e5+10,maxq=1010;
int n,m,q,len;
int W[maxm],d[maxm];
piiii G[maxm];
namespace DSU{
    int fa[maxn<<1];
    inline void init(){for(int i=1;i<=n<<1;i++)fa[i]=i;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}
using DSU::merge;
void discrete(){
    memc(d,W);
    sort(d+1,d+m+1);
    len=unique(d+1,d+m+1)-d-1;
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    if(m==n-1){
        while(q--)  puts("-1");
        exit(0);
    }
    for(int i=1,u,v,w;i<=m;i++){
        scanf("%d%d%d",&u,&v,&w);
        G[i]=piiii(pii(w,i),pii(u,v));
        W[i]=w;
    }
    discrete();
    sort(G+1,G+m+1,greater<piiii>());
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        int ans=0;
        DSU::init();
        for(int i=1;i<=m;i++){
            if(G[i].fi.se>=l&&G[i].fi.se<=r){
                int u=G[i].se.fi,v=G[i].se.se;
                merge(u+n,v);merge(u,v+n);
                if(DSU::find(u)==DSU::find(u+n)){ans=G[i].fi.fi;break;}
                if(DSU::find(v)==DSU::find(v+n)){ans=G[i].fi.fi;break;}
            }
        }
        if(!ans)    puts("-1");
        else    printf("%d\n",ans);
    }
}