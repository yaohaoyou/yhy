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
const int maxn=1e7+10,mod=998244353;
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
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
bool mem1;
int n,m,k;
mit fac[maxn<<1],inv[maxn<<1];
void init(){
    const int N=2e7;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=fac[i-1]*i;
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
inline mit C(int x,int y){return x<y||x<0||y<0?mit(0):fac[x]*inv[y]*inv[x-y];}
bool mem2;
void matt(int _cases){
    scanf("%d%d%d",&n,&m,&k);
    if(k>m) return printf("%d\n",m),void();
    mit ans=0;
    for(int i=0;i<=n&&i+k<=m;i++){
        ans+=(C(i+i+k-1,i)-C(i+i+k-1,i-1))*C(n+m-i-i-k,n-i)*(i+k);
        // ans+=(C(i+i+k-1,i)-C(i+i+k-1,i-1))*C(n+m-i-i-k,n-i);
    }
    if(n+k>m)   ans+=(C(m+n,m)-C(m+n,n+k))*m;
    ans*=qpow(fac[n+m]*inv[n]*inv[m],mod-2);
    printf("%d\n",ans);
}
int main(){init();debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}