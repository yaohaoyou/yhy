#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
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
int n,m;
int a[maxn];
priority_queue<pii> q;
int pr[maxn],nx[maxn];
bool vis[maxn];
inline void era(int x){int pre=pr[x],nxt=nx[x];nx[pre]=nxt;pr[nxt]=pre;}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),q.ep(a[i],i),nx[i]=i+1,pr[i]=i-1;
    ll ans=0;
    while(m--){
        int x=q.top().se;q.pop();
        if(a[x]<=0)    break;
        // printf("%d %d %d\n",x,a[x],vis[x]);
        if(vis[x]){m++;continue;}
        ans+=a[x];
        a[x]=a[pr[x]]+a[nx[x]]-a[x];
        q.ep(a[x],x);
        vis[pr[x]]=vis[nx[x]]=true;
        era(pr[x]);
        era(nx[x]);
    }
    printf("%lld\n",ans);
}