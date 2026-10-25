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
const int maxn=2e6+10,mod=998244353;
struct mint{
    int v;
    mint(int _v=0){v=_v;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mint operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mint operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mint operator*(int y){return 1ull*v*y%mod;}
};
int l,r;
mint f[maxn],s[maxn];
bool mem2;
int main(){
    freopen("b.in","r",stdin);freopen("b.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&l,&r);
    if(l==1)    return puts("1"),0;
    f[l]=1;s[l]=1;
    for(int i=l+1;i<=r;i++){
        f[i]+=s[i-1]-s[i-l-1];
        s[i]=s[i-1]+f[i];
    }
    mint ans=0;
    for(int i=l;i<=r;i++){
        for(int j=i+i;j<=r;j+=i)f[j]-=f[i];
        ans+=f[i];
    }
    printf("%d\n",ans);
}