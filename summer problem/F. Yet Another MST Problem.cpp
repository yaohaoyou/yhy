#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define us multiset<int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=4e5+10;
bool mem1;
int n,m;
int a[maxn];
pii b[maxn],p[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(int x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
map<pii,int> mp;
pii ss[maxn<<2];int tot;
vector<pii> res;
int al;
// struct SegmentTree{
//     #define ls p<<1
//     #define rs p<<1|1
//     #define lson ls,l,mid
//     #define rson rs,mid+1,r
//     #define all 1,0,n+1
//     #define setmid int mid=(l+r)>>1
//     #define setpos int p,int l,int r
//     us tr[maxn<<2];
//     inline void add(int x,pii s){
//         if(mp.find(s)==mp.end())mp[s]=++tot,ss[tot]=s;int id=mp[s];
//         int p=1,l=0,r=n+1;while(l^r){tr[p].ep(id);al++;setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p].ep(id);al++;
//     }
//     inline void era(int x,pii s){int id=mp[s];int p=1,l=0,r=n+1;while(l^r){tr[p].erase(tr[p].find(id));setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p].erase(tr[p].find(id));}
//     inline void query(setpos,int pl,int pr){if(l>=pl&&r<=pr){for(int i:tr[p])res.ep(ss[i]);return;}setmid;if(pl<=mid)query(lson,pl,pr);if(pr>mid)query(rson,pl,pr);}
// }T[2];
// inline int lowbit(int x){return x&-x;}
// struct BIT{
//     us tr[maxn];
//     inline void add(int x,pii s){if(mp.find(s)==mp.end())mp[s]=++tot,ss[tot]=s;int id=mp[s];while(x){tr[x].ep(id);x^=lowbit(x);}}
//     inline void era(int x,pii s){int id=mp[s];while(x){tr[x].erase(tr[x].find(id));x^=lowbit(x);}}
//     inline void query(int x){while(x<=n){for(int i:tr[x])res.eb(ss[i]);x+=lowbit(x);}}
// }T0;
// struct BIT2{
//     us tr[maxn];
//     inline void add(int x,pii s){if(mp.find(s)==mp.end())mp[s]=++tot,ss[tot]=s;int id=mp[s];while(x<=n){tr[x].ep(id);x+=lowbit(x);}}
//     inline void era(int x,pii s){int id=mp[s];while(x<=n){tr[x].erase(tr[x].find(id));x+=lowbit(x);}}
//     inline void query(int x){while(x){for(int i:tr[x])res.eb(ss[i]);x^=lowbit(x);}}
// }T1;
multiset<pii> sl,sr;
bool mem2;
void data(){
    srand(time(0));
    n=m=3e5;
    printf("%d %d\n",n,m);
    iota(a+2,a+n+1,1);
    random_shuffle(a+1,a+n+1);
    for(int i=1;i<=n;i++) printf("%d ",a[i]);puts("");
    for(int i=1;i<=m;i++){
        int l=rand()%n+1,r=rand()%n+1;
        if(l>r)swap(l,r);
        printf("%d %d\n",l,r);
    }
    exit(0);
}
int main(){
    debug("%.2lfMB\n",abs(&mem1-&mem2)/1024./1024);
    // data();
    n=read();m=read();
    b[0]=pii(n,0);b[n+1]=pii(n,n+1);
    for(int i=1;i<=n;i++)   a[i]=read(),b[i]=pii(a[i],i);
    for(int i=1;i<=m;i++)   p[i].fi=read(),p[i].se=read();
    sort(b,b+n+2);
    int edg=m-1;ll ans=0;
    // for(int i=1;i<=m;i++)   T0.add(p[i].fi,p[i]),T1.add(p[i].se,p[i]);
    for(int i=1;i<=m;i++)   sl.ep(p[i]),sr.ep(p[i].se,p[i].fi);
    // debug("al = %d\n",al);
    for(int i=0;i<=n+1;i++){
        int x=b[i].se;
        // debug("b[i] = %d %d\n",b[i].fi,b[i].se);
        // printf("b[%d] = %d\n",i,x);
        int siz=0;
        res.clear();
        int L=0,R=n+1;
        if(x!=n+1){
            // T0.query(x+1);
            auto it=sl.lower_bound(pii(x+1,0));
            siz+=res.size();
            // for(pii j:res)  T0.era(j.fi,j),T1.era(j.se,j),L=max(L,j.fi),R=min(R,j.se);
            while(it!=sl.end()){
                auto j=*it;
                sr.erase(sr.find(pii(j.se,j.fi)));
                L=max(L,j.fi);R=min(R,j.se);
                siz++;
                it=sl.erase(it);
            }
        }
        res.clear();
        if(x){
            // T1.query(x-1);
            // siz+=res.size();
            // for(pii j:res)  T0.era(j.fi,j),T1.era(j.se,j),L=max(L,j.fi),R=min(R,j.se);
            auto it=sr.lower_bound(pii(x,0));
            if(it!=sr.begin()){
                it--;
                for(auto k=it;k!=sr.begin();k--){
                    auto j=*k;
                    sl.erase(sl.find(pii(j.se,j.fi)));
                    L=max(L,j.se);R=min(R,j.fi);
                    siz++;
                }
                auto k=sr.begin();
                auto j=*k;
                sl.erase(sl.find(pii(j.se,j.fi)));
                L=max(L,j.se);R=min(R,j.fi);
                siz++;
                
                while(k!=sr.end()&&k->fi<x) k=sr.erase(k);
            }
        }
        // printf("res.size = %d\n",res.size());
        if(!siz) continue;
        edg-=(siz-1);
        ans+=1ll*b[i].fi*(siz-1);
        // T0.add(L,pii(L,R));T1.add(R,pii(L,R));
        sl.ep(L,R);sr.ep(R,L);
        // debug("edg = %d\n",edg);
        if(!edg)    break;
    }
    printf("%lld\n",ans);
}