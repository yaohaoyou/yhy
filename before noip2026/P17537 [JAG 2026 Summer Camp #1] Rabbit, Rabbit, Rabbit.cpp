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
bool mem1;
const int maxn=3e5+10;
int n;
int a[maxn],b[maxn],c[maxn];
map<int,int> d;
int A[maxn],B[maxn];
queue<int> q[2];
ll solve(){
    while(!q[0].empty())q[0].pop();while(!q[1].empty())q[1].pop();
    d.clear();
    for(int i=1;i<=n;i++)   a[i]=A[i],b[i]=B[i];
    for(int i=n;i;i--)  a[i]-=a[1]-b[1];
    for(int i=2;i<=n;i++)q[b[i]&1].ep(i);
    int mx=0;
    for(int i=2;i<=n;i++){
        bool o=a[i]&1;
        if(q[o].empty())    return 1e18;
        c[i]=b[q[o].front()]-a[i];gmx(mx,abs(c[i]));q[o].pop();
    }
    for(int i=1;i<=n;i++){
        int R=(mx+c[i])/2,L=(mx-c[i])/2;
        d[R]++;
    }
    ll ans=0;
    int lst=0,now=0;
    for(auto [i,j]:d){
        ans+=1ll*(i-lst)*now*(n-now);
        now+=j;lst=i;
    }
    return ans;
}
bool mem2;
void matt(int _C){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    sort(a+1,a+n+1);sort(b+1,b+n+1);
    for(int i=1;i<=n;i++)   A[i]=a[i],B[i]=b[i];
    ll ans=solve();
    for(int i=2;i<=n;i++)if((B[i]&1)!=(B[1]&1)){
        rotate(B+1,B+i,B+i+1);break;
    }
    gmn(ans,solve());
    if(ans==1e18)   ans=-1;
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}