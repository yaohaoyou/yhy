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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10,maxq=2e5+10;
int n,q;
ll ans[maxq];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
struct BIT{
    ll tr[maxn];
    inline ll lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline void upd(int l,int r,int s){if(l>r||l<=0||r>n)return;add(l,s);add(r+1,-s);}
    // inline ll query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T[2];
struct odt{
    int l,r,v;odt(int x=0,int y=0,int w=0){l=x;r=y;v=w;}
    inline bool operator<(odt x)const{return l<x.l;}
};
int tot=1,lst=1;
int nex[maxn][26],fa[maxn],len[maxn],dep[maxn];
char s[maxn];
vector<pii> Q[maxn];
void ins(char c){
    int o=c-'a',x=++tot,p=lst;
    lst=x;len[x]=len[p]+1;
    while(!nex[p][o])   nex[p][o]=x,p=fa[p];
    if(!p)  return fa[x]=1,void();
    int q=nex[p][o];
    if(len[q]==len[p]+1)    return fa[x]=q,void();
    int nw=++tot;
    memc(nex[nw],nex[q]);len[nw]=len[p]+1;fa[nw]=fa[q];
    fa[q]=fa[x]=nw;
    while(nex[p][o]==q) nex[p][o]=nw,p=fa[p];
}
int son[maxn],siz[maxn],tp[maxn];
int mxd[maxn];
set<odt> st[maxn];
unordered_map<int,int> id[maxn];
inline auto split(int p,int o){
    auto it=st[o].lower_bound(odt(p));
    if(it!=st[o].end()&&it->l==p)   return it;
    if(it==st[o].begin()) return st[o].end();
    it--;
    if(it->r<p) return st[o].end();
    int l=it->l,r=it->r,v=it->v;
    st[o].erase({l,r,v});st[o].ep(l,p-1,v);
    return st[o].ep(p,r,v).fi;
}
void dfs1(int u){
    siz[u]=1;dep[u]=dep[fa[u]]+1;
    go(u,i){
        dfs1(t);
        siz[u]+=siz[t];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
}
void dfs2(int u){
    gmx(mxd[tp[u]],dep[u]);id[tp[u]][dep[u]]=u;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u]);
    go(u,i)if(t^son[u])tp[t]=t,dfs2(t);
}
int p=1;
void upd(char c,int r){
    p=nex[p][c-'a'];
    for(int i=p;(i^1)&&i;i=fa[tp[i]]){
        int f=tp[i];
        if(dep[i]^mxd[f])split(dep[i]+1,f);
        for(auto it=st[f].begin();it!=st[f].end()&&it->l<=dep[i];it=st[f].erase(it)){
            int x=id[f][it->l],y=id[f][it->r],w=it->v;
            int l1=len[fa[x]]+1,l2=len[y];
            if(w){
                T[0].upd(w-l2+2,w-l1+1,-(w-l1+2));T[1].upd(w-l2+2,w-l1+1,1);
                T[0].upd(1,w-l2+1,-(l2-l1+1));
                // if(w-l2+1>=1)   printf("- %d\n",l2-l1+1);
            }
            // printf("%d -> %d : %d %d %d\n",x,y,l1,l2,r);
            // if(r-l2+1>=1)   printf("+ %d\n",l2-l1+1);
            T[0].upd(r-l2+2,r-l1+1,r-l1+2);T[1].upd(r-l2+2,r-l1+1,-1);
            T[0].upd(1,r-l2+1,l2-l1+1);
        }
        st[f].ep(dep[f],dep[i],r);
    }
}
void data(){
    n=20;for(int i=1;i<=n;i++)printf("%c",rand()%26+'a');puts("");
    q=20;printf("%d\n",q);while(q--){int l=rand()%n+1,r=rand()%n+1;if(l>r)swap(l,r);printf("%d %d\n",l,r);}
    exit(0);
}
int main(){
    // data();
    scanf("%s",s+1);n=strlen(s+1);
    for(int i=1;i<=n;i++)   ins(s[i]);
    for(int i=2;i<=tot;i++) add(fa[i],i);
    dfs1(1);tp[1]=1;dfs2(1);
    for(int i=1;i<=tot;i++)if(tp[i]==i)st[i].ep(dep[i],mxd[i],0);
    scanf("%d",&q);
    for(int i=1;i<=q;i++){int l,r;scanf("%d%d",&l,&r);Q[r].eb(l,i);}
    for(int i=1;i<=n;i++){
        upd(s[i],i);
        for(auto [l,id]:Q[i])   ans[id]=T[0].que(l)+T[1].que(l)*l;
    }
    for(int i=1;i<=q;i++)   printf("%lld\n",ans[i]);
}