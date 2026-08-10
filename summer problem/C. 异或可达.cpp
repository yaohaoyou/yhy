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
int n,m,k;
ll ans;
struct EDGE{int u,v,w;}E[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ll x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
struct DSU{
    int fa[maxn],siz[maxn];
    stack<int> stk;
    void init(){for(int i=1;i<=n;i++)fa[i]=i,siz[i]=1;}
    int find(int x){return fa[x]==x?x:find(fa[x]);}
    inline void merge(int x,int y){
        x=find(x);y=find(y);if(x==y)return;
        if(siz[x]>siz[y])swap(x,y);
        ans+=1ll*siz[x]*siz[y];
        stk.ep(x);fa[x]=y;siz[y]+=siz[x];
    }
    inline void era(int s){while(stk.size()^s){int x=stk.top();stk.pop();siz[fa[x]]-=siz[x];ans-=1ll*siz[x]*siz[fa[x]];fa[x]=x;}}
}U;
int cnt;
unordered_map<int,int> mp[31];
vector<pii> G[maxn*31];
unordered_set<int> st[maxn];
int L[maxn*40],R[maxn*40];
pii Q[maxn];
ll out[maxn];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,q
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<pii> tr[maxn<<2];
    void upd(setpos,int pl,int pr,int u,int v){if(l>=pl&&r<=pr)return tr[p].eb(u,v),void();setmid;if(pl<=mid)upd(lson,pl,pr,u,v);if(pr>mid)upd(rson,pl,pr,u,v);}
    void dfs(setpos){
        int siz=U.stk.size();
        for(pii t:tr[p]){
            int u=t.fi,v=t.se;
            U.merge(u,v);
        }
        if(l==r)    out[Q[l].se]=ans;
        if(l^r){setmid;dfs(lson);dfs(rson);}
        U.era(siz);
    }
}
using namespace SegmentTree;
int main(){
    n=read(),m=read(),k=read();
    for(int i=1;i<=m;i++){int u=read(),v=read(),w=read();E[i]={u,v,w};}
    for(int i=1;i<=m;i++){
        int u=E[i].u,v=E[i].v,w=E[i].w,nw=0;
        for(int j=30;~j;j--){
            if(w&(1<<j))    nw|=(1<<j);
            if(!mp[j][nw]) mp[j][nw]=++cnt;
            G[mp[j][nw]].eb(u,v);
        }
    }
    int q=read();
    for(int i=1;i<=q;i++)   Q[i]=pii(read(),i);
    sort(Q+1,Q+q+1);
    for(int i=1;i<=q;i++){
        int d=Q[i].fi,id=Q[i].se,nw=0;
        for(int j=30;~j;j--){
            bool o1=k&1<<j,o2=d&1<<j;
            if(o1)   st[i].ep(mp[j][nw|(o2<<j)]);
            nw|=(o1^o2)<<j;
        }
    }
    for(int i=1;i<=q;i++){
        for(int j:st[i]){
            if(st[i-1].find(j)==st[i-1].end())L[j]=i;
            if(st[i+1].find(j)==st[i+1].end())R[j]=i;
        }
    }
    for(int i=1;i<=cnt;i++){
        for(pii tmp:G[i]){
            int u=tmp.fi,v=tmp.se;
            if(L[i]&&R[i]&&L[i]<=R[i])    upd(all,L[i],R[i],u,v);
        }
    }
    U.init();dfs(all);
    for(int i=1;i<=q;i++)   print(out[i]),putc('\n');
    flush();
}