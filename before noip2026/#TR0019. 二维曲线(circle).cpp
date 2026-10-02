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
const int maxn=1e4+10;
const ll lim=2e18;
int n;
ll a[maxn],b[maxn],c[maxn],p[maxn],ans[maxn];
queue<int> q;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);int N=n;
    for(int i=1;i<=n;i++)   scanf("%lld%lld",&a[i],&b[i]),q.ep(i);
    while(q.size()>=2){
        int u=q.front(),v;q.pop();v=q.front();q.pop();
        p[u]=p[v]=++n;
        if(a[u]>a[v])   swap(u,v);
        ll x=a[v]-a[u],y=b[v]-b[u],xx=a[u]+a[v],yy=b[u]+b[v];
        if(x*x+y*y<=xx*xx+yy*yy){
            a[n]=a[v]-a[u];b[n]=b[v]-b[u];
            c[u]=-1;c[v]=1;
            q.ep(n);
        }
        else{
            a[n]=a[u]+a[v];b[n]=b[u]+b[v];
            c[u]=c[v]=1;
            q.ep(n);
        }
        // assert(a[n]*a[n]+b[n]*b[n]<=lim);
    }
    ans[n]=1;
    for(int i=n-1;i;i--)ans[i]=c[i]*ans[p[i]];
    for(int i=1;i<=N;i++)   printf("%lld ",ans[i]);
}