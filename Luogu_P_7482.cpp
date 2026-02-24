#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=2e5+10,mod=1e9+7;
int n;
int a[maxn];
ll ans;
ll dp[maxn][2][2],mx[maxn][2];
#define pli pair<ll,int>
vector<pli> g;
#define eb emplace_back
inline void upans(ll x){x%=mod;(ans+=x)%=mod;}
void divide(int l,int r){
    if(l==r)    return upans(a[l]),void();
    int mid=(l+r)>>1;
    divide(l,mid);divide(mid+1,r);
    g.clear();
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)dp[mid][i][j]=0;
    dp[mid][0][0]=0;dp[mid][1][1]=a[mid];
    mx[mid][0]=0;mx[mid][1]=a[mid];
    g.eb(pli(mx[mid][0]-mx[mid][1],mid));
    for(int i=mid-1;i>=l;i--){
        for(int j=0;j<2;j++){
            dp[i][0][j]=max(dp[i+1][0][j],dp[i+1][1][j]);
            dp[i][1][j]=dp[i+1][0][j]+a[i];
            mx[i][j]=max(dp[i][0][j],dp[i][1][j]);
        }
        g.eb(pli(mx[i][0]-mx[i][1],i));
    }
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)dp[mid+1][i][j]=0;
    dp[mid+1][0][0]=0;dp[mid+1][1][1]=a[mid+1];
    mx[mid+1][0]=0;mx[mid+1][1]=a[mid+1];
    g.eb(pli(mx[mid+1][0]-mx[mid+1][1],mid+1));
    for(int i=mid+2;i<=r;i++){
        for(int j=0;j<2;j++){
            dp[i][0][j]=max(dp[i-1][0][j],dp[i-1][1][j]);
            dp[i][1][j]=dp[i-1][0][j]+a[i];
            mx[i][j]=max(dp[i][0][j],dp[i][1][j]);
        }
        g.eb(pli(mx[i][0]-mx[i][1],i));
    }
    for(int i=l;i<=mid;i++) upans(mx[i][0]*(r-mid));
    for(int i=mid+1;i<=r;i++)   upans(mx[i][1]*(mid-l+1));
    sort(g.begin(),g.end());
    int cl=0,cr=0;
    for(pli i:g){
        ll c=i.first;
        int x=i.second;
        if(x<=mid){upans(((r-mid)-cr)*(-c));cl++;}
        else{upans(cl*c);cr++;}
    }
}
signed main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    divide(1,n);
    printf("%lld\n",(ans+mod)%mod);
}