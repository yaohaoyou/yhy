#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
bool mem1;
const int maxn=1e5+10;
int n;ll m;
pii a[maxn];
bool mem2;
void MATT(){
    scanf("%d%lld",&n,&m);
    pii mn=pii(1e9+10,1e9);int p=0;
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        if(mn.fi+mn.se>a[i].fi+a[i].se) mn=a[i],p=i;
        else if(mn.fi+mn.se==a[i].fi+a[i].se&&mn.fi>a[i].fi)    mn=a[i],p=i;
    }
    ll sum=0,ans=0,cnt=0;
    for(int i=0;i<=n;i++){
        if(i==p)    continue;
        cnt+=bool(i);
        sum+=a[i].fi;
        ll x=(m-sum)/(mn.fi+mn.se)*2,y=(m-sum)%(mn.fi+mn.se);
        if(y>=mn.fi)  ans=max(ans,x+cnt+1);
        else ans=max(ans,x+cnt);
    }
    printf("%lld\n",ans);
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=1;while(T--)MATT();
}