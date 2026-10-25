#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pll pair<ll,ll>
#define plli pair<pll,int>
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
ll ans,tag;
priority_queue<plli> q;
ll a[maxn],b[maxn];
bool check(){for(int i=1;i<=n;i++)if(a[i]^(b[i]+tag))return false;return true;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    ll ans=0;
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%lld",&b[i]);
    for(int i=1;i<=n;i++)q.ep(pll(b[i]-a[i],b[i]),i);
    int cnt=0;
    while(q.top().fi.fi+tag>0){
        cnt++;if(cnt>100000)return puts("-1"),0;
        int p=q.top().se;q.pop();
        // printf("%d %d %d\n",p,a[p],b[p]+tag);
        if(b[p]+tag<n-1)    return puts("-1"),0;
        b[p]-=n;q.ep(pll(b[p]-a[p],b[p]),p);
        tag++;ans++;
        // for(int i=1;i<=n;i++)   printf("%d ",b[i]+tag);puts("");
    }
    printf("%lld\n",ans);
}