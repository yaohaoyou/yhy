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
const int maxn=5e5+10;
int n,m,q;
int a[maxn],b[maxn];
pii c[maxn];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    ll sum[maxn<<2],tr[maxn<<2];
    inline void pu(int p){tr[p]=tr[ls]+tr[rs];sum[p]=sum[ls]+sum[rs];}
    ll QTR(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid;ll res=0;if(pl<=mid)res=QTR(lson,pl,pr);if(pr>mid)res+=QTR(rson,pl,pr);return res;}
    ll QS(setpos,int pl,int pr){if(l>=pl&&r<=pr)return sum[p];setmid;ll res=0;if(pl<=mid)res=QS(lson,pl,pr);if(pr>mid)res+=QS(rson,pl,pr);return res;}
    inline void upd(int x,int s1,ll s2){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s1;sum[p]=s2;while(p>>=1)pu(p);}
    inline int bry(ll s){
        int p=1,l=1,r=n,ans=0;
        while(l^r){
            setmid;
            if(tr[ls]>=s)   p=ls,r=mid;
            else    s-=tr[ls],p=rs,l=mid+1;
        }
        return l;
    }
}T[2];
ll solve(){
    ll x=T[0].tr[1]-T[1].tr[1],sum=T[0].sum[1]+T[1].sum[1];
    x>>=1;
    if(!x)  return sum;
    if(x>0){
        int k=T[0].bry(x);
        if(k^1){
            sum-=T[0].QS(all,1,k-1)*2;
            x-=T[0].QTR(all,1,k-1);
        }
        sum-=x*c[k].fi;
    }
    else{
        int k=T[1].bry(-x);
        if(k^1){
            sum-=T[1].QS(all,1,k-1)*2;
            x+=T[1].QTR(all,1,k-1);
        }
        sum-=x*c[k].fi;
    }
    // ll x=0,sum=0;
    // for(int i=1;i<=n;i++){
    //     if(c[i].fi>=0)  sum+=1ll*c[i].fi*a[c[i].se],x+=a[c[i].se];
    //     else    sum-=1ll*c[i].fi*a[c[i].se],x-=a[c[i].se];
    // }
    // printf("x = %lld\n",x);
    // if(x>0){
    //     for(int i=1;i<=n;i++)if(c[i].fi>=0){
    //         ll w=min(x,a[c[i].se]*2ll);
    //         sum-=1ll*w*c[i].fi;
    //         x-=w;if(!x)break;
    //     }
    // }
    // else{
    //     for(int i=1;i<=n;i++)if(c[i].fi<0){
    //         ll w=max(x,-a[c[i].se]*2ll);
    //         sum-=1ll*w*c[i].fi;
    //         x-=w;if(!x)break;
    //     }
    // }
    return sum;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);rotate(a+1,a+n,a+n+1);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);c[u+1].fi++;c[v+1].fi--;}
    for(int i=n;i;i--)  c[i].fi+=c[i+1].fi,c[i].se=i;
    sort(c+1,c+n+1,[&](pii x,pii y){return pii(abs(x.fi),x.se)<pii(abs(y.fi),y.se);});
    for(int i=1;i<=n;i++)if(c[i].fi>=0)T[0].upd(i,a[c[i].se]*2,1ll*c[i].fi*a[c[i].se]);else T[1].upd(i,a[c[i].se]*2,-1ll*c[i].fi*a[c[i].se]);
    for(int i=1;i<=n;i++)   b[c[i].se]=i;
    while(q--){
        int x,y;scanf("%d%d",&x,&y);x=(x+1)%n+1;
        a[x]=y;x=b[x];
        if(c[x].fi>=0)T[0].upd(x,a[c[x].se]*2,1ll*c[x].fi*a[c[x].se]);else T[1].upd(x,a[c[x].se]*2,-1ll*c[x].fi*a[c[x].se]);
        printf("%lld\n",solve());
    }
}