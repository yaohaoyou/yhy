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
const int maxn=1e6+10,mod=1e9+7;
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
int n,d;
int a[maxn],b[maxn];
int dp[maxn];
vector<int> v,va;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=imadd(tr[ls],tr[rs]);}
    inline void pt(int p,int s){mmul(tr[p],s);mmul(tag[p],s);}
    inline void pd(int p){if(tag[p]^1)pt(ls,tag[p]),pt(rs,tag[p]),tag[p]=1;}
    void upd(setpos,int pl,int pr){if(l>=pl&&r<=pr)return pt(p,2);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr);if(pr>mid)upd(rson,pl,pr);pu(p);}
    // int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];pd(p);setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)madd(res,query(rson,pl,pr));return res;}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
}
using namespace SegmentTree;
int main(){
    scanf("%d%d",&n,&d);
    fill(tag+1,tag+(n<<2)+1,1);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    a[n+1]=2e9;b[n+1]=1;
    int ans=0;
    for(int i=1;i<=n+1;i++){
        if(!b[i]){
            int k=lower_bound(va.begin(),va.end(),a[i]-d)-va.begin();
            if(k>=0&&k<va.size())   upd(all,v[k],v.back());
            // for(int j:v)if(a[i]-a[j]<=d)mmul(dp[j],2);
        }
        else{
            // for(int j:v)madd(dp[i],dp[j]);
            dp[i]=imadd(1,tr[1]);upd(i,dp[i]);
            v.eb(i);va.eb(a[i]);
        }
    }
    printf("%d\n",imdel(dp[n+1],1));
}