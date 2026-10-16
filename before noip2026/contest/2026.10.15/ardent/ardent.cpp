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
const int maxn=6010;
bool mem1;
ll n,s,x;
int a[maxn];
int f[2][maxn][maxn],g[maxn][maxn];
bool check(ll lim){
    for(int i=0;i<=n+n;i++)for(int j=0;j<=n;j++)f[0][i][j]=f[1][i][j]=0;
    f[0][0][0]=true;
    // printf("%lld\n",lim);
    for(int i=0;i<=60;i++){
        for(int j=n;~j;j--){
            for(int k=0;k<=n;k++)if(f[i&1][j][k]){
                bool o=(lim>>i)&1,p=(x>>i)&1;
                if(!o){
                    for(int l=p;l<=n;l+=2)f[(i+1)&1][j+l][max(k,l)]=true;
                }
                else{
                    for(int l=p;l<=n;l+=2)f[(i+1)&1][j+l][max(k-int(n)+l,0)]=true;
                }
                f[i&1][j][k]=false;
            }
        }
        // for(int j=0;j<=n+n;j++)for(int k=0;k<=n;k++)f[i&1][j][k]=0;
        for(int j=(s>>i)&1;j<=n+n;j+=2)for(int k=0;k<=n;k++)if(f[(i+1)&1][j][k])g[j>>1][k]=true,f[(i+1)&1][j][k]=0;
        for(int j=0;j<=n+n;j++)for(int k=0;k<=n;k++)f[(i+1)&1][j][k]=g[j][k],g[j][k]=0;
        // for(int j=0;j<=n+n;j++)for(int k=0;k<=n;k++)if(f[j][k])printf("%d %d %d\n",i,j,k);
    }
    return f[1][0][0];
}
bool mem2;
void matt(int _cases){
    scanf("%lld%lld%lld",&n,&s,&x);n=min(n,s);
    // for(int i=0;i<=s;i++)printf("%d ",check(i));puts("");
    // printf("! %d\n",check(5));
    ll l=0,r=s,ans=-1;
    while(l<=r){
        ll mid=(l+r)>>1;
        if(check(mid))  ans=mid,r=mid-1;
        else    l=mid+1;
    }
    printf("%lld\n",ans);
}
int main(){freopen("ardent.in","r",stdin);freopen("ardent.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}