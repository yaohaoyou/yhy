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
const int maxn=5e5+10;
bool mem1;
int n;
int a[maxn];
ll s[maxn];
struct frac{
    int p,q;
    frac(int _p=0,int _q=0){p=_p;q=_q;int g=__gcd(p,q);if(g)p/=g,q/=g;}
    bool operator<(frac y)const{return 1ll*p*y.q<1ll*q*y.p;}
};
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    frac ans(0,1);
    for(int i=2;i<=n;i++){
        int l=i,r=n;
        while(l<=r){
            int mid=(l+r)>>1;
            if(s[mid]-s[i-1]+a[1]<1ll*a[i]*(mid-i+2))  ans=max(ans,frac(mid-i+1,mid-i+2)),l=mid+1;
            else    r=mid-1;
        }
    }
    printf("%d/%d ",ans.p,ans.q);
    ans=frac(1e9,1);
    for(int i=1;i<n;i++)if(a[i]==a[i+1])ans=frac(0,1);
    for(int i=1;i<n;i++){
        int l=1,r=i;
        while(l<=r){
            int mid=(l+r)>>1;
            if(s[i]-s[mid-1]+a[n]>=1ll*a[i]*(i-mid+2))  ans=min(ans,frac(1,i-mid+2)),r=mid-1;
            else    l=mid+1;
        }
    }
    printf("%d/%d\n",ans.p,ans.q);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}