#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n;
int a[maxn];
ll w[maxn];
priority_queue<pli,vector<pli>,greater<pli>> q;
bool mem2;
int main(){
    freopen("kfc.in","r",stdin);freopen("kfc.out","w",stdout);
    debug("%.2fMB",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    ll ans=accumulate(a+1,a+n+1,0ll);
    for(int i=1;i<=n;i++)   q.ep(3ll*a[i],i),w[i]=1;
    int T=n-2;
    while(T--){
        ans+=q.top().fi;int x=q.top().se;q.pop();
        w[x]++;
        q.ep(((w[x]+1)*(w[x]+1)-w[x]*w[x])*a[x],x);
    }
    printf("%lld\n",ans);
}