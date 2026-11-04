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
const int maxn=100,maxm=100,maxd=2e6+10;
int n,m;
int b[maxn];
ll P,a[maxn],N;
ll fac[maxn],f[maxd];
bool vis[maxd];
inline ll calc(){
    ll res=0;
    for(int i=1;i<=n;i++)res+=(1ll<<i-1)*fac[i-1]*b[i];
    while(res>=N)res=res%N+res/N;
    return res;
}
inline ll calc(ll x){
    assert(x>0&&x<N);
    ll res=0;
    for(int i=1;i<=n;i++){
        res+=x%(i+i);
        x=x/(i+i);
    }
    return res;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    N=(1ll<<n)*fac[n];
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    P=calc();
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++)scanf("%d",&b[j]);
        a[i]=calc();
    }
    ll d=N-1;for(int i=1;i<=m;i++)d=__gcd(d,a[i]);
    if(d>=maxd){
        ll ans=1e18;
        for(int k=0;P+k*d<N;k++)    gmn(ans,calc(P+k*d));
        for(int k=-1;P+k*d>0;k--)   gmn(ans,calc(P+k*d));
        printf("%lld\n",ans);
    }
    else{
        assert(d<maxd);
        mems(f,0x3f);
        for(int i=1;i<=n;i++)   f[(1ll<<i-1)*fac[i-1]%d]=1;
        for(int _=1;_<=n;_++){
            int x=(1ll<<_-1)*fac[_-1]%d;
            for(int p=0,lim=__gcd((ll)x,d);p<lim;p++){
                int u=p;
                for(int j=0;j<=2;(u+=x)%=d,j+=(u==p))   gmn(f[(u+x)%d],f[u]+1);
            }
        }
        printf("%lld\n",f[P%d]);
    }
}