#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,mod=1e9+7;
bool mem1;
int n,m,k;
namespace Graph{
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    const int maxm=maxn<<1;
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
struct Trie{
    Trie *ls,*rs;
    void insert(Trie*& u,int d,int x){
        if(!u)  u=new Trie;
        if(!~d)   return;
        insert(x >> d & 1? u->ls : u->rs,d-1,x);
    }
    int dfs(Trie *u,int d,int val){
        if(!u->ls && !u->rs)  return val<=k;
        if(u->ls && u->rs)  return dfs(u->ls,d-1,val+(1<<d))+dfs(u->rs,d-1,val+(1<<d));
        if(u->ls){
            if(val+(1<<d)<=k)   return (1<<d)+dfs(u->ls,d-1,val+(1<<d));
            else    return dfs(u->ls,d-1,val);
        }else{
            if(val+(1<<d)<=k)   return (1<<d)+dfs(u->rs,d-1,val+(1<<d));
            else    return dfs(u->rs,d-1,val);
        }
    }
    static Trie __pool[maxn*20+10];
    static int __poolcnt;
    static void poolReset(){__poolcnt = 0;}
    void* operator new(size_t){
        Trie* res=&__pool[++__poolcnt];
        res->ls=res->rs=0;
        return res;
    }
};
Trie Trie::__pool[maxn*20+10];
int Trie::__poolcnt = 0;
bool vis[maxn];
int dis[maxn];
int ans=1;
bool mem2;
int main(){
    // printf("%.2lf MB\n",abs(&mem1-&mem2)/1024.0/1024.0);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    for(int i=1;i<=n;i++){
        if(vis[i])  continue;
        Trie::poolReset();
        Trie* rt = new Trie;
        function<void(int)> dfs=[&dfs,&rt](int u){
            rt->insert(rt,29,dis[u]);
            vis[u]=true;
            go(u,i){
                int t=e[i].to,w=e[i].w;
                if(vis[t]){
                    if(dis[t]^dis[u]^w) exit(puts("0")&0);
                    continue;
                }
                dis[t]=dis[u]^w;
                dfs(t);
            }
        };
        dfs(i);
        int x=rt->dfs(rt,29,0);
        mmul(ans,x);
    }
    printf("%d\n",ans);
}