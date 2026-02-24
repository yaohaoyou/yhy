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
const int maxn=10010;
int n,m,K;
int a[maxn],s[maxn];
int dp[maxn][maxn];  // dp[i][j] 表示前 j 个位置填了 i 个 -1 的最小的最大非负区间和
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
inline int sum(int l,int r){
    int k=(r-l+1)/2;
    if(!(l&1)&&!(r&1))  k++;
    return s[r]-s[l-1]+k*K;
}
int main(){
    scanf("%d%d",&n,&K);
    if(n==1)    return puts("0"),0;
    m=n+n-1;swap(n,m);
    for(int i=1;i<=n;i+=2)  scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+a[i];
    mems(dp,0x3f);
    dp[0][0]=0;
    for(int i=1;i<=n;i++){
        if(!(i&1)){
            for(int j=1;j<=i/2;j++) gmn(dp[j][i],dp[j-1][i-1]);
        }
        if(a[i]<0){
            for(int j=0;j<=i/2;j++) gmn(dp[j][i],dp[j][i-1]);
            continue;
        }
        int hd=i;
        while(hd&&a[hd]>=0)hd--;
        if(!hd) gmn(dp[0][i],sum(1,i));
        for(int j=0,k=hd+1+(!hd);j<=i/2;j++){
            gmn(dp[j][i],max(dp[j][hd-1],sum(hd+1,i)));
            if(j){
                while(dp[j-1][k-1]<sum(k+1,i))   k+=2;
                gmn(dp[j][i],dp[j-1][k-1]);
                if(k-2>=hd) gmn(dp[j][i],sum(k-1,i));
            }
            // for(int k=i-1;~k;k--){
            //     if(!k){if(!j)gmn(dp[j][i],sum(k+1,i));break;}
            //     if(k&1){
            //         if(a[k]<0){gmn(dp[j][i],max(dp[j][k-1],sum(k+1,i)));break;}
            //     }
            //     else if(j)  gmn(dp[j][i],max(dp[j-1][k-1],sum(k+1,i)));
            // }
        }
    }
    int sum=max(0,a[1])+max(0,a[n])+s[n-1]-s[1];
    int ans=0;
    for(int i=0;i<m;i++)    gmx(ans,sum+(m-1-i)*K-i-dp[i][n]);
    printf("%d\n",ans);
}