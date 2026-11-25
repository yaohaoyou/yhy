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
const int maxn=5010,mod=998244353;
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
mit f[maxn],fac[maxn],inv[maxn];
void init(){
    n=5005;
    fac[0]=1;for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i;
    inv[n]=qpow(fac[n],mod-2);for(int i=n-1;~i;i--)inv[i]=inv[i+1]*(i+1);
}
inline mit C(int x,int y){return x<0||y<0||x<y?mit(0):fac[x]*inv[y]*inv[x-y];}
inline mit A(int x,int y){return x<0||y<0||x<y?mit(0):fac[x]*inv[x-y];}
bool mem2;
int main(){
    init();
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1,greater<int>());a[++n]=0;
    if(a[1]<a[2]*2) return puts("0"),0;
    f[1]=f[2]=1;
    for(int i=3;i<=n;i++){
        int A=0;
        f[i]+=fac[i-2];
        for(int j=i-1;j>1;j--)if(a[i]*2<=a[j]){
            while(i-1-A>j&&a[i-1-A]*2<=a[j])    A++;
            int x=j-2,B=i-j-1-A;
            mit res=C(A+B+x+1,B+x+1);
            // for(int k=0;k<=A;k++)   res+=C(A+B+x-k,B+x);
            res*=fac[A]*fac[B+x]*inv[x];
            f[i]+=f[j]*res;
        }
    }
    printf("%d\n",f[n]);
}