#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e6+10,mod=998244353,P=1e9+7,inv2=(mod+1)>>1,i2=(P+1)>>1;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
struct mt{
    int v;
    mt(ll _x=0){v=_x%P;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=P)&&(v-=P);}
    inline mt operator+(int y){y+=v;(y>=P)&&(y-=P);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=P);}
    inline mt operator-(int y){y=v-y;(y<0)&&(y+=P);return y;}
    inline void operator*=(int y){v=1ull*v*y%P;}
    inline mt operator*(int y){return 1ull*v*y%P;}
};
bool mem1;
int n;
ll ans;
struct hsh{
    size_t operator()(const pii &x)const{return ((ll)x.fi<<30)^x.se;}
};
__gnu_pbds::cc_hash_table<pii,int,hsh> mp;
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    mit tl[maxn],tr[maxn];
    mt TL[maxn],TR[maxn];
    void dfs(setpos){
        if(l==r)    return tl[l]=tr[l]=l,TL[l]=TR[l]=l,ans++,void();
        setmid;dfs(lson);dfs(rson);
        for(int i=l;i<=mid;i++) mp[pii(tl[i]-i,TL[i]-i)]++;
        for(int i=mid+1;i<=r;i++)if(mp.find(pii(mit(i)-tr[i],mt(i)-TR[i]))!=mp.end())ans+=mp[pii(mit(i)-tr[i],mt(i)-TR[i])];
        for(int i=l;i<=mid;i++) mp[pii(tl[i]-i,TL[i]-i)]--;
        for(int i=l;i<=mid;i++) tl[i]=(tl[i]+tl[mid+1])*inv2,TL[i]=(TL[i]+TL[mid+1])*i2;
        for(int i=mid+1;i<=r;i++)   tr[i]=(tr[i]+tr[mid])*inv2,TR[i]=(TR[i]+TR[mid])*i2;
    }
    // mit query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return sum[p];setmid;return pr<=mid?query(lson,pl,pr):pl>mid?query(rson,pl,pr):(query(lson,pl,pr)+query(rson,pl,pr))*(mod+1>>1);}
}
using namespace SegmentTree;
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    ans=0;dfs(all);
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}