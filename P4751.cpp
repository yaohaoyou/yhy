// 支持子树查询
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
const int maxn=1e6+10,inf=1e9;
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
int n,q;
bool mem1;
int a[maxn];
inline void getmx(int &x,int y){(x<y)&&(x=y);}
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
struct Matrix{
    int a[2][2];int lx,ly;
    Matrix(int x=0,int y=0){lx=x;ly=y;a[0][0]=a[0][1]=a[1][0]=a[1][1]=-inf;}
    int* operator[](int x){return a[x];}
    Matrix operator*(Matrix y){
        Matrix ret(lx,y.ly);
        ret[0][0]=max(a[0][0]+y[0][0],a[0][1]+y[1][0]);
        ret[0][1]=max(a[0][0]+y[0][1],a[0][1]+y[1][1]);
        ret[1][0]=max(a[1][0]+y[0][0],a[1][1]+y[1][0]);
        ret[1][1]=max(a[1][0]+y[0][1],a[1][1]+y[1][1]);
        return ret;
    }
}G[maxn];
int tot;
int fa[maxn],f[maxn][2],g[maxn][2],siz[maxn],son[maxn],dfsn[maxn],rnk[maxn],tp[maxn],ed[maxn],w[maxn];
inline void getmx(auto &x,auto y){(x<y)&&(x=y);}
inline void getmn(auto &x,auto y){(x>y)&&(x=y);}
inline void GenMatt(int i){G[i][0][0]=G[i][1][0]=g[i][0];G[i][0][1]=g[i][1];G[i][1][1]=-inf;}
void dfs1(int u,int ft){
    fa[u]=ft;
    siz[u]=1;
    f[u][1]=a[u];
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs1(t,u);
        siz[u]+=siz[t];
        f[u][0]+=max(f[t][0],f[t][1]);
        f[u][1]+=f[t][0];
        if(siz[t]>siz[son[u]])  son[u]=t;
    }
    w[u]=siz[u]-siz[son[u]];
}
void dfs2(int u,int ft){
    dfsn[u]=++tot;rnk[tot]=u;
    if(son[u])  tp[son[u]]=tp[u],dfs2(son[u],u),ed[u]=ed[son[u]];
    else    ed[u]=u;
    g[u][1]=a[u];
    go(u,i){
        int t=e[i].to;
        if(t==ft||t==son[u])   continue;
        tp[t]=t;
        dfs2(t,u);
        g[u][0]+=max(f[t][0],f[t][1]);
        g[u][1]+=f[t][0];
    }
}
namespace SegmentTree{
    #define ls lc[p]
    #define rs rc[p]
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all(x) rt[x],dfsn[x],dfsn[ed[x]]
    #define setmid int mid=md[p]
    #define setpos int p,int l,int r
    int cur;
    Matrix tr[maxn<<2];
    int rt[maxn],pos[maxn],lc[maxn<<2],rc[maxn<<2],md[maxn<<2],ft[maxn<<2];
    inline void pu(int p){tr[p]=tr[rs]*tr[ls];}
    void build(int &p,int l,int r){
        p=++cur;
        if(l==r){
            if(!rt[tp[rnk[l]]]) rt[rnk[l]]=p;
            tr[p]=G[rnk[l]];pos[l]=p;
            return;
        }
        if(tp[rnk[r]]==tp[rnk[l]]){
            if(!rt[tp[rnk[r]]]) rt[rnk[l]]=p;
            int s=0;for(int i=l;i<=r;i++)s+=w[rnk[i]];
            md[p]=r-1;for(int i=l;i<r;i++){s-=w[rnk[i]]*2;if(s<=0){md[p]=i;break;}}
        }
        else{
            int i=l;ll s=0;
            for(int i=l;i<=r;i++)   s+=w[rnk[i]];
            for(;dfsn[ed[rnk[i]]]^r;i=dfsn[ed[rnk[i]]]+1){
                s-=siz[rnk[i]]*2;
                if(s<=0){(i==l)&&(i=dfsn[ed[rnk[i]]]+1);break;}
            }
            md[p]=i-1;
        }
        setmid;build(lson);build(rson);pu(p);ft[ls]=ft[rs]=p;
    }
    inline void update(int x){int p=pos[x];tr[p]=G[rnk[x]];while(p=ft[p])pu(p);}
    Matrix query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;return pl<=mid?pr>mid?query(rson,pl,pr)*query(lson,pl,pr):query(lson,pl,pr):query(rson,pl,pr);}
}
using namespace SegmentTree;
inline void modify(int u,int v){
    g[u][1]+=v-a[u];a[u]=v;
    while(tp[u]^1){
        int ftp=fa[tp[u]];
        Matrix tmp=tr[rt[tp[u]]];
        g[ftp][0]-=max(tmp[0][0],tmp[0][1]);g[ftp][1]-=tmp[0][0];
        GenMatt(u);update(dfsn[u]);
        tmp=tr[rt[tp[u]]];
        g[ftp][0]+=max(tmp[0][0],tmp[0][1]);g[ftp][1]+=tmp[0][0];
        u=ftp;
    }
    GenMatt(u);update(dfsn[u]);
}
inline ll getans(){Matrix ans=tr[rt[1]];return max(ans[0][0],ans[0][1]);}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        adde(u,v);
    }
    dfs1(1,0);tp[1]=1;dfs2(1,0);
    for(int i=1;i<=n;i++){G[i]=Matrix(2,2);GenMatt(i);}
    {int RT;build(RT,1,n);}
    int lst=0;
    while(q--){
        int x=read()^lst,y=read();if(x<=0||x>n)exit(0);
        modify(x,y);print(lst=getans(),'\n');
    }
    flush();
}