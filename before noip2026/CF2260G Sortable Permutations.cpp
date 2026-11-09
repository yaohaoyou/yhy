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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=4e5+10,mod=998244353;
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
int n;
int g[maxn];
mit f[maxn],fac[maxn],inv[maxn];
bool ntp[maxn];
int mu[maxn],d[maxn];
void init(){
    n=2e5;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
    vector<int> p;
    for(int i=2;i<=n;i++){
        if(!ntp[i]) mu[i]=-1,d[i]=i,p.eb(i);
        for(int j:p){
            if(1ll*i*j>n)   break;
            ntp[i*j]=true;d[i*j]=j;
            if(i%j==0)  break;
            mu[i*j]=-mu[i];
        }
    }
}
inline mit C(int x,int y){return fac[x]*inv[y]*inv[x-y];}
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        vector<int> v;
        {int x=i;while(x^1)v.eb(d[x]),x/=d[x];}
        {int x=i+1;while(x^1)v.eb(d[x]),x/=d[x];}
        sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
        for(int s=0;s<(1<<v.size());s++){
            ll x=1;
            for(int j=0;j<v.size();j++)if(s&(1<<j))x*=v[j];
            if(x>n*2) continue;
            if(i%x&&(i+1)%x)    g[x]++;
        }
    }
    mit ans=0;
    for(int i=3;i<=n;i+=2)if(mu[i]){
        mit w=fac[n]*inv[n-n/i]*qpow(2,g[i]);
        w-=fac[n]*inv[n-n/(2*i)]*qpow(2,g[i*2]-((n-1)/i+1)/2*2)*qpow(3,((n-1)/i+1)/2);
        if(mu[i]==-1)    ans+=w;
        else    ans-=w;
    }
    ans+=fac[n]*inv[n-n/2];  // i=2
    printf("%d\n",ans);
}