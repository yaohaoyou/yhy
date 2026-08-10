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
const int maxn=5010,maxm=1e5+10,inf=0x3f3f3f3f;
int n;
int a[maxn],b[maxn],c[maxn];
bool pr[maxn],sf[maxn];
int buc[maxm];
short dp[maxn][maxn],mx[maxn][maxn],mx2[maxn][maxn];
int mel[maxn][7],mel2[7][maxn];
inline void getmx(auto &x,auto y){(x<y)&&(x=y);}
void discrete(){
    for(int i=1;i<=n;i++)   buc[a[i]]++;
    for(int i=1;i<=n;i++)   pr[i]=buc[a[i]-1],sf[i]=buc[a[i]+1];
    memc(b,a);sort(b+1,b+n+1);
    int siz=unique(b+1,b+n+1)-b-1;
    for(int i=1;i<=n;i++)   c[i]=lower_bound(b+1,b+siz+1,a[i])-b;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    mems(dp,-0x3f);mems(mx,-0x3f);mems(mx2,-0x3f);mems(mel,-0x3f);mems(mel2,-0x3f);
    dp[0][0]=0;
    for(int i=1;i<=n;i++)for(int j=0;j<i;j++)  dp[i][j]=bool(j)+1;
    int ans=0;
    for(int j=0;j<n;j++){
        for(int i=j+1;i<=n;i++){
            getmx(dp[i][j],dp[j][0]+1);
            if(pr[i])getmx(dp[i][j],mx[j][c[i]-1]+1);
            if(sf[i])getmx(dp[i][j],mx[j][c[i]+1]+1);
            if(pr[i])getmx(dp[i][j],mx2[c[i]-1][j]+1);
            if(sf[i])getmx(dp[i][j],mx2[c[i]+1][j]+1);
            getmx(dp[i][j],mel[j][a[i]%7]+1);
            getmx(dp[i][j],mel2[a[i]%7][j]+1);
            // for(int k=0;k<j;k++)
                // if(abs(a[i]-a[k])==1||a[k]%7==a[i]%7)    getmx(dp[i][j],dp[j][k]+1);
            // for(int k=j+1;k<i;k++)
                // if(abs(a[i]-a[k])==1||a[k]%7==a[i]%7)    getmx(dp[i][j],dp[k][j]+1);
            ans=max(ans,(int)dp[i][j]);
            getmx(mx[i][c[j]],dp[i][j]);getmx(mx2[c[i]][j],dp[i][j]);
            getmx(mel[i][a[j]%7],dp[i][j]);getmx(mel2[a[i]%7][j],dp[i][j]);
            // printf("%d %d : %d\n",i,j,dp[i][j]);
        }
    }
    printf("%d\n",ans);
}