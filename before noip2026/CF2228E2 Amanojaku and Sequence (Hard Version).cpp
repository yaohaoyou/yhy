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
bool mem1;
const int maxn=3e5+10,maxv=2e6+10,mod=998244353;
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
int n,q;
int a[maxn];
// int c[maxn],s[maxn];
int fac[maxv],inv[maxv];
void init(){
    const int N=2e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x==y?1:x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
struct nd{
    ll x;int x2,len;
    nd(ll _x=0,int _y=0,int _l=0){x=_x;x2=_y;len=_l;}
    inline void operator+=(ll k){
        int mx=x%mod;(mx<0)&&(mx+=mod);
        x+=k*len;k%=mod;(k<0)&&(k+=mod);
        madd(x2,2ull*mx*k%mod);
        madd(x2,1ull*len*k%mod*k%mod);
    }
    inline nd operator+(nd y){return {x+y.x,imadd(x2,y.x2),len+y.len};}
};
struct node{
    int x,y,xy,len;
    node(int _x=0,int _y=0,int _xy=0,int _l=0){x=_x;y=_y;xy=_xy;len=_l;}
    inline void adx(int k){madd(x,immul(k,len));madd(xy,immul(k,y));}
    inline void ady(int k){madd(y,immul(k,len));madd(xy,immul(k,x));}
    inline node operator+(node z){return {imadd(x,z.x),imadd(y,z.y),imadd(xy,z.xy),len+z.len};}
};
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    nd tr[maxn<<2];ll tag[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pt(int p,ll s){tr[p]+=s;tag[p]+=s;}
    inline void pd(int p){if(tag[p])pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=0;}
    void build(setpos){tag[p]=0;if(l==r)return tr[p]={0,0,1},void();setmid;build(lson);build(rson);pu(p);}
    nd Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid;return pr<=mid?Q(lson,pl,pr):pl>mid?Q(rson,pl,pr):Q(lson,pl,pr)+Q(rson,pl,pr);}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
}c,s;
struct SGT{
    node tr[maxn<<2];int ax[maxn<<2],ay[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];}
    inline void pta(int p,int s){tr[p].adx(s);madd(ax[p],s);}
    inline void ptb(int p,int s){tr[p].ady(s);madd(ay[p],s);}
    inline void pd(int p){if(ax[p])pta(ls,ax[p]),pta(rs,ax[p]),ax[p]=0;if(ay[p])ptb(ls,ay[p]),ptb(rs,ay[p]),ay[p]=0;}
    void build(setpos){ax[p]=ay[p]=0;if(l==r)return tr[p]={0,0,0,1},void();setmid;build(lson);build(rson);pu(p);}
    void upa(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pta(p,s);setmid;pd(p);if(pl<=mid)upa(lson,pl,pr,s);if(pr>mid)upa(rson,pl,pr,s);pu(p);}
    void upb(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return ptb(p,s);setmid;pd(p);if(pl<=mid)upb(lson,pl,pr,s);if(pr>mid)upb(rson,pl,pr,s);pu(p);}
    node Q(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;pd(p);return pr<=mid?Q(lson,pl,pr):pl>mid?Q(rson,pl,pr):Q(lson,pl,pr)+Q(rson,pl,pr);}
}cs;
bool mem2;
void matt(int _cases){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    c.build(all);s.build(all);cs.build(all);
    for(int i=1;i<=n;i++)
        if(~a[i])   s.upd(all,i,n,a[i]),cs.upa(all,i,n,a[i]);
        else    c.upd(all,i,n,1),cs.upb(all,i,n,1);
    while(q--){
        int op,l,r,m;
        scanf("%d%d%d",&op,&l,&r);
        if(op==1){
            if(~a[l])   s.upd(all,l,n,-a[l]),cs.upa(all,l,n,mod-a[l]);
            else    c.upd(all,l,n,-1),cs.upb(all,l,n,mod-1);
            a[l]=r;
            if(~a[l])   s.upd(all,l,n,a[l]),cs.upa(all,l,n,a[l]);
            else    c.upd(all,l,n,1),cs.upb(all,l,n,1);
        }
        else{
            scanf("%d",&m);
            ll sum=m-s.Q(all,r,r).x;int cr=c.Q(all,r,r).x,ans=0;
            nd wc=c.Q(all,l,r),ws=s.Q(all,l,r);
            if(l^1){
                sum+=s.Q(all,l-1,l-1).x;
                // mdel(cr,c.Q(all,l-1,l-1).x);
                cr-=c.Q(all,l-1,l-1).x;
                wc+=-c.Q(all,l-1,l-1).x;
                ws+=-s.Q(all,l-1,l-1).x;
            }
            if(sum>m)while(1);
            if(sum<0){puts("0");continue;}
            madd(ans,immul(ws.x2,C(sum+cr-1,cr-1)));
            node W=cs.Q(all,l,r);
            if(l^1){
                int cx=cs.Q(all,l-1,l-1).x,cy=cs.Q(all,l-1,l-1).y;
                W.adx(mod-cx);W.ady(mod-cy);
            }
            madd(ans,2ull*W.xy*C(sum+cr-1,cr)%mod);
            madd(ans,immul(wc.x%mod,C(sum+cr-1,cr)%mod));
            madd(ans,immul(imadd(wc.x%mod,wc.x2),C(sum+cr-1,cr+1)));
            printf("%d\n",ans);
            // for(int i=l;i<=r;i++){
            //     madd(ans,1ull*s[i]*s[i]%mod*C(sum+c[r]-1,c[r]-1)%mod);
            //     madd(ans,2ull*s[i]*c[i]%mod*C(sum+c[r]-1,c[r])%mod);
            //     madd(ans,immul(c[i],C(sum+c[r]-1,c[r])));
            //     madd(ans,1ull*c[i]*(c[i]+1)%mod*C(sum+c[r]-1,c[r]+1)%mod);
            // }
        }
    }
}
int main(){init();debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}