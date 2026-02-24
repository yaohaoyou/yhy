#include<bits/stdc++.h>
#define ll long long
#define int long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define ppc(x) __builtin_popcountll(x)
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int lgV=60;
int n,q;
ll L,R;
int cnt[2];
ll f[lgV+5][lgV+5][2];
pll slv(ll R){
    if(R==-1)   return pll(0,0);
    mems(f,0);
    f[lgV+1][0][1]=1;
    for(int i=lgV,k=1;~i;i--,k++){
        ll x=1ll<<i;bool o=R&x;
        if(!o){
            for(int j=0;j<=k;j++){
                f[i][j][1]=f[i+1][j][1];
                f[i][j][0]=f[i+1][j][0];
                if(j)   f[i][j][0]+=f[i+1][j-1][0];
            }
        }
        else{
            for(int j=0;j<=k;j++){
                if(j)   f[i][j][1]=f[i+1][j-1][1];
                f[i][j][0]=f[i+1][j][1]+f[i+1][j][0];
                if(j)   f[i][j][0]+=f[i+1][j-1][0];
            }
        }
    }
    pll ans=pll(0,0);
    for(int i=0;i<=lgV;i++)if(i&1)ans.fi+=f[0][i][0]+f[0][i][1];else ans.se+=f[0][i][0]+f[0][i][1];
    assert(ans.fi+ans.se==R+1);
    return ans;
}
inline ll query(ll l,ll r){pll x=slv(r),y=slv(l-1);return max(x.fi-y.fi,x.se-y.se);}
inline ll lowbit(ll x){return x&(-x);}
inline ll low0(ll x){return lowbit(~x);}
inline void out(ll l,ll r){
    cnt[0]=cnt[1]=0;
    for(ll i=l;i<=r;i++)cnt[ppc(i)&1]++;
    if(cnt[0]>=cnt[1]){
        for(ll i=l;i<=r;i++)putchar((!(ppc(i)&1))+'0');
    }
    else{
        for(ll i=l;i<=r;i++)putchar((ppc(i)&1)+'0');
    }
}
void matt(int _cases){
    scanf("%lld%lld%lld",&q,&L,&R);
    if(!q){
        ll x=L,l=L,r,ans=0;
        while(l<=R){
            L=l;x=l;r=l;
            while(L+low0(x)<=R){
                x+=low0(x);r=min(x,R);
                l+=lowbit(l);
            }
            ans+=query(L,r);
            l=r+1;
        }
        printf("%lld\n",ans);
    }
    else{
        ll x=L,l=L,r,ans=0;
        while(l<=R){
            L=l;x=l;r=l;
            while(L+low0(x)<=R){
                x+=low0(x);r=min(x,R);
                l+=lowbit(l);
            }
            out(L,r);
            l=r+1;
        }
        putchar('\n');
    }
}
main(){int T;scanf("%lld",&T);for(int i=1;i<=T;i++)matt(i);}