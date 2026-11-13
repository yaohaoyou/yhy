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
const int maxn=1e5+10;
int n;
ll a[maxn],b[maxn];
bool mem2;
int main(){
    freopen("lead.in","r",stdin);freopen("lead.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    if(a[1]<*max_element(a+2,a+n+1))    return puts("0"),0;
    sort(a+2,a+n+1,greater<ll>());
    ll tag=0,ans=0,s=a[2];
    int i=2;while(i<=n&&a[i]==a[2])i++;
    for(;i<=n;i++){
        int j=i;while(j<n&&a[j+1]==a[i])j++;
        ll k=1ll*(1+__lg(i-2))*(a[2]-a[j]-tag);
        s+=__lg(i-2)*(a[2]-a[j]-tag);
        if(s>a[1]){
            s-=__lg(i-2)*(a[2]-a[j]-tag);
            k=(a[1]-s)/__lg(i-2);
            s+=k*__lg(i-2);
            ans+=k*(__lg(i-2)+1);
            ans+=a[1]-s;
            // ans+=(a[1]-s)*(__lg(i-2)+1);
            printf("%lld\n",ans);
            return 0;
        }
        tag=a[2]-a[j];
        ans+=k;
        // printf("k = %d %d %d\n",k,tag,s);
        i=j;
    }
    // printf("ans = %d\n",ans);
    ll k=(a[1]-s)/__lg(n-1);
    s+=k*__lg(n-1);
    ans+=k*(__lg(n-1)+1);
    ans+=a[1]-s;
    printf("%lld\n",ans);
}