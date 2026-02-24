#include<bits/stdc++.h>
#define ull unsigned ll
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
const int maxn=1e6+10;
int n,m;
int a[maxn],b[maxn],c[maxn];
unordered_set<int> st;
mt19937 Matt(time(0));
inline int rd(){return abs(int(Matt()));}
inline ull hsh(){ull res=0;for(int i=1;i<=n;i++)res=res*8594376298ull+a[i];return res;}
inline int calc(){int tot=0;mems(c,0);for(int i=1;i<=n;i++)tot+=(!c[a[i]]),c[a[i]]=1;return tot;}
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    void rebuild(){cnt=1;mems(head,0);}
}
using namespace Graph;
int dep[maxn],de;
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    if(dep[u]>dep[de])   de=u;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
    }
}
void matt(){
    rebuild();
    st.clear();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)if(a[i])adde(i,a[i]);
    for(int i=1;i<=n;i++)if(!a[i])de=0,dfs(i,0),a[i]=de;
    int cnt=0;
    while(m--){
        memc(b,a);
        for(int i=1;i<=n;i++)   a[i]=b[b[i]];
        int w=calc();
        if(st.find(w)!=st.end()){
            printf("%d\n",w);
            return;
        }
        st.ep(w);
    }
    printf("%d\n",calc());
}
int main(){int T;scanf("%d",&T);while(T--)matt();}