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
const int maxn=5010,inf=1e9;
int n;
int a[maxn],b[maxn],L[maxn],R[maxn],pr[maxn],nx[maxn];
// int f[maxn][maxn];  // f[i][l] 表示前 i 个数填入的最左边是 l 的答案
unordered_map<int,ll> f[2][maxn];  // f[i][l][r] 表示前 i 个填入的数填入了区间 [l,r] 的答案（知道 l 就可以推出唯一的 r，所以复杂度为 O(n^2)）
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
void matt(int _cases){
    for(int i=0;i<=n;i++)f[0][i].clear(),f[1][i].clear();
    scanf("%d",&n);
    fill(b,b+n,0);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(~a[i])   b[a[i]]=i;
    }
    for(int i=1;i<=n;i++)   pr[i]=(!~a[i-1])?i-1:pr[i-1];
    for(int i=n;i;i--)      nx[i]=(!~a[i+1])?i+1:nx[i+1];
    // for(int i=1;i<=n;i++)   printf("%d %d\n",pr[i],nx[i]);
    L[0]=b[0]?b[0]:inf;R[0]=b[0]?b[0]:-inf;
    for(int i=1;i<n;i++){
        L[i]=L[i-1];R[i]=R[i-1];
        if(b[i])    gmn(L[i],b[i]),gmx(R[i],b[i]);
    }
    int p=0;ll ans=0;
    while(p<n&&b[p]){
        ans+=L[p]*(n-R[p]+1);
        p++;
    }
    if(p==n)    return printf("%lld\n",ans),void();
    for(int i=1;i<=n;i++)if(!~a[i])f[p&1][i][i]=ans+min(L[p],i)*(n-max(R[p],i)+1);
    for(int i=p;i<n-1;i++){
        for(int j=1;j<=n;j++)   f[(i+1)&1][j].clear();
        for(int l=1;l<=n;l++){
            for(auto [r,t]:f[i&1][l]){
                // printf("%d %d %d : %d\n",i,l,r,t);
                if(b[i+1]){
                    gmx(f[(i+1)&1][l][r],t+min(L[i+1],l)*(n-max(R[i+1],r)+1));
                }
                else{
                    if(pr[l])   gmx(f[(i+1)&1][pr[l]][r],t+min(L[i+1],pr[l])*(n-max(R[i+1],r)+1));
                    if(nx[r])   gmx(f[(i+1)&1][l][nx[r]],t+min(L[i+1],l)*(n-max(R[i+1],nx[r])+1));
                }
            }
        }
    }
    ans=0;
    for(int i=1;i<=n;i++)for(auto [j,t]:f[(n-1)&1][i])gmx(ans,t);
    printf("%lld\n",ans);
    // int l=n,r=1;ll ans=0;
    // for(int i=0;i<n;i++){
    //     if(b[i]){
    //         gmn(l,b[i]);gmx(r,b[i]);
    //         ans+=l*(n-r+1);
    //         continue;
    //     }
    //     int p=0;int res=-1;
    //     for(int j=1;j<=n;j++){
    //         if(~a[j])   continue;
    //         if(min(l,j)*(n-max(r,j)+1)>res) res=min(l,j)*(n-max(r,j)+1),p=j;
    //     }
    //     a[b[i]=p]=i;
    //     gmn(l,b[i]);gmx(r,b[i]);
    //     ans+=l*(n-r+1);
    // }
    // printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}