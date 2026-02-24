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
const int maxn=2e5+10;
int n,k;
int a[maxn];
ll s[maxn];
inline ll calc(int l,int r,int x){return s[n]-(s[r]-s[x-1])-s[l]+1ll*(r-x+1+l)*a[x];}
void matt(int _cases){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    ll ans=0;
    for(int i=1;i<=n;i++){
        int l=1,r=min(i-1,n-i),p=0;
        // for(int j=0;j<=r;j++)   printf("%d ",calc(max(1,i-j*k),i+j,i));puts("");
        while(l<=r){
            int mid=(l+r)>>1;
            if(calc(min(i-1ll,1ll*mid*k),i+mid,i)>=calc(min(i-1ll,1ll*(mid-1)*k),i+mid-1,i)) p=mid,l=mid+1;
            else r=mid-1;
        }
        // printf("p = %d\n",p);
        ans=max(ans,calc(min(i-1ll,1ll*p*k),i+p,i));
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}