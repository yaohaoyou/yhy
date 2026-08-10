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
char s[maxn];
vector<pii> v;
pii dp[maxn];
void chk(pii &x,pii y){if(x.fi<y.fi)x=y;else if(x.fi==y.fi&&x.se>y.se)x=y;}
void matt(){
    v.clear();
    scanf("%d%s",&n,s+1);
    if(!count(s+1,s+n+1,'0')||!count(s+1,s+n+1,'1'))    return puts("0 0"),void();
    int l=0,L=0,R=0,cnt=0;
    for(int i=1;i<=n;i++){
        int j=i;while(j<=n&&s[i]==s[j])j++;j--;
        v.eb(i,j);i=j;
    }
    if(s[1]=='1')   v.erase(v.begin());
    if(v.size()<2)  return puts("0 0"),void();
    pii ans=pii(0,0);
    int j=1;
    for(int i=1;i<v.size();i+=2,j++){
        int l=v[i].fi,r=v[i].se,l1=r-l+1,pl=v[i-1].fi,pr=v[i-1].se,l0=pr-pl+1;
        // printf("%d %d %d %d\n",pl,pr,l,r);
        pii nw=pii(0,0);
        if(l1>=l0)  dp[j]=pii(1,l1-l0+l1-1),nw=pii(1,l0-1);
        else dp[j]=pii(1,l1-1);
        if(l1>=l0)  chk(dp[j],pii(dp[j-1].fi+1,dp[j-1].se+l1-l0+l1-1));
        chk(ans,pii(dp[j-1].fi+nw.fi,dp[j-1].se+nw.se));
    }
    printf("%d %d\n",ans.fi,ans.se);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}