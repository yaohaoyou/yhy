#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define db __float128
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=60,maxm=1e4+10,mod=998244353;
int n,m;
db f[maxn];
db C[maxm][maxn];
db ans[maxn];
void init(){
    const int N=1e4;
    for(int i=0;i<=N;i++){C[i][0]=1;if(i<=50)C[i][i]=1;for(int j=1;j<i&&j<=50;j++)C[i][j]=C[i-1][j-1]+C[i-1][j];}
}
int main(){
    init();
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n&&i*j<=m;j++)   f[j]+=1.0*C[n][j]/C[m][n]*C[m-j*(i-1)][n];
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if((j-i)&1) ans[i]-=C[j][i]*f[j];
            else ans[i]+=C[j][i]*f[j];
        }
    }
    for(int i=n;i;i--)   ans[i]+=ans[i+1];
    reverse(ans+1,ans+n+1);
    for(int i=1;i<=n;i++)   ans[i]+=ans[i-1];
    for(int i=1;i<=n;i++)   printf("%.10lf ",(double)ans[i]);
}