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
const int maxn=8000+10;
int n,m,k,ans;
int v[maxn],p[maxn];
int a[maxn],b[maxn];
int f[maxn],g[maxn];
inline int level(int s1,int s2){double pp=100.0*s2/s1;return lower_bound(p+1,p+k+1,pp)-p;}
int main(){
    freopen("exam.in","r",stdin);freopen("exam.out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=k;i++)   scanf("%d",&p[i]);
    for(int i=1;i<=k;i++)   scanf("%d",&v[i]);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    mems(f,-0x3f);mems(g,-0x3f);f[0]=g[0]=0;
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=m;j++)f[j]=max(f[j],f[j-a[i]]+b[i]);
    for(int i=1;i<=m;i++)
        for(int j=i;j<=m;j++)
            if(f[i]>0)    g[j]=max(g[j],g[j-i]+v[level(i,f[i])]*i);
    int ans=0;
    for(int i=1;i<=m;i++)   ans=max(ans,g[i]);
    printf("%d\n",ans);
}