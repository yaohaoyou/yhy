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
const int maxn=310,maxv=3010;
int n,m;
int a[maxv],s[maxv],dp[maxn][maxv],p[maxn][maxv];  // dp[i][j] 表示前 j 个村庄选 i 个邮局的答案
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline int w(int l,int r){
    int mid=(l+r)>>1;
    return (mid-l)*a[mid]-(s[mid-1]-s[l-1])+(s[r]-s[mid])-(r-mid)*a[mid];
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),s[i]=s[i-1]+a[i];
    mems(dp,0x3f);dp[0][0]=0;
    for(int i=1;i<=m;i++){
        p[i][n+1]=n;
        for(int j=n;j;j--){
            for(int k=p[i-1][j];k<=min(p[i][j+1],j-1);k++){
                int co=dp[i-1][k]+w(k+1,j);
                if(dp[i][j]>co)dp[i][j]=co,p[i][j]=k;
            }
        }
    }
    printf("%d\n",dp[m][n]);
}