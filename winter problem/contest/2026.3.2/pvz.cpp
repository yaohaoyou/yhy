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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
bool mem1;
const int maxn=2e6+10;
int n;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
    inline void print(int x,char ch){if(!x)return putc(48),putc(ch),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);putc(ch);}
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
int a[maxn],f[maxn],son[maxn],siz[maxn];
unordered_set<int> v[maxn];
vector<int> st;
int buc[maxn];
void dfs1(int u,int ft){siz[u]=1;go(u,i)if(t^ft){dfs1(t,u);siz[u]+=siz[t];if(siz[t]>siz[son[u]])son[u]=t;}}
void dfs(int u,int ft){
    f[u]=1;
    if(!son[u])    return v[u].ep(a[u]),void();
    dfs(son[u],u);f[u]+=f[son[u]];v[u].swap(v[son[u]]);
    go(u,_)if((t^ft)&&(t^son[u]))   dfs(t,u),f[u]+=f[t];
    int mx=1;
    go(u,_){
        if(t==son[u]||t==ft)    continue;
        for(int i:v[t]){
            if(!buc[i]) st.eb(i);
            buc[i]++;
        }
    }
    for(int i:st){
        if(v[u].count(i))   buc[i]++;
        gmx(mx,buc[i]);
    }
    if(mx==1)for(int i:st)v[u].ep(i);
    else{
        v[u].clear();
        for(int i:st)if(buc[i]==mx)v[u].ep(i);
    }
    f[u]-=mx;
    for(int i:st)   buc[i]=0;
    st.clear();
}
bool mem2;
int main(){
    freopen("pvz.in","r",stdin);freopen("pvz.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();
    for(int i=2;i<=n;i++)   adde(i,read());
    for(int i=1;i<=n;i++)   a[i]=read();
    dfs1(1,0);dfs(1,0);
    printf("%d\n",f[1]);
}