#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
int n;
int a[maxn];
bool vis[maxn];
mit fac[maxn],inv[maxn];
void init(){
    n=1e7;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
bool is_perm(){
    for(int i=1;i<=n;i++)vis[a[i]]=true;
    if(count(vis+1,vis+n+1,1)==1) exit(printf("%d\n",fac[n])&0);
    return !count(vis+1,vis+n+1,0);
}
bool check_no(){
    mems(vis,0);a[0]=a[1];
    for(int i=1;i<=n;i++)if(a[i]!=a[i-1]){
        int j=i;while(a[(j-1)%n+1]==a[i])j++;
        if(vis[a[i]])return true;
        vis[a[i]]=true;
        i=j-1;
    }
    for(int i=1;i<=n;i++)if(a[i]==a[i%n+1]&&a[i]==a[(i+1)%n+1])return false;
    return true;
}
bool mem2;
int main(){
    // freopen("fx.in","r",stdin);freopen("fx.out","w",stdout);
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(is_perm())  return puts("1"),0;
    if(check_no())   return puts("0"),0;
    mems(vis,0);for(int i=1;i<=n;i++)vis[a[i]]=true;
    int r=count(vis+1,vis+n+1,0),k=count(vis+1,vis+n+1,1);
    mit ans=fac[n]*inv[k-1];
    if(n>=r*3)   ans-=mit(n)*k*fac[n-2*r-1]*inv[n-3*r];
    if(r==2&&n>=6&&!(n&1))  ans*=(mod+1)>>1;
    printf("%d\n",ans);
}