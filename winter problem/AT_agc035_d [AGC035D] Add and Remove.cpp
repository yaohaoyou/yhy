#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
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
const int maxn=20;
int n;
int a[maxn];
struct PII{size_t operator()(const pii &x)const{return ((ull)x.fi<<20)^x.se;}};
unordered_map<pii,ll,PII> f[maxn][maxn];
ll dp(int l,int r,int x,int y){
    if(f[l][r].find(pii(x,y))!=f[l][r].end())   return f[l][r][pii(x,y)];
    if(r<=l+1)    return 0;
    ll res=1e18;
    for(int i=l+1;i<r;i++)  gmn(res,dp(l,i,x,x+y)+dp(i,r,x+y,y)+1ll*a[i]*(x+y));
    // printf("[%d,%d] %d %d : %d\n",l,r,x,y,res);
    return f[l][r][pii(x,y)]=res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    printf("%lld\n",a[1]+a[n]+dp(1,n,1,1));
}