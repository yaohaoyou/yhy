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
const int maxd=50;
int d;
ll s,k;
ll f[maxd];
inline void getmn(auto &x,auto y){(x>y)&&(x=y);}
inline ll calc(ll x){
    ll res=0;
    for(int i=0;i<d;i++)if(x>=f[i])res+=(x-f[i])/d+bool(i);
    return res;
}
void matt(){
    scanf("%lld%lld",&s,&k);
    d=1;while(s%d==0)d++;
    mems(f,0x3f);f[0]=0;
    ll lim=(s-1)/2;
    while(true){
        ll mn=1e18;
        for(int x=1;x<d;x++){
            ll v=0;
            for(int i=1;i<d;i++)    v=max(v,(s-f[((s-i*x)%d+d)%d])/i+1);
            while((v%d)^x)  v++;
            if(f[x]<=v) continue;
            mn=min(mn,v);
        }
        if(mn>lim) break;
        f[mn%d]=mn;
        for(int i=1;i<d;i++)
            for(int j=0;j<d;j++){
                if(f[i]+__int128(mn)*j>s) break;
                getmn(f[(i+mn*j)%d],f[i]+mn*j);
            }
    }
    if(k>lim)   return puts("-1"),void();
    // for(int i=0;i<d;i++)    printf("%d ",f[i]);puts("");
    // for(int i=1;i<=lim;i++)    if(calc(i)!=calc(i-1)) printf("%d ",i);puts("");
    // for(int i=s-lim;i<=s;i++)    if(calc(s-i-1)==calc(s-i)) printf("%d ",i);puts("");
    ll cnt=calc(lim);
    if(cnt>=k){
        ll l=1,r=lim,p=0;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(calc(mid)>=k)    p=mid,r=mid-1;
            else    l=mid+1;
        }
        printf("%lld\n",p);
    }
    else{
        ll l=1,r=lim,p=0;
        while(l<=r){
            ll mid=(l+r)>>1;
            if(lim-(mid-1-calc(mid-1))>=k)    p=s-mid,l=mid+1;
            else    r=mid-1;
        }
        printf("%lld\n",p);
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}