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
const int maxn=3e5+10,inf=1e9;
int n,q,C;
int fa[maxn];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
    inline void clr(int x){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=inf;while(p>>=1)tr[p]=inf;}
    int binary1(setpos,int pr,int lim){
        if(tr[p]>lim)   return -1;
        if(l==r)    return l;
        setmid;
        if(r<=pr){
            if(tr[rs]<=lim) return binary1(rson,pr,lim);
            return binary1(lson,pr,lim);
        }
        int res=-1;
        if(pr>mid)  res=binary1(rson,pr,lim);
        if(~res)return res;
        return binary1(lson,pr,lim);
    }
    int binary2(setpos,int pl,int lim){
        if(tr[p]>lim)   return n+1;
        if(l==r)    return l;
        setmid;
        if(l>=pl){
            if(tr[ls]<=lim) return binary2(lson,pl,lim);
            return binary2(rson,pl,lim);
        }
        int res=n+1;
        if(pl<=mid)  res=binary2(lson,pl,lim);
        if(res<=n)return res;
        return binary2(rson,pl,lim);
    }
}
using namespace SegmentTree;
#define __div(x,s) ALL=s,findWC(x,0),divide(rt)
int tot,ALL,rt;
int b[maxn],siz[maxn],pr[maxn],nx[maxn],dep[maxn],ans[maxn];
bool vis[maxn];
queue<int> que;
vector<pii> v,Q[maxn],ins[maxn],era[maxn];
void findWC(int u,int ft){
    siz[u]=1;int mx=0;
    go(u,i)if((t^ft)&&!vis[t]){
        findWC(t,u);
        mx=max(mx,siz[t]);
        siz[u]+=siz[t];
    }
    mx=max(mx,ALL-siz[u]);
    if(mx+mx<=ALL)  rt=u;
}
void dfs(int u,int ft){dep[u]=dep[ft]+1;siz[u]=1;v.eb(b[u],u);go(u,i)if((t^ft)&&!vis[t])dfs(t,u),siz[u]+=siz[t];}
void divide(int u){
    vis[u]=true;
    v.clear();
    dep[0]=-1;dfs(u,0);sort(v.begin(),v.end());
    for(pii tmp:v){
        int x=tmp.se;
        gmx(pr[x],binary1(all,x,C-dep[x]));
        gmn(nx[x],binary2(all,x,C-dep[x]));
        upd(x,dep[x]);
    }
    for(pii x:v)clr(x.se);
    go(u,i)if(!vis[t])__div(t,siz[t]);
}
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline void upd(int l,int r,int s){add(l,s);add(r+1,-s);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
int main(){
    mems(tr,0x3f);
    n=read();q=read();C=read();
    for(int i=2;i<=n;i++)   fa[i]=read(),adde(i,fa[i]);
    fill(pr+1,pr+n+1,-1);fill(nx+1,nx+n+1,n+1);
    que.ep(1);
    while(!que.empty()){
        int u=que.front();que.pop();
        b[u]=++tot;
        go(u,i)if(t^fa[u])que.ep(t);
    }
    __div(1,n);
    for(int i=1;i<=q;i++){int l=read(),r=read();Q[l].eb(r,i);}
    for(int i=1;i<=n;i++){
        ins[max(pr[i]+1,1)].eb(i,nx[i]-1);
        era[i+1].eb(i,nx[i]-1);
    }
    for(int i=1;i<=n;i++){
        for(auto [l,r]:ins[i])  T.upd(l,r,1);
        for(auto [l,r]:era[i])  T.upd(l,r,-1);
        for(auto [r,id]:Q[i])   ans[id]=T.que(r);
    }
    for(int i=1;i<=q;i++)   print(ans[i]),putc('\n');flush();
}