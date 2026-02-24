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
const int maxn=5e6+10;
int n,m;
int a[maxn],t[maxn];
int p[maxn],k[maxn],b[maxn],w[maxn];
int ans[maxn];
ll sum[maxn];
namespace Read{
    int seed,base;
    inline int rnd(){int ret=seed;seed=(1ll*seed*base+233)%1000000007;return ret;}
    void read(){
        for(int i=1;i<=m;i++){
            seed=b[i];base=w[i];
            for(int j=p[i-1]+1;j<=p[i];j++) t[j]=rnd()%2,a[j]=(rnd()%k[i])+1;
        }
    }
}
const int mod=1e9+7;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d%d%d%d",&p[i],&k[i],&b[i],&w[i]);
    Read::read();
    for(int i=1;i<=n;i++)   sum[t[i]]+=a[i];
    if(sum[1]>sum[0]){swap(sum[0],sum[1]);for(int i=1;i<=n;i++)t[i]^=1;}
    int p=1;
    if(!t[1]){
        a[1]--;ans[1]++;
        for(int i=1;i<=n;i++)
            if(t[i]==1){p=i;break;}
    }
    ll cnt=0;
    while(sum[1]||cnt){
        if(t[p]==1){ans[p]+=a[p];cnt+=a[p];sum[1]-=a[p];a[p]=0;}
        else{
            int d=min(cnt,(ll)a[p]);
            a[p]-=d;cnt-=d;ans[p]+=d;
        }
        p=p%n+1;
    }
    int out=1;
    for(int i=1;i<=n;i++)
        out=1ll*out*(((ans[i]^(1ll*i*i))+1)%mod)%mod;
    printf("%d\n",out);
}