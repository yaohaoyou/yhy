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
const int maxn=510,V=500*500;
int n;
vector<pii> a[3];
int dp[3][maxn*maxn],f[3][maxn*maxn*2];
inline void gmx(int &x,int y){(x<y)&&(x=y);}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int t,x,y;scanf("%d%d%d",&t,&x,&y);
        a[t-1].eb(x,y);
    }
    mems(f,-0x3f);
    for(int o=0;o<3;o++){
        dp[o][0]=0;
        for(pii i:a[o])
            for(int j=V;j>=i.fi;j--)    gmx(dp[o][j],dp[o][j-i.fi]+i.se);
        for(int i=0;i<=V;i++)   gmx(f[o][dp[o][i]+i],dp[o][i]);
        for(int i=1;i<=V+V;i++) gmx(f[o][i],f[o][i-1]);
    }
    int ans=0;
    for(int i=0;i<=V+V;i++)
        if(f[0][i]>=0&&f[1][i]>=0&&f[2][i]>=0) gmx(ans,f[0][i]+f[1][i]+f[2][i]-i);
    printf("%d\n",ans);
}