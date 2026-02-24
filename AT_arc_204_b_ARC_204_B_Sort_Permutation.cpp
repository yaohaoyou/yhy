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
const int maxn=510,maxk=15,maxnk=maxn*maxk;
int n,k;
int p[maxnk],dp[maxnk][maxnk];
bool vis[maxnk];
vector<int> buc[maxn];
int main(){
    scanf("%d%d",&n,&k);
    int m=n*k;
    for(int i=1;i<=m;i++)   scanf("%d",&p[i]);
    int ans=0;
    for(int i=1;i<=m;i++){
        if(vis[i])  continue;
        vector<int> v;v.clear();
        int x=i;
        while(!vis[x]){v.eb(x);vis[x]=true;x=p[x];}
        if(v.size()==1) continue;
        int len=v.size();
        for(int j=0;j<n;j++)    buc[j].clear();
        for(int j=0;j<len;j++)    buc[v[j]%n].eb(j);
        for(int j=1;j<=len;j++){
            for(int l=0,r=j-1;r<len;l++,r++){
                dp[l][r]=max(dp[l+1][r],dp[l][r-1]);
                for(int k:buc[v[l]%n])if(k>l&&k<=r)dp[l][r]=max(dp[l][r],dp[l][k-1]+dp[k][r]+1);
            }
        }
        ans+=dp[0][len-1];
    }
    printf("%d\n",ans);
}