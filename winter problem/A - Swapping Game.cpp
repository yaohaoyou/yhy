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
const int maxn=3e4+10,maxl=15;
int n,l;
int c[maxn],b[maxl],cc[maxn];
int a[maxn][maxl];
int dp[maxn];
int v[maxl][maxl][maxn];
int len[maxl][maxl];
int main(){
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;i++){
        scanf("%d",&c[i]);
        for(int j=1;j<=l;j++)   scanf("%d",&a[i][j]);
    }
    iota(a[0]+1,a[0]+l+1,1);
    for(int i=0;i<=n;i++){
        for(int j=1;j<=l;j++){
            for(int k=j+1;k<=l;k++) v[a[i][j]][a[i][k]][++len[a[i][j]][a[i][k]]]=i;
        }
    }
    mems(dp,-0x3f);dp[0]=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=l;j++)   b[a[i][j]]=j;
        for(int j=i-1,k=0;j>=0&&k<=l*(l-1);j--,k++){
            if(dp[i]>=dp[j]+c[i])   continue;
            int cc=i-j;
            for(int x=1;x<=l;x++){
                for(int y=x+1;y<=l;y++)if(b[a[j][x]]>b[a[j][y]]){cc--;if(cc<0)break;}
                if(cc<0)break;
            }
            if(cc>=0)    dp[i]=dp[j]+c[i];
        }
    }
    printf("%d\n",*max_element(dp,dp+n+1));
}