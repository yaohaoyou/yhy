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
const int maxn=110;
int n,m;
int a[maxn];
vector<int> v[maxn];
int b[maxn];
ll ans=1e18;
void dfs(int x,ll s){
    if(x>n){
        for(int i=1;i<=m;i++)
            if(b[i]>0)  return;
        ans=min(ans,s);
        return;
    }
    dfs(x+1,s);
    for(int i:v[x]) b[i]--;
    dfs(x+1,s+a[x]);
    for(int i:v[x]) b[i]--;
    dfs(x+1,s+a[x]+a[x]);
    for(int i:v[x]) b[i]+=2;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++){
        int c;scanf("%d",&c);
        while(c--){int x;scanf("%d",&x);v[x].eb(i);}
    }
    for(int i=1;i<=m;i++)   b[i]=2;
    dfs(1,0);
    printf("%lld\n",ans);
}