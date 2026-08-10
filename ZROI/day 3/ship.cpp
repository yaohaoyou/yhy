#pragma GCC optimize(2,3,"Ofast","inline")
#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define piiii pair<pii,pli>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e5+10,inf=1e9;
const ll INF=1e18;
int n,mx,my,q;
int a[maxn],b[maxn],c[maxn],d[maxn];
vector<pii> point[maxn],Q[maxn];
int K[maxn];
ll ans[maxn];
namespace FastIO{
    const int SIZ=1000000;static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    inline void flush(){fwrite(obuf,p3-obuf,1,stdout);}
    inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++;}
    inline void putc(char x){(p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}
    inline int read(){int x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline ll readll(){ll x=0,f=1;char c=getc();while(c<48||c>57){if(c=='-')f=-1;c=getc();}while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getc();x*=f;return x;}
    inline void print(ll x){if(!x)return putc(48),void();int len=0;if(x<0)x=-x,putc(45);while(x)cc[len++]=x%10+48,x/=10;while(len--)putc(cc[len]);}
}
using FastIO::read;using FastIO::readll;using FastIO::print;using FastIO::getc;using FastIO::putc;using FastIO::flush;
void discrete(){
    memc(c,a);sort(c+1,c+n+1);
    mx=unique(c+1,c+n+1)-c-1;
    for(int i=1;i<=n;i++)   a[i]=lower_bound(c+1,c+mx+1,a[i])-c;
    memc(d,b);sort(d+1,d+n+1);
    my=unique(d+1,d+n+1)-d-1;
    for(int i=1;i<=n;i++)   b[i]=lower_bound(d+1,d+my+1,b[i])-d;
}
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,my
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    priority_queue<ll,vector<ll>,greater<ll>> st[maxn],erast[maxn];
    pli tr[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);}
    inline void upd(int x,pli s){
        int p=1,l=1,r=my;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        st[x].ep(s.fi);while(!st[x].empty()&&!erast[x].empty()&&st[x].top()==erast[x].top())st[x].pop(),erast[x].pop();
        tr[p]=pli(st[x].top(),x);
        while(p>>=1)pu(p);
    }
    inline void era(int x,pli s){
        int p=1,l=1,r=my;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        erast[x].ep(s.fi);while(!st[x].empty()&&!erast[x].empty()&&st[x].top()==erast[x].top())st[x].pop(),erast[x].pop();
        tr[p]=st[x].empty()?pli(INF,inf):pli(st[x].top(),x);
        while(p>>=1)pu(p);
    }
    pli query(setpos,int pl,int pr){if(pl>pr)return pli(INF,inf);if(l>=pl&&r<=pr)return tr[p];setmid;pli res=pli(INF,inf);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=min(res,query(rson,pl,pr));return res;}
    void clear(){for(int i=0;i<(maxn<<2);i++)tr[i]=pli(INF,inf);}
}T[2][2];
inline void insL(int x,int y){
    T[0][0].upd(y,pli(-c[x]-d[y],y));
    T[0][1].upd(y,pli(-c[x]+d[y],y));
    T[1][0].era(y,pli(c[x]-d[y],y));
    T[1][1].era(y,pli(c[x]+d[y],y));
}
inline void insR(int x,int y){
    T[1][0].upd(y,pli(c[x]-d[y],y));
    T[1][1].upd(y,pli(c[x]+d[y],y));
}
vector<piiii> vec;
inline void era(int x,int y){
    vec.eb(pii(0,0),pli(-c[x]-d[y],y));
    T[0][0].era(y,pli(-c[x]-d[y],y));
    vec.eb(pii(0,1),pli(-c[x]+d[y],y));
    T[0][1].era(y,pli(-c[x]+d[y],y));
}
inline void era(int x,int y,pli w){
    vec.eb(pii(x,y),w);
    T[x][y].era(w.se,w);
}
main(){
    freopen("ship.in","r",stdin);freopen("ship.out","w",stdout);
    n=read();q=read();
    for(int i=1;i<=n;i++){
        int x=read(),y=read();
        a[i]=x+y;b[i]=x-y;
    }
    discrete();
    // for(int i=1;i<=n;i++)   debug("%lld : %lld %lld (%lld,%lld)\n",i,a[i],b[i],c[a[i]],d[b[i]]);
    for(int i=1;i<=n;i++)   point[a[i]].eb(a[i],b[i]);
    for(int i=1;i<=q;i++){
        int p=read(),k=read();
        int x=a[p],y=b[p];Q[x].eb(y,i);K[i]=k;
    }
    for(int i=0;i<4;i++)    T[i/2][i&1].clear();
    for(int i=1;i<=n;i++)   insR(a[i],b[i]);
    for(int i=1;i<=mx;i++){
        for(auto [x,y]:point[i])    insL(x,y);
        for(auto [y,id]:Q[i]){
            vec.clear();
            era(i,y);
            int k=K[id];
            pli o1=T[0][0].query(all,1,y),o2=T[0][1].query(all,y+1,my),
                o3=T[1][0].query(all,1,y),o4=T[1][1].query(all,y+1,my);
            while(k--){
                ll s1=c[i]+d[y]+o1.fi,s2=c[i]-d[y]+o2.fi,s3=-c[i]+d[y]+o3.fi,s4=-c[i]-d[y]+o4.fi;
                ll mn=min({s1,s2,s3,s4});ans[id]+=mn;
                if(s1==mn)era(0,0,o1),o1=T[0][0].query(all,1,y);
                else if(s2==mn)era(0,1,o2),o2=T[0][1].query(all,y+1,my);
                else if(s3==mn)era(1,0,o3),o3=T[1][0].query(all,1,y);
                else era(1,1,o4),o4=T[1][1].query(all,y+1,my);
            }
            for(auto j:vec) T[j.fi.fi][j.fi.se].upd(j.se.se,j.se);
        }
    }
    for(int i=1;i<=q;i++)   print(ans[i]>>1),putc('\n');flush();
}