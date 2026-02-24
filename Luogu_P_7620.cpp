#include<bits/stdc++.h>
#define rep(t) for(int t:{0,1,2,3})
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=20,mod=998244353;
int n,m;
ll sum;
ll l[maxn],r[maxn];
int dif[maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
inline bool check(int s,int k){
    ll ss=0;
    for(int i=1;i<n;i++){
        if(s&1<<i>>1){
            if(dif[i]<k)    return false;  // 若 l[1~k] 和 r[1~k] 相同，则只剩下一种状态即可。
            ss^=r[i];
        }
        else    ss^=l[i];
    }
    return (ss>>k)==(sum>>k);
}
int dp[maxn][4];
int ans;
int main(){
    scanf("%d",&n);m=60;
    for(int i=1;i<=n;i++){scanf("%lld",&l[i]);r[i-1]=l[i];sum^=l[i];}
    for(int i=1;i<n;i++){
        dif[i]=-1;
        for(int j=m-1;~j;j--)if(bool(l[i]&(1ll<<j))^bool(r[i]&(1ll<<j))){dif[i]=j;break;}
    }
    for(int i=0;i<1<<n>>1;i++) ans+=check(i,0);
    for(int i=0;i<m;i++)for(int s=0;s<1<<n>>1;s++){
        if(!check(s,i+1))   continue;
        mems(dp,0);dp[0][0]=1;
        for(int p=1;p<n;p++){
            if(dif[p]<i){
                int num=(r[p]-l[p]+1)%mod;
                rep(t)madd(dp[p][t],immul(dp[p-1][t^bool(l[p]&(1ll<<i))],num));
            }
            else if(dif[p]==i){
                ll x=r[p]>>i<<i,s0=x-l[p],s1=r[p]-x+1;
                s0%=mod;s1%=mod;
                rep(t){
                    madd(dp[p][t],immul(dp[p-1][t],s0));
                    madd(dp[p][t],immul(dp[p-1][t^1],s1));
                }
            }
            else if(s&1ll<<p>>1){  // b[p] 的第 i+1 到 m-1 位与 r[p] 相同
                ll lim=r[p]>>i<<i;
                if(!(r[p]&1ll<<i)){
                    ll s0=r[p]-lim+1;
                    s0%=mod;
                    rep(t)madd(dp[p][t],immul(dp[p-1][t],s0));
                }
                else{
                    ll s0=1ll<<i,s1=r[p]-lim+1;
                    s0%=mod;s1%=mod;
                    rep(t){
                        madd(dp[p][t],immul(dp[p-1][t^1],s1));
                        if(t>1)madd(dp[p][t],imadd(immul(dp[p-1][t],s0),dp[p-1][t&1]));
                    }
                }
            }
            else{  // b[p] 的第 i+1 到 m-1 位与 l[p] 相同
                ll lim=l[p]|((1ll<<i)-1);
                if(l[p]&1ll<<i){
                    ll s1=lim-l[p]+1;
                    s1%=mod;
                    rep(t)madd(dp[p][t],immul(dp[p-1][t^1],s1));
                }
                else{
                    ll s0=lim-l[p]+1,s1=1ll<<i;
                    s0%=mod;s1%=mod;
                    rep(t){
                        madd(dp[p][t],immul(dp[p-1][t],s0));
                        if(t>1)madd(dp[p][t],imadd(immul(dp[p-1][t^1],s1),dp[p-1][(t^1)&1]));
                    }
                }
            }
        }
        bool o=sum&(1ll<<i);
        madd(ans,dp[n-1][2|o]);
    }
    printf("%d\n",ans);
}