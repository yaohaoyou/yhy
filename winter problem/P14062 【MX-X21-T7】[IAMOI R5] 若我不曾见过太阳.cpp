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
const int maxn=4e6+10;
int n;
int a[maxn],b[maxn],pre[maxn],nex[maxn],isp[maxn],isn[maxn];
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),b[a[i]]=i;
    for(int i=1;i<=n;i++)   pre[i]=i-1,nex[i]=i+1;
    pre[1]=n+2;nex[n+2]=1;nex[n]=n+3;pre[n+3]=n;

    for(int i=n;i;i--){
        int x=b[i],pr=pre[x],nx=nex[x];
        isp[x]=pr;isn[x]=nx;
        pre[nx]=pr;nex[pr]=nx;
    }
    // for(int i=1;i<=n;i++)   printf("%d %d\n",isp[i],isn[i]);
    for(int i=1;i<=n;i++)   pre[i]=i-1,nex[i]=i+1;
    nex[0]=1;pre[n+1]=n;
    int l=0,r=n+3,ans=n;
    for(int i=1;i<=n;i++){
        int x=b[i],pr=pre[x],nx=nex[x];
        pre[nx]=pr;nex[pr]=nx;
        if(x<=i&&l==x)  l=pre[x];
        if(nex[l]<=i)   l=nex[l];

        pre[x]=isp[x];nex[pre[x]]=x;nex[x]=isn[x];pre[nex[x]]=x;
        if(pre[r]<=n&&pre[r]>i)    r=pre[r];
        if(r<=i)    r=nex[r];
        ans=min(ans,r-l);
        // printf("%d %d\n",l,r);
    }
    printf("%d\n",n-ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}