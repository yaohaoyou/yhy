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
int n,m,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
struct Linear_Basis{
    int p[31];
    inline void ins(int x){
        #pragma unroll(4)
        for(int i=30;~i;i--){
            if(!(x&(1<<i))) continue;
            if(!p[i])   return p[i]=x,void();
            x^=p[i];
        }
    }
    inline int query(int x){
        int cnt=1,X=x;
        for(int i=30;~i;i--)
            if(x<(x^p[i]))  x^=p[i];
        return x;
    }
}lb;
int s[maxn],ss[maxn];
void dfs(int u,int ft){
    go(u,i){
        if(t==ft)   continue;
        s[t]=s[u]^w;
        dfs(t,u);
    }
}
namespace Sub1{
    void solve(){
        vector<int> vec;
        for(int i=1;i<=m;i++){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);
            if(u^v)    vec.eb(w);
            else lb.ins(w);
        }
        if(vec.size()>1){
            int T=4e6;
            while(T--){
                int x=rand()%vec.size(),y=rand()%vec.size();
                lb.ins(vec[x]^vec[y]);
            }
        }
        int ans=0;
        for(int i:vec)  ans=max(ans,lb.query(i));
        // for(int i=1;i<(1<<vec.size());i++){
        //     if(!(__builtin_popcount(i)&1))  continue;
        //     int sum=0;
        //     for(int j=0;j<vec.size();j++)if(i&(1<<j))sum^=vec[j];
        //     ans=max(ans,lb.query(sum));
        // }
        printf("%d\n",ans);
        exit(0);
    }
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    if(n==2&&q==1)    Sub1::solve();
    for(int i=1;i<=m;i++){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)   ss[i]=ss[i-1]^s[i];
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        if((r&1)^(l&1)) printf("%d\n",ss[r]^ss[l-1]);
        else    puts("0");
    }
}