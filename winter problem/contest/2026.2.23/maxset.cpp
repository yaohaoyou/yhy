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
const int maxn=1e5+10,maxk=35,mod=998244353;
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
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,k,q;
int a[maxn];
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
struct Matrix{
    int a[2][2];int lx,ly;
    Matrix(int x=0,int y=0){lx=x;ly=y;mems(a,0);}
    inline int* operator[](int x){return a[x];}
    inline void init(){mems(a,0);for(int i=0;i<max(lx,ly);i++)a[i][i]=1;}
    inline Matrix operator*(Matrix y){
        Matrix ret(lx,y.ly);
        // assert(ly==y.lx);
        for(int i=0;i<lx;i++)
            for(int j=0;j<ly;j++)if(a[i][j])
                for(int k=0;k<y.ly;k++)if(y[j][k])madd(ret[i][k],immul(a[i][j],y[j][k]));
        return ret;
    }
    inline void print(){for(int i=0;i<lx;i++,puts(""))for(int j=0;j<ly;j++)printf("%d ",a[i][j]);puts("");}
};
Matrix pre[maxn][maxk],suf[maxn][maxk],f[maxn][maxk],g[maxn][maxk],M[maxn][maxk];
void dfs(int u,int ft){
    for(int i=0;i<=k;i++)   f[u][i]=Matrix(2,1);
    for(int i=0;i<=k;i++)   f[u][i][0][0]=1;
    vector<int> son;son.clear();
    go(u,_)if(t^ft){
        dfs(t,u);
        son.eb(t);
        for(int i=0;i<=k;i++){
            int s=0;for(int j=0;j<=i;j++)madd(s,f[t][j][0][0]);
            int x=0;
            for(int j=i+1;j<=k;j++) madd(x,imadd(f[t][j][0][0],f[t][j][1][0]));
            madd(x,f[t][i][1][0]);
            M[t][i]=Matrix(2,2);M[t][i][0][0]=M[t][i][1][1]=s;M[t][i][0][1]=0;M[t][i][1][0]=x;
            f[u][i]=M[t][i]*f[u][i];
        }
    }
    if(!son.empty()){
        Matrix now(2,2);
        for(int i=0;i<=k;i++){
            now.init();
            for(int t:son){
                pre[t][i]=now;
                now=M[t][i]*now;
            }
            now.init();
            for(int _=son.size()-1;~_;_--){
                int t=son[_];
                suf[t][i]=now;
                now=M[t][i]*now;
            }
        }
    }
}
Matrix fft[maxk];
void dfs2(int u,int ft){
    for(int i=0;i<=k;i++)   g[u][i]=Matrix(2,2),g[u][i].init();
    if(ft){
        for(int i=0;i<=k;i++)   fft[i]=g[ft][i]*pre[u][i]*suf[u][i];
        for(int i=0;i<=k;i++){
            int s=0;for(int j=0;j<=i;j++)madd(s,fft[j][0][0]);
            int x=0;for(int j=i+1;j<=k;j++)madd(x,imadd(fft[j][0][0],fft[j][1][0]));madd(x,fft[i][1][0]);
            g[u][i][0][0]=g[u][i][1][1]=s;g[u][i][0][1]=0;g[u][i][1][0]=x;
            f[u][i]=g[u][i]*f[u][i];
        }
    }
    go(u,_)if(t^ft)dfs2(t,u);
}
int main(){
    freopen("maxset.in","r",stdin);freopen("maxset.out","w",stdout);
    n=read();k=read();q=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    dfs(1,0);
    dfs2(1,0);
    while(q--){
        int x=read(),y=read();
        print(imadd(f[x][y][0][0],f[x][y][1][0]));putc('\n');
    }
    flush();
}