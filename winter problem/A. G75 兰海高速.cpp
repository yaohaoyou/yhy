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
const int maxn=5e5+10;
int n;
int vis[maxn];
vector<int> v[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
struct DSU{
    int fa[maxn],siz[maxn];
    stack<int> stk;
    void init(){iota(fa+1,fa+n+1,1);fill(siz+1,siz+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){x=find(x);y=find(y);if(x^y){stk.ep(x);stk.ep(y);fa[y]=x;siz[x]+=siz[y];siz[y]=0;}}
    inline void clear(){while(!stk.empty())fa[stk.top()]=stk.top(),siz[stk.top()]=1,stk.pop();}
}U;
int fa[maxn],c[maxn],dep[maxn],cc[maxn];
void dfs(int u,int ft){
    dep[u]=dep[fa[u]=ft]+1;
    go(u,i){
        if(t==ft)   continue;
        dfs(t,u);
    }
}
void matt(int _cases){
    rebuild();
    for(int i=1;i<=n;i++)   cc[i]=c[i]=0;
    n=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    for(int i=1;i<=n;i++){
        int s=read();
        while(s--)  v[read()].eb(i);
        // if(_cases==181)puts("");
    }
    dfs(1,0);
    bool flag=true;
    U.init();
    for(int i=1;i<=n;i++){
        sort(v[i].begin(),v[i].end(),[&](int x,int y){return dep[x]>dep[y];});
        if(v[i].size()&1)   flag=false;
        for(int j:v[i]) vis[j]++;
        int poi=0,rt=0;
        for(int j:v[i]){
            if(vis[j]&&vis[fa[j]]){
                vis[fa[j]]--;vis[j]--;
                c[j]++;
                U.merge(j,fa[j]);
                // printf("%d,%d\n",j,fa[j]);
                deg[j]++;deg[fa[j]]++;
                if(deg[j]>2||deg[fa[j]]>2)  flag=false;
                if(!cc[j])  poi++,cc[j]=i,rt=j;
                if(!cc[fa[j]])  poi++,cc[fa[j]]=i,rt=fa[j];
            }
        }
        // for(int j:col[i])if(cc[j]==cc[fa[j]])U.merge(j,fa[j]);
        if(rt){
            // printf("%d %d\n",U.siz[U.find(col[i].front())],poi);
            if(U.siz[U.find(rt)]!=poi)    flag=false;
        }
        U.clear();
        for(int j:v[i]) vis[j]=0,cc[j]=cc[fa[j]]=deg[j]=deg[fa[j]]=0;
        v[i].clear();
    }
    // for(int i=1;i<=n;i++)   printf("%d ",c[i]);puts("");
    for(int i=2;i<=n;i++)if(c[i]^1){flag=false;break;}
    puts(flag?"Yes":"No");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}