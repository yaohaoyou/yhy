#include<bits/stdc++.h>
#define ll long long
#define LL __int128
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn],c[maxn],p[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(LL x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
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
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
    inline int operator[](int x){return find(x);}
}U;
bool bk[maxn];
int fa[maxn];
void dfs(int u,int ft){
    fa[u]=ft;
    go(u,i)if(t^ft)dfs(t,u);
}
vector<piii> v[2][maxn];
LL solve(int r,int tp=-1){
    LL ans=0;U.init();
    dfs(r,0);mems(bk,0);mems(c,0);
    for(int i=1;i<=n;i++){
        int u=U[fa[p[i]]],x=c[p[i]];
        U.merge(p[i],fa[p[i]]);
        if(x){
            for(;u;u=U[u]){
                int del=min(b[u]-c[u],x);
                if(~tp)v[tp][u].eb(p[i],pii(del,x));
                c[u]+=del;x-=del;ans+=1ll*del*(a[p[i]]-a[u]);
                if(c[u]==b[u])  U.merge(u,fa[u]);
                if(!x)  break;
            }
        }
        if(x)   continue;
        if(u){
            x=b[p[i]];
            for(;u;u=U[u]){
                int del=min(b[u]-c[u],x);
                if(~tp)v[tp][u].eb(p[i],pii(del,x));
                c[u]+=del;x-=del;ans+=1ll*del*(a[p[i]]-a[u]);
                if(c[u]==b[u])  U.merge(u,fa[u]);
                if(!x)  break;
            }
        }
    }
    return ans;
}
void solve_list(){
    debug("list solving\n");
    LL ans=0;
    print(ans=solve(1,0));putc('\n');solve(n,1);
    LL lst=0;
    for(auto [i,j]:v[0][1]) lst+=1ll*j.fi*(a[i]-a[1]);
    for(int u=2;u<=n;u++){
        // debug("u = %d\n",u);
        ans-=lst;
        int x=b[u-1];
        for(auto [i,j]:v[1][u-1]){
            int del=min(x,j.se);
            x-=del;ans+=1ll*del*(a[i]-a[u-1]);
            // debug("add %d\n",1ll*del*(a[i]-a[u]));
            if(!x)  break;
        }
        // debug("lst = %d,ans = %d\n",(int)lst,(int)ans);
        for(auto [i,j]:v[0][u]) ans-=1ll*j.fi*(a[i]-a[u]);
        vector<piii> tmp;for(piii i:v[0][u])tmp.eb(i);for(piii i:v[1][u])tmp.eb(i);
        sort(tmp.begin(),tmp.end(),[&](piii x,piii y){return a[x.fi]>a[y.fi];});
        x=b[u];
        lst=0;
        for(auto [i,j]:tmp){
            int del=min(x,j.se);
            // debug("! %d %d %d %d\n",i,j.se,u,1ll*del*(a[i]-a[u]));
            x-=del;ans+=1ll*del*(a[i]-a[u]);
            lst+=1ll*del*(a[i]-a[u]);
            if(!x)  break;
        }
        // debug("------------------\n");
        print(ans);putc('\n');
    }
}
int main(){
    int _o;
    scanf("%d%d",&n,&_o);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    bool islist=true;
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);islist&=(abs(u-v)==1);}
    iota(p+1,p+n+1,1);sort(p+1,p+n+1,[&](int x,int y){return a[x]>a[y];});
    if(_o==1)   print(solve(1));
    else if(islist)  solve_list();
    else for(int r=1;r<=n;r++)print(solve(r)),putc('\n');
    flush();
}