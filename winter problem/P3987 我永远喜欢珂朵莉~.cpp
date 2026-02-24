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
const int maxn=1e5+10,maxv=5e5+10;
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline void pus(string s){int _len=s.length();for(int i=0;i<_len;i++)putc(s[i]);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(auto x){if(!x)return putc(48),void();if(x==INT_MIN)return pus("-2147483648"),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::pus;using FastIO::flush;
int n,q;
int tot;
int a[maxn];
vector<int> fac[maxv],V[maxv],vid[maxv];
pii rnk[maxn*200];
struct DSU{
    int fa[maxn*200];
    void init(){iota(fa+1,fa+tot+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(x)]=find(y);}
    inline int operator[](int x){return find(x);}
}U;
struct BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline ll query(int l,int r){return que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
void makefactors(int x,int id){for(int i:fac[x])V[i].eb(id);}
void init(){
    const int V=5e5;
    for(int i=1;i<=V;i++)for(int j=i;j<=V;j+=i)fac[j].eb(i);
}
int main(){
    init();exit(0);
    n=read();q=read();
    for(int i=1;i<=n;i++){
        a[i]=read();
        makefactors(a[i],i);
        T.add(i,a[i]);
    }
    for(int i=1;i<=maxv;i++){
        if(V[i].empty())    continue;
        for(int j=0;j<V[i].size();j++)  vid[i].eb(++tot),rnk[tot]=pii(i,j);
        vid[i].eb(++tot);rnk[tot]=pii(i,V[i].size());
    }
    U.init();
    while(q--){
        int op=read(),l=read(),r=read(),x;
        if(op==1){
            x=read();
            if(x==1||V[x].empty())  continue;
            int p=lower_bound(V[x].begin(),V[x].end(),l)-V[x].begin();
            p=U[vid[x][p]];
            if(rnk[p].se==V[x].size()||V[x][rnk[p].se]>r)  continue;
            while(true){
                p=rnk[p].se;if(p>=V[x].size())break;
                int i=V[x][p];if(i>r) break;
                if(a[i]%x==0){T.add(i,-a[i]+a[i]/x);a[i]/=x;}
                if(a[i]%x)U.merge(vid[x][p],vid[x][p+1]);
                p=U[vid[x][p+1]];
            }
        }
        else    print(T.query(l,r)),putc('\n');
    }
    flush();
}