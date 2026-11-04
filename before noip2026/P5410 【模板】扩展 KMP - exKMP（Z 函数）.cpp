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
const int maxn=2e7+10;
bool mem1;
int n,m;
char a[maxn],b[maxn];
int nx[maxn],ex[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%s%s",b+1,a+1);n=strlen(a+1);m=strlen(b+1);
    int p,r=0;
    for(int i=2;i<=n;i++){
        if(i<=r)    nx[i]=min(r-i+1,nx[i-p+1]);
        else    nx[i]=0;
        while(i+nx[i]<=n&&a[i+nx[i]]==a[1+nx[i]])nx[i]++;
        if(i+nx[i]-1>r) r=i+nx[i]-1,p=i;
    }
    r=0;
    for(int i=1;i<=m;i++){
        if(i<=r)    ex[i]=min(r-i+1,nx[i-p+1]);
        else    ex[i]=0;
        while(i+ex[i]<=m&&ex[i]<n&&b[i+ex[i]]==a[1+ex[i]])ex[i]++;
        if(i+ex[i]-1>r)  r=i+ex[i]-1,p=i;
    }
    nx[1]=n;
    ll ans=0;
    for(int i=1;i<=n;i++)ans^=1ll*i*(nx[i]+1);
    printf("%lld\n",ans);
    ans=0;
    for(int i=1;i<=m;i++)ans^=1ll*i*(ex[i]+1);
    printf("%lld\n",ans);
}