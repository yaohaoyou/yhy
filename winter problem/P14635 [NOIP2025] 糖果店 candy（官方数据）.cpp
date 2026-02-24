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
const int maxn=1e5+10;
int n;ll m;
pii a[maxn];
int main(){
    scanf("%d%lld",&n,&m);
    int mn=2e9,p=0;
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        if(mn>a[i].fi+a[i].se) mn=a[i].fi+a[i].se,p=i;
        else if(mn==a[i].fi+a[i].se&&a[p].fi>a[i].fi)    p=i;
    }
    ll now=0,ans=m/mn;
    if(ans*mn+a[p].fi<=m) ans=ans*2+1;
    else    ans<<=1;
    int c=0;
    for(int i=1;i<=n;i++){
        if(i==p)    continue;
        now+=a[i].fi;
        c++;
        if(now>m)   continue;
        ll t=(m-now)/mn,res=t*2+c;
        if(t*mn+now+a[p].fi<=m)   res++;
        ans=max(ans,res);
    }
    printf("%lld\n",ans);
}