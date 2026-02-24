#include<bits/stdc++.h>
// #include "festival.h"
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=2e5+10,V=1e9;
int n,m;
piii a[maxn];
pii b[maxn];
int fr[maxn][35];
ll dp[maxn][35];  // dp[i][j] 表示前 i 个数选了 j 个的最大值
std::vector<int> max_coupons(int aaa,std::vector<int> P,std::vector<int> T){
    ll A=aaa;
    for(int i=0;i<P.size();i++){
        if(T[i]==1) b[++m]=pii(P[i],i);
        else a[++n]=piii(pii(P[i],T[i]),i);
    }
    sort(a+1,a+n+1,[&](piii x,piii y){return 1ll*x.fi.fi*x.fi.se*(y.fi.se-1)<1ll*y.fi.fi*y.fi.se*(x.fi.se-1);});sort(b+1,b+m+1);
    vector<int> ans;ans.clear();
    for(int i=1;i<=n;i++){
        ll nw=(A-a[i].fi.fi)*a[i].fi.se;
        if(nw>=A){
            ans.eb(a[i].se),A=nw;
            if(A>1ll*maxn*V){
                for(int j=i+1;j<=n;j++) ans.eb(a[j].se);
                for(int j=1;j<=m;j++)   ans.eb(b[j].se);
                // printf("%d\n",ans.size());
                return ans;
            }
        }
        else break;
    }
    for(int i=ans.size()+1;i<=n;i++)    a[i-ans.size()]=a[i];
    n-=ans.size();
    mems(dp,-0x3f);
    dp[0][0]=A;
    for(int i=1;i<=n;i++){
        dp[i][0]=dp[i-1][0];
        for(int j=1;j<35;j++){
            dp[i][j]=dp[i-1][j];fr[i][j]=j;
            if(dp[i-1][j-1]>=a[i].fi.fi){
                ll w=1ll*(dp[i-1][j-1]-a[i].fi.fi)*a[i].fi.se;
                if(dp[i][j]<w)dp[i][j]=w,fr[i][j]=j-1;
            }
        }
    }
    int res=0;int p=0;
    ll s=0;
    for(int i=0;i<=m;i++){
        s+=b[i].fi;
        // printf("s = %lld\n",s);
        for(int j=34;~j;j--)if(dp[n][j]>=s){
            if(res<j+i){res=j+i;p=i;}
            break;
        }
    }
    {
        vector<int> tmp;tmp.clear();
        int i=n,j=res-p;
        while(i){
            if(j^fr[i][j])  tmp.eb(a[i].se);
            j=fr[i][j];
            i--;
        }
        reverse(tmp.begin(),tmp.end());
        for(int i:tmp) ans.eb(i);
    }
    for(int i=1;i<=p;i++)   ans.eb(b[i].se);
    return ans;
}
// int main(){
//     int N,A;
//     vector<int> P,T;
//     scanf("%d%d",&N,&A);
//     for(int i=1;i<=N;i++){
//         int x,y;scanf("%d%d",&x,&y);
//         P.eb(x);T.eb(y);
//     }
//     vector<int> ret=max_coupons(A,P,T);
//     printf("%d\n",ret.size());
//     for(int i:ret)  printf("%d ",i);puts("");
// }