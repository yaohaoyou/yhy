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
const int maxn=2e6+10;
int n;
int a[maxn];
int vis[maxn];
void dfs(int x,int y,int z){
    if(z<0) return;
    if(x>n){
        if(!(y&1))vis[z]|=3;
        vis[z]|=1;
        return;
    }
    for(int i=0;i<=10;i++){
        if(x<=(n+1)/2)  dfs(x+1,y+i,z+(1<<i));
        else dfs(x+1,y+i,z-(1<<i));
    }
}
void matt(int _cases){
    mems(vis,0);
    scanf("%d",&n);
    dfs(1,0,0);
    for(int i=1;i<=n*1024;i++)if(!vis[i])printf("%d ",i);puts("");
    for(int i=1;i<=n*1024;i++)if(vis[i]==1)printf("%d ",i);puts("");
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}