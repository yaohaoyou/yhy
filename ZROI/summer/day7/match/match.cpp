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
const int maxn=20;
int n,k;
pii a[maxn];
bool f[maxn];
int p[maxn];
bool dfs(int x,int y){
    if(y>k) return false;
    if(x>n){
        if(y^k)return false;
        for(int i=1;i<=n;i++)if(p[i])printf("%d %d\n",i,p[i]);
        return true;
    }
    if(f[x])    return p[x]=0,dfs(x+1,y);
    for(int i=x+1;i<=n;i++)if(!f[i]){
        p[x]=i;f[i]=true;
        if(dfs(x+1,y+(a[x].fi==a[i].fi||a[x].se==a[i].se)))return true;
        f[i]=false;
    }
    return false;
}
void matt(int _cases){
    mems(f,0);mems(p,0);
    scanf("%d%d",&n,&k);n<<=1;
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    if(!dfs(1,0)) puts("-1");
}
int main(){freopen("match.in","r",stdin);freopen("match.out","w",stdout);;int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}