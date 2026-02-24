#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define plii pair<ll,pii>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e4+10;
int n,m,p;
int a[maxn],b[maxn];
ll f[maxn],g[maxn];
pii ans[maxn<<1];
void divide(int sx,int sy,int tx,int ty,int cnt,int stp){
    ans[cnt]=pii(sx,sy);ans[cnt+stp]=pii(tx,ty);
    if(stp<=1)   return;
    int k=stp>>1;
    for(int i=sy;i<=ty;i++) f[i]=g[i]=0;
    for(int i=sx;i<=tx;i++){
        for(int j=sy;j<=ty;j++){
            if(i-sx+j-sy>k) break;
            if(j^sy)    f[j]=max(f[j],f[j-1]);
            f[j]+=(a[i]+b[j])%p;
        }
    }
    k=stp-k;
    for(int i=tx;i>=sx;i--){
        for(int j=ty;j>=sy;j--){
            if(tx-i+ty-j>k) break;
            if(j^ty)    g[j]=max(g[j],g[j+1]);
            g[j]+=(a[i]+b[j])%p;
        }
    }
    k=stp>>1;
    plii res=plii(-1,pii(0,0));
    for(int i=sx;i<=tx;i++){
        int j=k+sy-i+sx;
        if(j<sy||j>ty)    continue;
        res=max(res,plii(f[j]+g[j]-(a[i]+b[j])%p,pii(i,j)));
    }
    divide(sx,sy,res.se.fi,res.se.se,cnt,k);
    divide(res.se.fi,res.se.se,tx,ty,cnt+k,stp-k);
}
int main(){
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    divide(1,1,n,m,1,n+m-2);
    mems(f,0);
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)f[j]=max(f[j],f[j-1])+(a[i]+b[j])%p;
    printf("%lld\n",f[m]);
    for(int i=2;i<=n+m-1;i++)   putchar(ans[i].fi==ans[i-1].fi?'S':'C');
}