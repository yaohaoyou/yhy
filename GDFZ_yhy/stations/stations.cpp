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
const int maxn=7e4+10;
int n,k;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int siz[maxn],son[maxn],fa[maxn],upw[maxn];
mt19937 matt(20251220);
namespace FHQTreap{
    int tot,rt;
    int ls[maxn],rs[maxn],val[maxn],rd[maxn],sz[maxn];
    int mem[maxn],tp;
    inline int nd(int v){int p=tp?mem[tp--]:++tot;val[p]=v;rd[p]=matt();sz[p]=1;return p;}
    inline void era(int p){mem[++tp]=p;val[p]=ls[p]=rs[p]=rd[p]=0;}
    inline void pu(int p){sz[p]=sz[ls[p]]+sz[rs[p]]+1;}
    int merge(int p,int q){
        if(!p||!q)  return p|q;
        if(rd[p]>rd[q]) return rs[p]=merge(rs[p],q),pu(p),p;
        else    return ls[q]=merge(p,ls[q]),pu(q),q;
    }
    void split(int p,int v,int &x,int &y){
        if(!p)  return x=y=0,void();
        if(v<val[p])    split(ls[p],v,x,ls[y=p]);
        else    split(rs[p],v,rs[x=p],y);
    }
    void clear(int p){if(!p)return;clear(ls[p]);clear(rs[p]);era(p);}
    inline void ins(int v){int x,y=nd(v),z;split(rt,v,x,z);rt=merge(merge(x,y),z);}
}
using namespace FHQTreap;
int sum;
ll ans[maxn];
struct node{
    map<ll,int> mp;ll tag;
    node(map<ll,int> x=map<ll,int>(),int y=0){mp=x;tag=y;}
    inline void swp(node &x){mp.swap(x.mp);swap(tag,x.tag);}
    inline void merge(node &x){
        if(mp.size()<x.mp.size())   this->swp(x);
        for(auto [i,j]:x.mp)  mp[i+x.tag-tag]+=j;
    }
    inline void M(node x){
        if(mp.size()<x.mp.size())   this->swp(x);
        for(auto [i,j]:x.mp)  mp[i+x.tag-tag]+=j;
    }
    inline void erase(node x){
        for(auto [i,j]:x.mp){
            if(mp[i+x.tag-tag]==j)  mp.erase(i+x.tag-tag);
            else mp[i+x.tag-tag]-=j;
        }
    }
    inline void ins(int x){mp[x-tag]++;}
    inline node& rem(int x){
        tag-=x;
        vector<int> vec;sum=0;
        for(auto [i,j]:mp){
            if(i+tag<0) vec.eb(i),sum+=j;
            else break;
        }
        for(int i:vec)  mp.erase(i);
        if(sum) mp[k-x-tag]+=sum;
        return *this;
    }
};
void dfs(int u,int ft){
    siz[u]=1;fa[u]=ft;
    go(u,i){
        if(t==ft)   continue;
        upw[t]=w;
        dfs(t,u);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
node getmp(int u,int ft){
    node res=node();
    go(u,_)if(t^ft)res.merge(getmp(t,u).rem(w));
    res.ins(k);
    return res;
}
node dfs1(int u,int ft){
    node res=node();
    go(u,_)if(t^ft){res.merge(dfs1(t,u).rem(w));ans[t]+=1ll*sum*(n-siz[t]);}
    res.ins(k);
    return res;
}
node ND;
node dfs2(int u,int ft){
    if(1){
        go(u,i)if((t^ft)&&(t^son[u]))ND.merge(getmp(t,u).rem(w));
        ND.ins(k);
        node res=node();
        if(son[u]){
            node clr=ND;
            ND.rem(upw[son[u]]);ans[u]+=1ll*sum*siz[son[u]];
            node tmp=dfs2(son[u],u);
            res.swp(tmp.rem(upw[son[u]]));
            ND.swp(clr);ND.M(res);
        }
        node clr=ND;
        go(u,i)if((t^ft)&&(t^son[u])){
            node tmp=getmp(t,u).rem(w);
            ND.erase(tmp);res.merge(tmp);
            ND.rem(w);ans[u]+=1ll*sum*siz[t];
            dfs2(t,u);
            ND=clr;
        }
        res.ins(k);
        return res;
    }
    else{
        go(u,i)if(t^ft)ND.merge(getmp(t,u).rem(w));
        ND.ins(k);
        node res=node(),clr=ND;
        go(u,i)if(t^ft){
            ND.erase(getmp(t,u).rem(w));
            ND.rem(w);ans[u]+=1ll*sum*siz[t];
            dfs2(t,u);
            ND=clr;
        }
        return res;
    }
}
int main(){
    freopen("stations.in","r",stdin);freopen("stations.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;i++){int u,v,w;scanf("%d%d%d",&u,&v,&w);adde(++u,++v,w);}
    dfs(1,0);
    dfs1(1,0);dfs2(1,0);
    // for(int i=1;i<=n;i++){
    //     int u=i,now=k;
    //     while(u){
    //         if(now<upw[u])  ans[u]-=n-siz[u],now=k;
    //         now-=upw[u];
    //         u=fa[u];
    //     }
    // }
    for(int i=1;i<=n;i++)   printf("%lld\n",ans[i]);
    // for(int i=1;i<=n;i++)   assert(!ans[i]);
}