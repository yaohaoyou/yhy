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
const int maxn=2e5+10,B=450;
int n,q;
int a[maxn];
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
int tot,cur;
int in[maxn],out[maxn],dfn[maxn],rnk[maxn<<1];
bool f[maxn];
ll qans[maxn];
namespace ST_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using ST_LCA::LCA;
struct ques{int l,r,lc,id,L,R;};
vector<ques> Q;
int buc[maxn],id[maxn];
int c[maxn],s[maxn];
void dfs(int u,int ft){
    in[u]=++tot;dfn[u]=++cur;rnk[tot]=u;
    ST_LCA::st[0][dfn[u]]=ft;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
    }
    out[u]=++tot;rnk[tot]=u;
}
inline void add(int x){
    int d=a[x];
    c[buc[d]]--;s[id[buc[d]]]--;
    buc[d]++;
    c[buc[d]]++;s[id[buc[d]]]++;
}
inline void del(int x){
    int d=a[x];
    c[buc[d]]--;s[id[buc[d]]]--;
    buc[d]--;
    c[buc[d]]++;s[id[buc[d]]]++;
}
inline void chg(int x){
    x=rnk[x];
    if(f[x])    del(x);
    else    add(x);
    f[x]^=1;
}
inline int query(int l,int r){
    if(id[l]==id[r])    return accumulate(c+l,c+r+1,0);
    int res=0,idl=id[l],idr=id[r];
    while(id[l]==idl)   res+=c[l++];
    while(id[r]==idr)   res+=c[r--];
    for(int i=idl+1;i<idr;i++)  res+=s[i];
    return res;
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)id[i]=(i-1)/B+1;
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    dfs(1,0);ST_LCA::build();
    for(int i=1;i<=q;i++){
        int x,y,a,b;
        scanf("%d%d%d%d",&x,&y,&a,&b);
        if(in[x]>in[y])swap(x,y);
        int l=LCA(x,y);
        if(l==x) Q.eb((ques){in[x],in[y],0,i,a,b});
        else Q.eb((ques){out[x],in[y],in[l],i,a,b});
    }
    sort(Q.begin(),Q.end(),[&](ques x,ques y){return x.l/B==y.l/B?x.r/B==y.r/B?x.id<y.id:x.r<y.r:x.l<y.l;});
    int l=1,r=0,tim=0;
    for(int i=0;i<Q.size();i++){
        int ql=Q[i].l,qr=Q[i].r;
        while(r<qr) chg(++r);
        while(l>ql) chg(--l);
        while(r>qr) chg(r--);
        while(l<ql) chg(l++);
        if(Q[i].lc){
            chg(Q[i].lc);
            qans[Q[i].id]=query(Q[i].L,Q[i].R);
            chg(Q[i].lc);
        }
        else qans[Q[i].id]=query(Q[i].L,Q[i].R);
    }
    for(int i=1;i<=q;i++)printf("%lld\n",qans[i]);
}