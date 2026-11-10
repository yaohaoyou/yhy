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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10,mod=998244353;
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
int n,m,q,T;
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
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int tot;
int rk[maxn],dfn[maxn],fa[maxn];
int c[maxn],p[maxn],w[maxn];
ll a[maxn][2],siz[maxn][2];
ll f[maxn][2];
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=31^__builtin_clz(y-x++);return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using stLCA::LCA;
void dfs1(int u,int ft){fa[u]=ft;rk[dfn[u]=++tot]=u;stLCA::st[0][tot]=ft;go(u,i)if(t^ft)dfs1(t,u);}
void dfs(){
    for(int i=n;i;i--){
        int u=rk[i];
        f[u][0]=f[u][1]=0;
        siz[u][0]=a[u][0];siz[u][1]=a[u][1];
        go(u,i)if(t^fa[u]){
            f[u][0]+=f[t][0]+siz[t][0];f[u][1]+=f[t][1]+siz[t][1];
            siz[u][0]+=siz[t][0];siz[u][1]+=siz[t][1];
        }
    }
}
void dfs2(){
    for(int i=2;i<=n;i++){
        int u=rk[i],ft=fa[u];
        for(bool o:{0,1}){
            ll fft=f[ft][o]-f[u][o]-siz[u][o],sz=siz[1][o]-siz[u][o];
            f[u][o]+=fft+sz;
        }
    }
}
inline mit calc(int l,int r){return l>r?0:1ll*(l+r)*(r-l+1)/2%mod;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();m=read();q=read();T=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    for(int i=1;i<=m;i++){
        c[i]=read()-1,p[i]=read(),w[i]=read();
        a[p[i]][c[i]]+=w[i];
    }
    dfs1(1,0);stLCA::build();
    while(q--){
        int k=read();
        while(k--){
            int i=read();
            a[p[i]][c[i]]-=w[i];
            c[i]=read()-1;p[i]=read();w[i]=read();
            a[p[i]][c[i]]+=w[i];
        }
        dfs();dfs2();
        int rt=1,p=1;
        for(int i=2;i<=n;i++){
            if(f[rt][0]>f[i][0])rt=i;
            if(f[p][1]>f[i][1])p=i;
        }
        // dep[0]=-1;dfs3(rt,0);
        vector<int> v,v2;
        int l=LCA(p,rt);
        while(p^l)  v.eb(p),p=fa[p];
        v.eb(l);
        while(rt^l) v2.eb(rt),rt=fa[rt];
        for(int i=int(v2.size())-1;~i;i--)v.eb(v2[i]);
        // assert(v.size()<=5);
        // ll lst=0;
        // for(int i=1;i<v.size();i++)assert(f[v[i]][1]-f[v[i-1]][1]>=lst),lst=f[v[i]][1]-f[v[i-1]][1];
        mit ans=0;
        int x=v.size()-1,y=0,i=1;
        while(i<=T){
            // printf("%d %d\n",x,y);
            if(x==y){
                ans+=mit(f[v[x]][0]+f[v[y]][1])*(T-i+1);
                break;
            }
            int mn=min(f[v[x-1]][0]-f[v[x]][0],f[v[y+1]][1]-f[v[y]][1]);
            int j=min(mn,T);
            if(i<=j){
                ans+=calc(i,j)*abs(x-y)+mit(f[v[x]][0]+f[v[y]][1])*(j-i+1);
            }
            // while(i<=j) ans+=mit(1ll*abs(dep[v[x]]-dep[v[y]])*i+f[v[x]][0]+f[v[y]][1]),i++;
            if(mn==f[v[x-1]][0]-f[v[x]][0]) x--;
            else    y++;
            i=j+1;
            // printf("%d %d %d %d\n",i-1,ans,x,y);
        }
        // for(int i=1;i<=T;i++){
        //     ll res=1e18;
        //     for(int x:v){
        //         // for(int j=1;j<=n;j++)gmn(res,1ll*dep[j]*i+f[j][1]);
        //         for(int y:v)gmn(res,1ll*abs(dep[x]-dep[y])*i+f[y][1]+f[x][0]);
        //     }
        //     // printf("%d ",res);
        //     ans+=res%mod;
        // }
        printf("%d\n",ans);
    }
}