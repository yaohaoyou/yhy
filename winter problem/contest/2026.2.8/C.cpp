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
const int maxn=1e5+10,maxv=(1<<18)+10;
int n,c;
int a[maxn];
ll s[maxn],f[maxn],buc[maxv];
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
// inline ll w(int l,int r){return l==r?0:s[r-1]-s[l];}
void matt(int _cases){
    mems(buc,0x3f);
    scanf("%d%d",&n,&c);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    bool flag=*max_element(a+1,a+n+1)<(1<<9);
    a[n+1]=0;
    f[0]=0;buc[0]=0;
    for(int i=1;i<=n+1;i++){
        f[i]=1e18;
        if(i<=3000){
            for(int j=0;j<i;j++)gmn(f[i],f[j]+(a[i]^a[j]));
        }
        else if(flag){
            for(int j=(1<<9);~j;j--)    gmn(f[i],buc[j]+(a[i]^j));
        }
        else{
            for(int j=max(0,a[i]-1000);j<=a[i];j++)    gmn(f[i],buc[j]+(a[i]^j));
            for(int j=a[i];j<maxv&&j<=a[i]+1000;j++)    gmn(f[i],buc[j]+(a[i]^j));
            for(int j=0;j<i&&j<3000;j++)gmn(f[i],f[j]+(a[i]^a[j]));
            for(int j=max(3000,i-3000);j<i;j++)gmn(f[i],f[j]+(a[i]^a[j]));
        }
        f[i]-=c;
        gmn(buc[a[i]],f[i]);
    }
    printf("%lld\n",f[n+1]+1ll*c*(n+1));
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}