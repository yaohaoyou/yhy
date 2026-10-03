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
const int maxn=1e3+10;
int n,m;
int a[maxn],p[maxn];
vector<int> son[maxn];
vector<pii> ans;
bool vis[maxn];
bool dfs(int u){
    for(int t:son[u])if(!vis[t]){
        vis[t]=true;
        if(!p[t]||dfs(p[t]))   return p[t]=u,p[u]=t;
    }
    return false;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1,greater<int>());
    if(a[1]*2>=m)   return puts("-1"),0;
    for(int i=1;i<=n;i++)if(a[i]*3ll>m){
        for(int j=i+1;j<=n;j++)
            if(a[i]%a[j]==0&&a[i]*2ll+a[j]<=m)    son[i].eb(j);
        mems(vis,0);
        if(!dfs(i)) return puts("-1"),0;
    }
    for(int i=1;i<=n;i++){
        if(a[i]*3>m){
            ans.eb(a[i]*2+a[p[i]],a[i]+a[p[i]]);
            p[p[i]]=-1;
        }
        else if(!p[i]){
            ans.eb(a[i]*2,a[i]*3);
        }
    }
    printf("%d\n",ans.size());
    for(auto [i,j]:ans) printf("%d %d\n",i,j);
}