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
#define fll(arr,x,siz) fill_n(arr,siz,x)
#define cpy(arr1,arr2,siz) copy_n(arr2,siz,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10,inf=1e9;
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
int n;
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
int k,tot;
int rk[maxn];
int dep[maxn],mxd[maxn],siz[maxn];
vector<int> f[maxn][3];
int g[3][maxn];
int G[maxn];
pii seg[maxn];
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    int pr=0;
    go(u,i)if(t^ft)dfs(t,u),pr=i;else if(!pr)head[u]=e[i].nxt;else e[pr].nxt=e[i].nxt;
    rk[++tot]=u;
}
bool mem2;
void data(){
    int T=2;printf("0 %d\n",T);
    srand(time(0));
    while(T--){
        n=5e5;printf("%d %d\n",n,10);
        for(int i=2;i<=n;i++)printf("%d %d\n",rand()%(i-1)+1,i);
    }
    exit(0);
}
void matt(int _cases){
    // data();
    rebuild();tot=0;
    n=read();const int K=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    int l=0,r=n,ans=0;
    dfs(1,0);tot=0;
    for(int i=1;i<=n;i++){
        seg[i].fi=tot+1;
        go(i,j)G[++tot]=t;
        seg[i].se=tot;
        // for(int j=0;j<3;j++)f[i][j].resize(K+1);
    }
    for(int i=0;i<3;i++){
        for(int u=1;u<=n;u++)f[u][i].resize(K+1,inf);
    }
    while(l<=r){
        int mid=(l+r)>>1;
        k=mid;
        for(int _=1;_<=n;_++){
            int u=rk[_];siz[u]=1;
            for(int i=0;i<3;i++)f[u][i].resize(K+1,inf);
            mxd[u]=0;f[u][0][1]=0;
            for(int __=seg[u].fi;__<=seg[u].se;__++){
                int t=G[__];
                for(int i=0;i<3;i++)for(int j=1;j<=K;j++)g[i][j]=f[u][i][j],f[u][i][j]=inf;
                for(int i=1;i<=siz[t]&&i<=K;i++){
                    if(f[t][0][i]+1+mxd[u]<=k) gmn(f[u][0][i],f[t][0][i]+1);
                    gmn(f[u][2][i],min(max(mxd[u],f[t][0][i]-k),max(mxd[u],f[t][2][i]+1)));
                    if(f[t][1][i]+1+mxd[u]<=k) gmn(f[u][1][i],f[t][1][i]+1);
                }
                for(int i=1;i<=siz[u]&&i<=K;i++){
                    if(mxd[t]+1+g[0][i]<=k) gmn(f[u][0][i],g[0][i]);
                    gmn(f[u][2][i],min(max(g[2][i],mxd[t]+1),max(g[0][i]-k-1,mxd[t]+1)));
                    if(mxd[t]+1+g[1][i]<=k) gmn(f[u][1][i],g[1][i]);
                    for(int j=1;j<=siz[t]&&i+j<=K;j++){
                        if(!f[t][0][j]&&!g[0][i])   f[u][0][i+j]=0;
                        else if(!f[t][1][j]&&!g[0][i])   f[u][1][i+j]=0;
                        else if(!f[t][0][j]&&!g[1][i])   f[u][1][i+j]=0;
                        else{
                            if(f[t][0][j]<k+k){
                                if(f[t][0][j]+1+g[0][i]<=k+k)    gmn(f[u][1][i+j],min(g[0][i],f[t][0][j]+1));
                                if(f[t][0][j]+1+g[2][i]<=k) gmn(f[u][1][i+j],f[t][0][j]+1);
                            }
                            if(f[t][2][j]+1+g[0][i]<=k) gmn(f[u][1][i+j],g[0][i]);
                        }
                    }
                }
                gmx(mxd[u],mxd[t]+1);siz[u]+=siz[t];
            }
        }
        if(f[1][0][K]<=k||f[1][1][K]<=k)    ans=mid,r=mid-1;
        else    l=mid+1;
    }
    print(ans,'\n');
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int C=read(),T=read();for(int i=1;i<=T;i++)matt(i);
    Flush();
}