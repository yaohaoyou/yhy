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
const int maxn=5010;
bool mem1;
int n;
int a[maxn],L[maxn],R[maxn];
int f[maxn],g[maxn],h[maxn];
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        L[i]=R[i]=0;
        for(int j=1;j<i;j++)L[i]+=a[j]<a[i];
        for(int j=i+1;j<=n;j++)R[i]+=a[j]>a[i];
    }
    fill(h+1,h+n+1,0);
    int ans=n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++)    g[j]=g[j-1]+(a[j]<a[i]);
        for(int j=1;j<i-1;j++)  h[j]+=(a[i-1]>a[j]);
        f[i]=L[i]-1;
        for(int j=1;j<i;j++)if(a[j]>a[i]){
            gmn(f[i],f[j]+g[i-1]-g[j]+h[j]-1);
        }
        gmn(ans,f[i]+R[i]+1);
    }
    gmx(ans,0);
    printf("%d\n",ans);
}
int main(){freopen("d.in","r",stdin);freopen("d.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}