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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n,r;
pii a[maxn];
int col[maxn];
bool ans[maxn];
bool flag;
inline ll sqr(int x){return 1ll*x*x;}
inline bool chk(pii x,pii y){return abs(x.fi-y.fi)+abs(x.se-y.se)<=r;}
void dfs(int u){
    for(int t=1;t<=n;t++)if(t^u){
        if(!chk(a[u],a[t])) continue;
        if(!~col[t])col[t]=col[u]^1,dfs(t);
        else if(col[t]==col[u]) flag=true;
        if(flag)return;
    }
}
void dfs2(int u){
    ans[u]=true;
    for(int t=1;t<=n;t++)if(t^u){
        if(!chk(a[u],a[t])) continue;
        if(!ans[t])dfs2(t);
    }
}
int main(){
    freopen("eightfour.in","r",stdin);freopen("eightfour.out","w",stdout);
    scanf("%d%d",&n,&r);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    mems(col,-1);
    for(int i=1;i<=n;i++){
        if(!~col[i]){
            flag=col[i]=0;
            dfs(i);
            if(flag)    dfs2(i);
        }
    }
    for(int i=1;i<=n;i++)   printf("%d",ans[i]);
}