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
const int maxn=520;
int n;
int ans[maxn][maxn];
bool vis[maxn][maxn];
inline int ask(int l,int r){if(ans[l][r])return ans[l][r];printf("? %d %d\n",l,r);fflush(stdout);int x;scanf("%d",&x);return ans[l][r]=x;}
void solve(int l,int r,int mx){
	if(vis[l][r])return;vis[l][r]=true;
    if(l>=r) return;
    int se=ask(l,r),w=se;
    if(se>mx)   swap(se,mx);
    for(int i=l;i<=se;i++)for(int j=mx;j<=r;j++)ans[i][j]=w;
    solve(se+1,r,mx);solve(l,mx-1,se);
}
int main(){
    scanf("%d",&n);
    int x=ask(1,n),mx;
    int l=x-1;while(l>0&&ask(l,x)!=x)   l--;
    if(l)   mx=l;
    int r=x+1;while(r<=n&&ask(x,r)!=x)  r++;
    if(r<=n)    mx=r;
    solve(1,n,mx);
    puts("!");fflush(stdout);
    int q;scanf("%d",&q);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        printf("%d\n",ans[l][r]);fflush(stdout);
    }
}