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
bool mem1;
const int maxn=5010;
int n,k;
pii a[maxn];vector<int> b;
int dp[maxn][maxn],mx[maxn][maxn],L[maxn];
bool contain[maxn];
deque<int> q;
bool mem2;
int main(){
    freopen("d.in","r",stdin);freopen("d.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i]!=a[j]&&a[i].fi<=a[j].fi&&a[j].se<=a[i].se){contain[i]=true;b.eb(a[i].se-a[i].fi+1);break;}
    for(int i=1;i<=n;i++){
        L[i]=i+1;
        for(int j=i-1;j;j--){
            if(contain[j])  continue;
            if(a[i].fi<=a[j].se)    L[i]=j;
            else    break;
        }
    }
    mems(dp,-0x3f);dp[0][0]=0;
    for(int j=1;j<=k;j++){
        q.clear();
        for(int i=1;i<=n;i++){
            if(contain[i]){dp[i][j-1]=dp[i-1][j-1];dp[i][j]=dp[i-1][j];continue;}
            while(!q.empty()&&q.front()<L[i])   q.pop_front();
            while(!q.empty()&&dp[q.back()-1][j-1]+a[q.back()].se<dp[i-1][j-1]+a[i].se)  q.pop_back();
            q.eb(i);
            int mxx=dp[q.front()-1][j-1]+a[q.front()].se;
            dp[i][j]=max(dp[i-1][j-1]+a[i].se-a[i].fi+1,mxx-a[i].fi+1);
        }
    }
    sort(b.begin(),b.end(),greater<int>());
    int ans=max(0,dp[n][k]),sum=0;
    for(int i=0;i<b.size()&&i<k;i++){
        sum+=b[i];
        ans=max(ans,sum+dp[n][k-i-1]);
    }
    printf("%d\n",ans);
}