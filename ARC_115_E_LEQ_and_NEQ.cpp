#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,mod=998244353;
int n;
int a[maxn];
int dp[maxn][2];  // dp[i][0/1] 表示前 i 个数分为了奇/偶段
int s[maxn][2];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
stack<int> stk;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    dp[0][0]=1;s[0][0]=1;
    stk.emplace(0);
    for(int i=1;i<=n;i++){
        while(a[i]<=a[stk.top()])  stk.pop();
        int lst=stk.top();
        stk.push(i);
        dp[i][0]=lst?dp[lst][0]:0;dp[i][1]=lst?dp[lst][1]:0;
        madd(dp[i][0],immul(imdel(s[i-1][1],lst?s[lst-1][1]:0),a[i]));
        madd(dp[i][1],immul(imdel(s[i-1][0],lst?s[lst-1][0]:0),a[i]));
        s[i][0]=imadd(s[i-1][0],dp[i][0]);
        s[i][1]=imadd(s[i-1][1],dp[i][1]);
    }
    if(n&1) swap(dp[n][0],dp[n][1]);
    printf("%d\n",imdel(dp[n][0],dp[n][1]));
}