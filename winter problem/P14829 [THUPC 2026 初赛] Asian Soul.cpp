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
int n,m,q;
int a[maxn];
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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
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
int dfn[maxn],ans[maxn],tot;
namespace st_LCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void build(){
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)
            for(int j=1;j+(1<<i)-1<=n;j++)
                st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
}
using st_LCA::LCA;
void dfs(int u,int ft){
    dfn[u]=++tot;
    st_LCA::st[0][dfn[u]]=ft;
    go(u,i)if(t^ft)dfs(t,u);
}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<pii> tr[maxn<<2];
    int v[maxn<<2],v2[maxn<<2];
    int f[maxn],tag[maxn];
    vector<int> son[maxn];
    void upd(setpos,int pl,int pr,pii Q){if(l>=pl&&r<=pr)return tr[p].eb(Q),void();setmid;if(pl<=mid)upd(lson,pl,pr,Q);if(pr>mid)upd(rson,pl,pr,Q);}
    bool cmp(int x,int y){return dfn[x]<dfn[y];};
    void dfs1(int u){
        tag[u]=f[u]?u:0;
        for(int t:son[u]){
            dfs1(t);
            f[u]+=f[t];
        }
        for(int t:son[u])if(f[u]>f[t])tag[t]=u;
    }
    void dfs2(int u){for(int t:son[u])gmx(tag[t],tag[u]),dfs2(t);}
    void dfs(setpos){
        if(l^r){setmid;dfs(lson);dfs(rson);}
        if(tr[p].empty())   return;
        if(r-l+1<=20){
            for(auto [i,j]:tr[p])for(int k=l;k<=r;k++)   gmx(ans[j],LCA(a[k],i));
            return;
        }
        int k=0;
        for(int i=l;i<=r;i++)   v[++k]=a[i],f[a[i]]++;
        for(auto [i,j]:tr[p])   v[++k]=i;v[++k]=1;
        {
            sort(v+1,v+k+1,cmp);
            int kk=0;
            for(int i=1;i+1<=k;i++)   v2[++kk]=v[i],v2[++kk]=LCA(v[i],v[i+1]);
            v2[++kk]=v[k];
            sort(v2+1,v2+kk+1,cmp);
            kk=unique(v2+1,v2+kk+1)-v2-1;
            k=0;
            for(int i=2;i<=kk;i++){
                v[++k]=v2[i];
                int lc=LCA(v2[i],v2[i-1]);
                if(lc^v2[i])son[lc].eb(v2[i]),v[++k]=lc;
            }
        }
        dfs1(1);dfs2(1);
        for(auto [u,i]:tr[p]){
            gmx(ans[i],tag[u]);
            if(f[u])gmx(ans[i],u);
        }
        for(int i=1;i<=k;i++)   f[v[i]]=tag[v[i]]=0,son[v[i]].clear();
    }
}
using namespace SegmentTree;
int main(){
    n=read();m=read();q=read();
    for(int i=1,u,v;i<n;i++)    u=read(),v=read(),adde(u,v);
    for(int i=1;i<=m;i++)   a[i]=read();
    for(int i=1;i<=q;i++){
        int l=read(),r=read(),u=read();
        upd(all,l,r,pii(u,i));
    }
    dfs(1,0);st_LCA::build();
    dfs(all);
    for(int i=1;i<=q;i++)   print(ans[i]),putc('\n');
    flush();
}