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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10;
bool mem1;
int mod;
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
int n;
int f[2][maxn][2],dep[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to,as1,as2;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v,1,1};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(auto x,char c){if(!x)return putc(48),putc(c),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(c);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
struct Matrix{
    int a[2][2];
    inline void clear(){mems(a,0);}
    inline void init(){clear();a[0][0]=a[1][1]=1;}
    inline int* operator[](int x){return a[x];}
    Matrix operator*(Matrix x)const{
        Matrix res;res.clear();
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                for(int k=0;k<2;k++)
                    madd(res.a[i][j],immul(a[i][k],x.a[k][j]));
        return res;
    }
    inline void print(){printf("%d %d\n%d %d\n\n",a[0][0],a[0][1],a[1][0],a[1][1]);}
};
Matrix pre[2][maxn],suf[2][maxn];
Matrix Make(int f0,int f1,bool o){
    Matrix M;
    if(o){
        M[0][0]=imadd(f0,1);M[0][1]=f1;
        M[1][0]=0;M[1][1]=imadd(f0,imadd(f1,1));
    }
    else{
        M[0][0]=imadd(imadd(f0,f1),1);M[0][1]=0;
        M[1][0]=f0;M[1][1]=imadd(f1,1);
    }
    return M;
}
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    go(u,i)if(t^ft)dfs(t,u);
    vector<int> son;son.clear();go(u,i)if(t^ft)son.eb(t);
    for(int o:{0,1}){
        f[o][u][0]=f[o][u][1]=0;
        if(o)   f[o][u][0]=1;
        else    f[o][u][1]=1;
        for(int t:son){
            int f0=f[o][u][0],f1=f[o][u][1];
            if(o){
                madd(f[o][u][1],immul(imadd(f1,f0),f[!o][t][1]));
                madd(f[o][u][1],immul(f1,f[!o][t][0]));
                madd(f[o][u][0],immul(f0,f[!o][t][0]));
            }
            else{
                madd(f[o][u][1],immul(f1,f[!o][t][1]));
                madd(f[o][u][0],immul(imadd(f0,f1),f[!o][t][0]));
                madd(f[o][u][0],immul(f0,f[!o][t][1]));
            }
        }
        Matrix now;now.init();
        for(int t:son)  pre[o][t]=now,now=now*Make(f[!o][t][0],f[!o][t][1],o);
        now.init();
        reverse(son.begin(),son.end());
        for(int t:son)  suf[o][t]=now,now=Make(f[!o][t][0],f[!o][t][1],o)*now;
        reverse(son.begin(),son.end());
    }
}
Matrix Matt[2],out[2][maxn];
int ans;
void dfs2(int u,int ft){
    if(ft){
        // if(ft==2){out[1][ft].print(),pre[1][u].print(),suf[1][u].print();puts("---------");}
        Matrix tmp=Matt[1]*out[1][ft]*pre[1][u]*suf[1][u];
        madd(ans,immul(tmp[0][0],f[1][u][0]));
        madd(ans,immul(tmp[0][1],f[1][u][1]));
        // printf("f[%d][1] = %d\n",ft,tmp[0][1]);
        // printf("%d %d : %d %d\n",u,ft,immul(tmp[0][1],f[1][u][1]),immul(tmp[0][0],f[1][u][0]));
        out[0][u]=Make(tmp[0][0],tmp[0][1],0);
        tmp=Matt[0]*out[0][ft]*pre[0][u]*suf[0][u];
        // printf("! %d %d %d\n",ft,tmp[0][0],tmp[0][1]);
        out[1][u]=Make(tmp[0][0],tmp[0][1],1);
    }
    go(u,i)if(t^ft)dfs2(t,u);
}
void data(){
    srand(time(0));
    int n=1e6,mod=998244353;
    printf("%d %d\n",n,mod);
    for(int i=2;i<=n;i++)printf("%d %d\n",rand()%(i-1)+1,i);
    exit(0);
}
bool mem2;
int main(){
    freopen("game.in","r",stdin);freopen("game.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    // data();
    Matt[1].clear();Matt[1][0][0]=1;Matt[1][0][1]=0;
    Matt[0].clear();Matt[0][0][0]=0;Matt[0][0][1]=1;
    out[1][1].init();out[0][1].init();
    n=read();mod=read();
    for(int i=1;i<n;i++)    adde(read(),read());
    dfs(1,0);dfs2(1,0);
    // for(int u=1;u<=n;u++){
    //     dfs(u,0);
    //     // printf("%d : %d %d\n",u,f[o][u][0],f[o][u][1]);
    //     go(u,i){
    //         // int f0=immul(f[o][u][0],qpow(f[!o][t][0]+1,mod-2)),f1=imdel(f[o][u][1],immul(f0,f[!o][t][1]));
    //         // mmul(f1,qpow(f[!o][t][1]+1,mod-2));
    //         Matrix tmp=(Matt*pre[t]*suf[t]);
    //         mmul(e[i|1].as1,tmp.a[0][1]);
    //         mmul(e[i|1].as2,tmp.a[0][0]);
    //     }
    // }
    // int ans=0;
    // for(int i=3;i<=cnt;i+=2)    madd(ans,imadd(e[i].as1,e[i].as2));
    printf("%d\n",ans%mod);
}