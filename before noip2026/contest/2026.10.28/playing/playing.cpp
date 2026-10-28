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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1010,maxv=(1<<13)+10;
bool mem1;
int n;
int a[maxn];
bool dp[maxn][maxv];int p[maxn][maxv];
char ans[maxn];
inline int lb(int x){return x&-x;}
inline int hb(int x){if(!x)return 0;return 1<<__lg(x);}
bool chk(int x){if(!x)return 0;return (1<<__lg(x))==x;}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    if(!chk(accumulate(a+1,a+n+1,0)))return puts("no"),void();
    int sum=a[1];
    ans[1]='l';
    dp[1][sum]=1;
    for(int i=2;i<=n;i++){
        for(int j=1;j<=sum;j++)if(dp[i-1][j]){
            // printf("%d %d\n",i-1,j);
            int k=sum-j;
            if(j<k)  continue;
            if(a[i]<=lb(j)) dp[i][j+a[i]]=true,p[i][j+a[i]]=-j;
            if(chk(j)&&a[i]>j)  dp[i][a[i]]=true,p[i][a[i]]=-j;
            if(!k){
                if(a[i]>=hb(j)) dp[i][j+a[i]]=true,p[i][j+a[i]]=j;
                else dp[i][j]=true,p[i][j]=j;
            }
            else if(a[i]<=lb(k)){
                // printf("%d %d %d\n",k,a[i],chk(k+a[i]));
                if(chk(k+a[i])&&k+a[i]==hb(j))  dp[i][j+k+a[i]]=true,p[i][j+k+a[i]]=j;
                else dp[i][j]=true,p[i][j]=j;
                // dp[i][max(j,k+a[i])]=true,p[i][max(j,k+a[i])]=j;
            }
        }
        sum+=a[i];
    }
    if(!dp[n][sum])  puts("no");
    else{
        int x=sum;
        for(int i=n;i>1;i--){
            assert(dp[i][x]);
            if(p[i][x]>0)  ans[i]='r',x=p[i][x];
            else    ans[i]='l',x=-p[i][x];
        }
        for(int i=1;i<=n;i++)   putchar(ans[i]);puts("");
    }
    for(int i=0;i<=n;i++)for(int j=0;j<=sum;j++)dp[i][j]=p[i][j]=0;
}
int main(){
    freopen("playing.in","r",stdin);freopen("playing.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
}