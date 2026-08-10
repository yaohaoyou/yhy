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
const int maxn=18,maxm=(1<<16)+10;
const ll INF=1e18;
int n,m;ll k;
int a[maxm],b[maxm],c[maxm];
ll dp[maxm][2];
inline void getmn(ll &x,ll y){(x>y)&&(x=y);}
void dfs(int u,int lim){
    dp[u][0]=dp[u][1]=INF;
    if(u>=m)    dp[u][b[u-m+1]>=lim]=0;
    else{
        int ls=u<<1,rs=u<<1|1;
        dfs(ls,lim);dfs(rs,lim);
        getmn(dp[u][0],dp[ls][0]+dp[rs][0]);
        getmn(dp[u][1],dp[ls][1]+dp[rs][1]);
        getmn(dp[u][1],dp[ls][1]+dp[rs][0]+a[u]);
    }
}
inline int calc(int rt,int x){dfs(rt,x);return dp[1][1];}
void slv(int u){
    if(u>=m){printf("%d ",b[u-m+1]);return;}
    int l=1,r=m,p=0,sum=0;
    while(l<=r){
        int mid=(l+r)>>1;
        int x=calc(u,mid);
        if(x<=k)    sum=x,p=mid,l=mid+1;
        else    r=mid-1;
    }
    printf("%d ",p);k-=sum;p=c[p]+m-1;
    vector<int> lst;lst.clear();
    lst.eb(p);
    while(p^u)  p>>=1,lst.eb(p);
    for(int i=1;i<lst.size();i++){
        if(lst[i-1]==(lst[i]<<1))   slv(lst[i]<<1|1);
        else    slv(lst[i]<<1);
    }
    vector<int>().swap(lst);
}
void matt(){
    scanf("%d%lld",&n,&k);m=1<<n;
    for(int i=1;i<m;i++)    scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]),c[b[i]]=i;
    slv(1);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}