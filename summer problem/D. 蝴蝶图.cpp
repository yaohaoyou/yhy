#pragma GCC optimize(2,3,"Ofast")
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
int n,m,l,r;
ll res=1e18;
int sta[maxn],col[maxn],bel[maxn];
vector<int> L,R,M;
struct EDGE{int u,v,w;};
vector<EDGE> W,E,le,re,LE,RE;
set<pii> st;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
}U;
inline bool cmp(EDGE x,EDGE y){return x.w<y.w;}
vector<EDGE> kruskal(vector<EDGE> ed,bool flag=1){
    vector<EDGE> ret;ret.clear();
    if(flag)sort(ed.begin(),ed.end(),cmp);
    for(EDGE i:ed){
        int u=U.find(i.u),v=U.find(i.v);
        if(u==v)    continue;
        ret.eb(i);U.merge(u,v);
    }
    return ret;
}
int all_time;
vector<EDGE> tmp;
void solve(vector<EDGE> vec){
    all_time+=vec.size();
    all_time+=RE.size();
    all_time+=LE.size();
    all_time+=M.size();
    ll now=0;
    {
        for(int i:M)    U.fa[i]=i;
        for(EDGE i:LE)  U.fa[i.u]=i.u,U.fa[i.v]=i.v;
        for(EDGE i:vec) U.merge(i.u,i.v),now+=i.w;
        tmp=kruskal(LE,0);
        for(EDGE i:tmp) now+=i.w;
    }
    {
        for(int i:M)    U.fa[i]=i;
        for(EDGE i:RE)  U.fa[i.u]=i.u,U.fa[i.v]=i.v;
        for(EDGE i:vec) U.merge(i.u,i.v);
        tmp=kruskal(RE,0);
        for(EDGE i:tmp) now+=i.w;
    }
    res=min(res,now);
}
int bell;
void dfs(int x,int y){
    if(x==M.size()){
        vector<EDGE> vec;vec.clear();
        for(EDGE i:W)if(bel[i.u]==bel[i.v])vec.eb(i);
        for(int u:M)U.fa[u]=u;
        all_time+=vec.size();
        solve(kruskal(vec,0));
        bell++;
        return;
    }
    bel[M[x]]=y+1;
    dfs(x+1,y+1);
    for(int i=1;i<=y;i++){
        bel[M[x]]=i;
        dfs(x+1,y);
    }
}
int main(){
    n=read();m=read();l=read();r=read();
    for(int i=1;i<=m;i++){int u=read(),v=read(),w=read();E.eb((EDGE){u,v,w});}
    for(int i=1;i<=l;i++){int x=read();L.eb(x),sta[x]=1;}
    for(int i=1;i<=r;i++){int x=read();R.eb(x);sta[x]|=2;}
    for(int i=1;i<=n;i++)if(sta[i]==3)M.eb(i);
    for(EDGE i:E){
        if(sta[i.u]==3&&sta[i.v]==3)W.eb(i);
        else if((sta[i.u]&1)&&(sta[i.v]&1)) le.eb(i);
        else if((sta[i.u]&2)&&(sta[i.v]&2)) re.eb(i);
    }
    LE=le;RE=re;
    ll ans=0;
    {
        U.init();
        for(EDGE i:W)U.merge(i.u,i.v);
        le=kruskal(le);
        U.init();
        for(EDGE i:le)  ans+=i.w;
        for(EDGE i:le)  col[i.u]=U.find(i.u),col[i.v]=U.find(i.v);
    }
    {
        U.init();
        for(EDGE i:W)U.merge(i.u,i.v);
        re=kruskal(re);
        U.init();
        for(EDGE i:re)  ans+=i.w;
    }
    U.init();
    for(EDGE i:le)   U.merge(i.u,i.v);
    for(EDGE i:re)   U.merge(i.u,i.v);
    for(int i=1;i<=n;i++)   col[i]=U.find(i);
    {
        U.init();
        for(EDGE &i:LE) i.u=col[i.u],i.v=col[i.v];
        LE=kruskal(LE);
        U.init();
        for(EDGE &i:RE) i.u=col[i.u],i.v=col[i.v];
        RE=kruskal(RE);
    }
    {
        for(int &i:M)   i=col[i];
        sort(M.begin(),M.end());M.erase(unique(M.begin(),M.end()),M.end());
        for(EDGE &i:W){
            i.u=col[i.u],i.v=col[i.v];
            if(i.u>i.v)swap(i.u,i.v);
        }
    }
    U.init();
    sort(W.begin(),W.end(),cmp);
    vector<EDGE> nW;nW.clear();
    {
        for(EDGE i:W)if(st.find(pii(i.u,i.v))==st.end())st.ep(i.u,i.v),nW.eb(i);
        W.swap(nW);
    }
    sort(LE.begin(),LE.end(),cmp);
    sort(RE.begin(),RE.end(),cmp);
    debug("%d %d %d %d\n",W.size(),LE.size(),RE.size(),M.size());
    dfs(0,0);
    printf("%lld\n",ans+res);
    debug("bell = %d %d\n",bell,all_time);
}