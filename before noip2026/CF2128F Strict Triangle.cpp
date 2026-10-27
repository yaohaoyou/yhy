#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=5e5+10;
bool mem1;
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
int n,m,k;
namespace Graph{
    const int maxm=2e6+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w,r=e[i].mr;i;i=e[i].nxt,t=e[i].to,w=e[i].w,r=e[i].mr)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,w,mr;}e[maxm];
    inline void add(int u,int v,int w,int mr){e[++cnt]={head[u],v,w,mr};head[u]=cnt;}
    inline void adde(int u,int v,int w,int mr){add(u,v,w,mr);add(v,u,w,mr);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
ll f[maxn],g[maxn];
bool vis[maxn];
priority_queue<pli,vector<pli>,greater<pli>> q;
void dijkstra(ll *d,int s){
    fill(d,d+n+1,1e18);fill(vis,vis+n+1,0);
    q.ep(d[s]=0,s);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        go(u,i)if(d[t]>d[u]+r){
            d[t]=d[u]+r;
            if(!vis[t])q.ep(d[t],t);
        }
    }
}
bool mem2;
void matt(int _cases){
    rebuild();
    n=read();m=read();k=read();
    for(int i=1;i<=m;i++){int u=read(),v=read(),l=read(),r=read();adde(u,v,l,r);}
    dijkstra(f,k);
    fill(g,g+n+1,1e18);fill(vis,vis+n+1,0);
    q.ep(g[1]=-f[1],1);
    while(!q.empty()){
        int u=q.top().se;q.pop();
        if(vis[u])continue;vis[u]=true;
        if(g[u]>=f[u])  continue;
        go(u,i)if(t!=k&&g[t]>max(g[u]+w,-f[t])){
            g[t]=max(g[u]+w,-f[t]);
            if(!vis[t])q.ep(g[t],t);
        }
    }
    // printf("%d %d\n",g[n],f[n]);
    puts(g[n]<f[n]?"YES":"NO");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}