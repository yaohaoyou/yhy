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
const int maxn=1e6+10,mod=998244353;
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
int n,ans;
int a[maxn];
ll f[maxn],g[maxn],h[maxn],sum[maxn];
int sf[maxn],sg[maxn];
stack<int> stk;
void divide(int l,int r){
    if(l==r)    return madd(ans,max(0,a[l]));
    int mid=(l+r)>>1;
    f[mid]=g[mid]=h[mid]=max(0,a[mid]);
    ll s=a[mid];
    for(int i=mid-1;i>=l;i--)   f[i]=max(f[i+1],h[i+1]+a[i]),h[i]=max(h[i+1]+a[i],0ll),g[i]=max(g[i+1],s+=a[i]);
    sf[mid]=sg[mid]=0;
    sf[mid+1]=sg[mid+1]=f[mid+1]=g[mid+1]=h[mid+1]=max(0,a[mid+1]);
    s=a[mid+1];
    for(int i=mid+2;i<=r;i++){
        f[i]=max(f[i-1],h[i-1]+a[i]),h[i]=max(h[i-1]+a[i],0ll),g[i]=max(g[i-1],s+=a[i]);
        sf[i]=imadd(sf[i-1],f[i]%mod),sg[i]=imadd(sg[i-1],g[i]%mod);
    }
    for(int i=mid,j=mid+1,j2=mid+1;i>=l;i--){
        while(j<=r&&max({f[i],f[j],g[i]+g[j]})==f[i])   j++;
        // [mid+1,j-1]
        madd(ans,immul(f[i]%mod,j-mid-1));
        j2=max(j2,j);
        while(j2<=r&&max({f[i],f[j2],g[i]+g[j2]})^f[j2])  j2++;
        // [j2,r]
        madd(ans,imdel(sf[r],sf[j2-1]));
        // [j,j2-1]
        madd(ans,immul(g[i]%mod,j2-j));
        madd(ans,imdel(sg[j2-1],sg[j-1]));
    }
    divide(l,mid);divide(mid+1,r);
}
void matt(){
    ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   sum[i]=sum[i-1]+a[i];
    while(!stk.empty())stk.pop();
    sum[-1]=1e18;stk.ep(-1);stk.ep(0);
    int s=0,ss=0;
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&sum[stk.top()]<sum[i]){
            int x=stk.top();
            stk.pop();
            int l=stk.top()+1;
            mdel(s,immul(x-l+1,(sum[x]%mod+mod)%mod));
        }
        int l=stk.top()+1;
        madd(s,immul(i-l+1,(sum[i]%mod+mod)%mod));
        stk.ep(i);
        madd(ss,(sum[i]%mod+mod)%mod);
        madd(ans,imdel(s,ss));
    }
    divide(1,n);
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}