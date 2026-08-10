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
const int maxn=1e6+10,B=1024,maxnB=maxn/B+10,V=1e5+1,maxV=V+10;
int n,q;
int a[maxn];
int bl[maxnB],br[maxnB],id[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
struct ques{int op,l,r,v;}Q[maxn];
struct DSU{
    int fa[maxV],cnt[maxV],v,tag;
    int clr[maxV<<4],cl;
    void clear(){tag=v=cl=0;iota(fa+1,fa+V+1,1);mems(cnt,0);}
    void init(){tag=v=0;for(int i=1;i<=cl;i++)fa[clr[i]]=clr[i],cnt[clr[i]]=0;cl=0;}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){assert(x<=v&&y<=v);x=find(x);y=find(y);if(x==y)return;fa[x]=y;cnt[y]+=cnt[x];cnt[x]=0;clr[++cl]=x;clr[++cl]=y;}
    inline int sum(int x){return cnt[x?find(x+tag):0];}
}U;
void build(){
    for(int i=1;i<=n;i++)   id[i]=(i-1)/B+1;
    for(int i=1;i<=id[n];i++){bl[i]=br[i-1]+1;br[i]=min(n,i*B);}
}
inline void broke(int x){for(int i=bl[x];i<=br[x];i++)a[i]=a[i]?(U.find(a[i])-U.tag):0;U.init();}
inline void rebuild(int x){U.v=0;for(int i=bl[x];i<=br[x];i++)U.v=max(U.v,a[i]),U.cnt[a[i]]++,U.clr[++U.cl]=a[i];}
inline void upd(int l,int r,int x,int o){
    if(!x)  return;
    if(l==bl[o]&&br[o]==r){
        int &v=U.v;
        if(v-U.tag<=x)    return;
        if(v-U.tag<=x+x){for(int j=x+U.tag+1;j<=v;j++)U.merge(j,j-x);v=x+U.tag;}
        else{for(int j=U.tag+1;j<=U.tag+x;j++)U.merge(j,j+x);U.tag+=x;}
        return;
    }
    broke(o);for(int i=l;i<=r;i++)(a[i]>x)&&(a[i]-=x);rebuild(o);
    // for(int i=1;i<=U.v;i++)   printf("%d %d\n",U.fa[i],U.cnt[i]);puts("");
}
inline int query(int l,int r,int x,int o){
    if(x+U.tag>U.v)   return 0;
    if(l==bl[o]&&br[o]==r)  return U.sum(x);
    int res=0;
    broke(o);for(int i=l;i<=r;i++)res+=a[i]==x;rebuild(o);
    // for(int i=1;i<=U.v;i++)   printf("%d %d\n",U.fa[i],U.cnt[i]);puts("");
    return res;
}
int ans[maxn],s0[maxn];
int main(){
    n=read();q=read();
    for(int i=1;i<=n;i++)   a[i]=read();
    for(int i=1;i<=n;i++)   s0[i]=s0[i-1]+(!a[i]);
    build();
    for(int i=1;i<=q;i++){
        int op=read(),l=read(),r=read(),x=read();
        Q[i]={op,l,r,x};
    }
    U.clear();
    for(int i=1;i<=id[n];i++){
        U.init();rebuild(i);
        for(int j=1;j<=q;j++){
            auto [op,l,r,x]=Q[j];
            if(r<bl[i]||l>br[i])    continue;
            if(op==1)   upd(max(l,bl[i]),min(r,br[i]),x,i);
            else    ans[j]+=query(max(l,bl[i]),min(r,br[i]),x,i);
        }
    }
    for(int i=1;i<=q;i++)if(Q[i].op==2&&!Q[i].v)ans[i]=s0[Q[i].r]-s0[Q[i].l-1];
    for(int i=1;i<=q;i++)if(Q[i].op==2)print(ans[i]),putc('\n');
    flush();
}