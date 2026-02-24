#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,base=547547;
const ll mod=1000000000000000003ll;
int n,m,q;
int a[maxn],dep[maxn];
ll hsh[maxn],pq[maxn];
namespace MyMod{
    inline void madd(ll &x,ll y){(x+=y)%=mod;}
    inline void mdel(ll &x,ll y){x-=y;(x+=mod)%=mod;}
    inline void mmul(ll &x,ll y){x=__int128(x)*y%mod;}
    inline ll imadd(ll x,ll y){madd(x,y);return x;}
    inline ll imdel(ll x,ll y){mdel(x,y);return x;}
    inline ll immul(ll x,ll y){mmul(x,y);return x;}
    inline ll qpow(ll x,ll y){
        ll res=1;
        while(y){
            if(y&1) mmul(res,x);
            mmul(x,x);
            y>>=1;
        }
        return res;
    }
}
using namespace MyMod;
namespace Graph{
    vector<int> son[maxn];
    inline void add(int u,int v){son[u].eb(v);}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
unordered_map<ll,int> mp;
void dfs(int u,int k,int fa){
    dep[u]=dep[fa]+1;
    hsh[u]=imadd(hsh[fa],immul(k,pq[dep[u]]));
    // printf("%d %d %llu\n",u,dep[u],hsh[u]);
    mp[hsh[u]]=u;
    sort(son[u].begin(),son[u].end());
    int s=1;
    for(int t:son[u]){
        if(t==fa)   continue;
        dfs(t,s,u);
        s++;
    }
}
void init(){pq[0]=1;for(int i=1;i<=max(n,m);i++)pq[i]=immul(pq[i-1],base);}
namespace BIT{
    ll tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,ll s){while(x<=n){madd(tr[x],s);x+=lowbit(x);}}
    inline ll que(int x){ll res=0;while(x){madd(res,tr[x]);x-=lowbit(x);}return res;}
    inline ll query(int l,int r){return imdel(que(r),que(l-1));}
}
using BIT::query;
namespace IO{
    const int SIZ=1000000;
    static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    #define if(sth) if(__builtin_expect(sth,1))
    #define while(sth) while(__builtin_expect(sth,1))
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
    inline void print(int x){ 
        if(!x)return putchar(48),void();
        int len=0;
        if(x<0)x=-x,putchar(45);
        while(x)cc[len++]=x%10+48,x/=10;
        while(len--)putchar(cc[len]);
        putchar(10);
    }
}
using namespace IO;
int main(){
    // freopen("D:\\yhy\\P5537_2.in","r",stdin);
    // freopen("D:\\yhy\\P5537.out","w",stdout);
    n=read();m=read();q=read();
    init();
    int rt;
    for(int i=1;i<=n;i++){
        int x=read();
        if(x)   adde(i,x);
        else    rt=i;
    }
    dep[0]=-1;
    dfs(rt,0,0);
    for(int i=1;i<=m;i++){
        a[i]=read();
        BIT::add(i,immul(a[i],pq[i]));
        // printf("%d\n",a[i]*pq[i]);
    }
    while(q--){
        int opt=read(),x=read(),l=read(),r;
        // printf("%d %d\n",immul(1,pq[2]),query(2,2));
        if(opt==1){
            r=read();
            int pl=1,pr=r-l+1,res=-1;
            ll inv;
            if(l-dep[x]-1>=0)   inv=qpow(pq[l-dep[x]-1],mod-2);
            else    inv=pq[dep[x]-l+1];
            // printf("%lld\n",query(1,2));
            while(pl<=pr){
                int mid=(pl+pr)>>1;
                if(mp.find(imadd(hsh[x],immul(query(l,l+mid-1),inv)))!=mp.end()){
                    res=mid;
                    pl=mid+1;
                }
                else    pr=mid-1;
            }
            int out;
            if(~res)    out=mp[imadd(hsh[x],immul(query(l,l+res-1),inv))];
            else   out=x;
            // if(out==136285){fprintf(stderr,"%d %d %d %d %d\n",x,dep[x],l,a[l],son[x].size());exit(0);}
            print(out);
        }
        else{
            // printf("nboj %d\n",immul(imdel(l,a[x]),pq[x]));
            BIT::add(x,immul(imdel(l,a[x]),pq[x]));a[x]=l;
        }
    }
    flush;
}