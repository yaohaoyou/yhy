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
const int maxn=5e5+10;
int n;
int w[maxn],c[maxn],dp[maxn];
pii sum[maxn][2];
vector<int> v[maxn];
vector<int> p;
bool ntpri[maxn];
void seive(){
    const int V=5e5;
    for(int i=2;i<=V;i++){
        if(!ntpri[i])   p.eb(i);
        for(int j:p){
            if(1ll*i*j>V)   break;
            ntpri[i*j]=true;
            if(i%j==0)  break;
        }
    }
}
void makefactors(int x,int id){
    for(int i:p){
        if(1ll*i*i>x)   break;
        if(x%i==0){
            v[id].eb(i);
            while(x%i==0)   x/=i;
        }
    }
    if(x^1) v[id].eb(x);
}
int main(){
    seive();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&w[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&c[i]);
    for(int i=1;i<=n;i++)   makefactors(w[i],i);
    int ans=0;
    for(int i=1;i<=n;i++){
        dp[i]=1;
        for(int j:v[i]){
            // printf("%d (%d,%d)\n",j,sum[j][0].fi,sum[j][0].se);
            if(sum[j][0].se!=c[i])  dp[i]=max(dp[i],sum[j][0].fi+1);
            else    dp[i]=max(dp[i],sum[j][1].fi+1);
        }
        for(int j:v[i]){
            if(sum[j][0].se==c[i])  sum[j][0]=max(sum[j][0],pii(dp[i],c[i]));
            else if(sum[j][1].se==c[i]){sum[j][1]=max(sum[j][1],pii(dp[i],c[i]));if(sum[j][1]>sum[j][0])swap(sum[j][0],sum[j][1]);}
            else if(sum[j][0].fi<dp[i])  sum[j][1]=sum[j][0],sum[j][0]=pii(dp[i],c[i]);
            else    sum[j][1]=max(sum[j][1],pii(dp[i],c[i]));
        }
        ans=max(ans,dp[i]);
    }
    printf("%d\n",ans);
}