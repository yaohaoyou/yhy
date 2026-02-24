#include<bits/stdc++.h>
#define if(sth) if(__builtin_expect(sth,1))
#define ll long long
#define eb emplace_back
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=60,mod=1e9+7;
ll n;int m,k,K;
ll a[maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace MyMod;
int fac[maxn],inv[maxn],invv[maxn];
int f1[maxn],pre[maxn],suf[maxn];
int f2[maxn];
void init(){
    fac[0]=1;
    for(int i=1;i<=K;i++)   fac[i]=immul(fac[i-1],i);
    inv[K]=qpow(fac[K],mod-2);
    for(int i=K-1;~i;i--)   inv[i]=immul(inv[i+1],i+1);
    for(int i=1;i<=K;i++)   invv[i]=immul(inv[i-1],inv[K-i]);
}
inline int func1(int x){
    int ret=0;
    pre[0]=suf[K+1]=1;
    for(int i=1;__builtin_expect(i<=K,1);i++)   pre[i]=1ll*pre[i-1]*(x-i+mod)%mod;
    for(int i=K;__builtin_expect(i,1);i--)  suf[i]=1ll*suf[i+1]*(x-i+mod)%mod;
    for(int i=1;__builtin_expect(i<=K,1);i++){
        // int p=1ll*f1[i]*pre[i-1]%mod*suf[i+1]%mod,q=1ll*inv[i-1]*inv[K-i]%mod,res=immul(p,q);
        int res=1ll*f1[i]*pre[i-1]%mod*suf[i+1]%mod*invv[i]%mod;
        if((K-i)&1) res=mod-res;
        madd(ret,res);
        // int res=f1[i];
        // for(int j=1;j<=K;j++)
        //     if(i^j) mmul(res,immul(imdel(x,j),qpow(imdel(i,j),mod-2)));
        // madd(ret,res);
    }
    return ret;
}
inline int func2(int x){
    int ret=0;
    pre[0]=suf[K+1]=1;
    for(int i=1;i<=K;i++)      pre[i]=immul(pre[i-1],imdel(x,i));
    for(int i=K;i;i--)  suf[i]=immul(suf[i+1],imdel(x,i));
    for(int i=1;i<=K;i++){
        // int p=1ll*f2[i]*pre[i-1]%mod*suf[i+1]%mod,q=1ll*inv[i-1]*inv[K-i]%mod,res=immul(p,q);
        int res=1ll*f2[i]*pre[i-1]%mod*suf[i+1]%mod*invv[i]%mod;
        if((K-i)&1) res=mod-res;
        madd(ret,res);
        // int res=f2[i];
        // for(int j=1;j<=K;j++)
        //     if(i^j) mmul(res,immul(imdel(x,j),qpow(imdel(i,j),mod-2)));
        // madd(ret,res);
    }
    return ret;
}
inline int calc(ll x,ll len){
    x%=mod;
    for(int i=1;i<=K;i++)
        f1[i]=imadd(f1[i-1],qpow(i,k));
    mems(f2,0);
    for(int i=1-len;i<=K;i++){
        int fi=func1(i);
        if(i>0) madd(f2[i],fi);
        if(i+len<=K) mdel(f2[i+len],fi);
        // f2[i]=imadd(f2[i-1],imdel(func1(i),func1(i-len)));
        // if(i-len<0) printf("f1(%d) = %d\n",i-len,func1(i-len));
    }
    for(int i=1;i<=K;i++) madd(f2[i],f2[i-1]);
    return func2(x);
}
void solve(){
    scanf("%lld%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%lld",&a[i]);
    sort(a+1,a+m+1);
    a[0]=0;a[m+1]=n+1;
    ll kk=0;int ans=0;
    k=0;
    for(int i=1;i<=m+1;i++){
        // a[i-1]+1,a[i]-1
        ll l=a[i-1]+1,r=a[i]-1;
        l-=kk;r-=kk;
        if(l>r) continue;
        k+=l;kk+=r+1;
    }
    K=k+2;init();
    for(int i=1;i<=m+1;i++){
        ll l=a[i-1]+1,r=a[i]-1;
        if(l>r) continue;
        for(int j=i;j<=m+1;j++){
            ll L=a[j-1]+1,R=a[j]-1;
            if(L>R) continue;
            madd(ans,imdel(calc(R,l),calc(L-1,l)));
        }
        for(int j=i-1;j<=m+1;j++)   a[j]-=r+1;
    }
    printf("%d\n",ans);
}
int main(){int t;scanf("%d",&t);while(t--)solve();}