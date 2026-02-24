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
const int maxn=5e5+10,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],b[maxn],c[maxn],i2[maxn<<1],p2[maxn<<1];
struct SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int c0[maxn<<2],tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){
        c0[p]=c0[ls]+c0[rs];
        tr[p]=imadd(tr[ls],tr[rs]);
    }
    inline void pt(int p,int s){mmul(tag[p],s);mmul(tr[p],s);}
    inline void pd(int p){if(tag[p]^1){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=1;}}
    pii query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pii(tr[p],c0[p]);pd(p);setmid;pii res=pii(0,0);if(pl<=mid)res=query(lson,pl,pr);if(pr>mid){pii tmp=query(rson,pl,pr);madd(res.fi,tmp.fi);res.se+=tmp.se;}return res;}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p,2);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    void upd(int x){
        int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        c0[p]=tr[p]=tag[p]=0;
        while(p>>=1)pu(p);
    }
    void build(setpos){tag[p]=1;if(l==r)return tr[p]=0,c0[p]=1,void();setmid;build(lson);build(rson);pu(p);}
}T[3];
vector<int> di;
vector<int> v[maxn<<1];
void discrete(){
    for(int i=1;i<=n;i++)   di.eb(a[i]),di.eb(b[i]);
    sort(di.begin(),di.end());di.erase(unique(di.begin(),di.end()),di.end());
    for(int i:di){
        int x=lower_bound(di.begin(),di.end(),a[i])-di.begin()+1,y=lower_bound(di.begin(),di.end(),b[i])-di.begin()+1;
        v[x].eb(i);v[y].eb(i);
    }
}
inline void mdf(int x){
    c[x]++;T[0].upd(x);T[1].upd(x);
    T[0].upd(all,x,n);T[1].upd(all,1,x);
}
int main(){
    scanf("%d",&n);
    p2[0]=1;for(int i=1;i<=n+n;i++)   p2[i]=imadd(p2[i-1],p2[i-1]);
    i2[0]=1;for(int i=1;i<=n+n;i++)   i2[i]=immul(i2[i-1],(mod+1)>>1);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    discrete();
    T[0].build(all);T[1].build(all);T[3].build(all);
    int ans=0;
    for(int i=1;i<=n;i++)   mdel(ans,immul(a[i]+b[i],p2[n-1]));
    int L=n+1,R=0,l=n+1,r=0;
    for(int i=di.size();i;i--){
        for(int j:v[i]){mdf(j);if(c[j]==2) L=min(L,j),R=max(R,j);if(c[j]==1)l=min(l,j),r=max(r,j);}
        int len=di[i-1]-(i>1?di[i-2]:0),res=0;
        if(L<=R){
            madd(res,immul(R-L+1,p2[n]));
            if(l<L){
                pii t=T[0].query(all,l,L-1);
                madd(res,imdel(immul(t.se,p2[n]),t.fi));
            }
            if(r>R){
                pii t=T[1].query(all,R+1,r);
                madd(res,imdel(immul(t.se,p2[n]),t.fi));
            }
        }
        else{

        }
    }
    // madd(ans,immul(tr[1].sum,lst));
    printf("%d\n",ans);
}