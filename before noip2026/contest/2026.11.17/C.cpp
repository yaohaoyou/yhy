#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define piii pair<int,pli>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void Flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::Flush;
int n;
int c[maxn],w[maxn],ans[maxn];
ll a[maxn],s[maxn];
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
int fa[maxn];
void dfs(int u,int ft){fa[u]=ft;go(u,i)if(t^ft)dfs(t,u);}
ll buc[maxn];
#define __div(x,s) all=s,findWC(x,0),dvd(rt)
bool vis[maxn];
int tot;
int siz[maxn],rk[maxn],L[maxn],R[maxn],ft[maxn];
int d[maxn],mx[maxn],ps[maxn];ll pr[maxn];
vector<pli> v[maxn];
pli V[maxn];int vl;
vector<int> vc;
priority_queue<pli,vector<pli>,greater<pli>> q;
ll all;int rt,col;
void findWC(int u,int ft){
    siz[u]=1;int mx=0;
    go(u,i)if((t^ft)&&!vis[t])findWC(t,u),gmx(mx,siz[t]),siz[u]+=siz[t];
    gmx(mx,all-siz[u]);if(mx<=all/2)rt=u;
}
void dfs1(int u,int ft){
    rk[L[u]=++tot]=u;siz[u]=1;::ft[u]=ft;
    go(u,i)if((t^ft)&&!vis[t])dfs1(t,u),siz[u]+=siz[t];
    R[u]=tot;
}
void dfs2(int x){
    ft[x]=0;
    for(int i=L[x];i<=R[x];i++){
        int u=rk[i],ft=::ft[u];
        if(c[u]==col)   a[u]=a[ft]+w[u];
        else    a[u]=a[ft]-w[u];
        if(a[u]<=0&&V[vl].fi>-a[u])  d[upper_bound(V+1,V+vl+1,pli(-a[u],1e9))-V]++;
    }
}
void dfs3(int u,int ft){
    buc[c[u]]+=w[u];all+=w[u];
    mx[u]=mx[ft];
    if(buc[c[u]]>buc[mx[u]])    mx[u]=c[u];
    if(buc[mx[u]]*2>all){
        if(v[mx[u]].empty())    vc.eb(mx[u]);
        v[mx[u]].eb(buc[mx[u]]*2-all,u);
    }
    go(u,i)if(!vis[t]&&(t^ft))dfs3(t,u);
    buc[c[u]]-=w[u];all-=w[u];
}
void dvd(int u){
    vector<int> path;
    {
        int x=u;
        while(x&&!vis[x])  path.eb(x),x=fa[x];
    }
    vis[u]=true;
    tot=0;dfs1(u,0);
    vector<piii> vec;
    int mx=0;ll sz=0;
    for(int x:path){
        buc[c[x]]+=w[x];sz+=w[x];
        if(buc[c[x]]>buc[mx])  mx=c[x];
        if(2*buc[mx]>sz)    vec.eb(mx,pli(2*buc[mx]-sz,x));
    }
    for(int x:path) buc[c[x]]=0;
    sort(vec.begin(),vec.end());
    for(int i=0;i<vec.size();i++){
        vl=0;
        int j=i;while(j<vec.size()&&vec[j].fi==vec[i].fi)   V[++vl]=vec[j].se,j++;
        col=vec[i].fi;
        d[0]++;
        go(u,_)if(!vis[t]&&(t^fa[u]))dfs2(t);
        for(int k=1;k<=vl;k++){
            d[k]+=d[k-1];
            ans[V[k].se]+=d[k];
        }
        fll(d,0,vl);
        i=j-1;
    }
    all=0;
    go(u,_)if(!vis[t]&&(t^fa[u]))dfs3(t,0);
    int now=0;
    for(int i:vc){
        sort(v[i].begin(),v[i].end());
        q.ep(v[i][0].fi,i);
        now+=v[i].size();ps[i]=0;
    }
    ll V=0;
    auto slv=[&](int x){
        now-=v[x].size()-ps[x];
        if(v[x].back().fi>V-2*buc[x]){
            ps[x]=upper_bound(v[x].begin(),v[x].end(),pli(V-2*buc[x],1e9))-v[x].begin();
            now+=v[x].size()-ps[x];
            ll w=v[x][ps[x]].fi+2*buc[x];
            if(w^pr[x]) q.ep(pr[x]=w,x);
        }
        else    ps[x]=v[x].size();
    };
    for(int x:path){
        buc[c[x]]+=w[x];V+=w[x];
        while(!q.empty()&&q.top().fi<=V){
            int v=q.top().se;q.pop();
            if(v==c[x])   continue;
            slv(v);
        }
        if(!v[c[x]].empty())    slv(c[x]);
        ans[x]+=now;
    }
    for(int i:vc)v[i].clear(),pr[i]=-1;vc.clear();
    for(int x:path) buc[c[x]]=0;
    while(!q.empty())   q.pop();
    go(u,i)if(!vis[t])__div(t,siz[t]);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)   c[i]=read();
    for(int i=1;i<=n;i++)   w[i]=read();
    dfs(1,0);
    __div(1,n);
    for(int i=1;i<=n;i++)   print(ans[i],'\n');Flush();
}