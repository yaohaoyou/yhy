#include<bits/stdc++.h>
using namespace std;
const int maxn=710,mod=1e9+7;
int n;
int lst[maxn],nxt[maxn],dp[maxn][maxn][3][3];
string s;
stack<int> stk;
#define rep(i) for(int i=0;i<3;i++)
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
void dfs(int l,int r){
    // printf("%d %d\n",l,r);
    if(l>r) return;
    if(l+1==r)  return dp[l][r][0][1]=dp[l][r][0][2]=dp[l][r][1][0]=dp[l][r][2][0]=1,void();
    if(lst[r]==l){
        dfs(l+1,r-1);
        rep(x) rep(y){
            int k=dp[l+1][r-1][x][y];
            if(x!=1)    madd(dp[l][r][1][0],k);
            if(x!=2)    madd(dp[l][r][2][0],k);
            if(y!=1)    madd(dp[l][r][0][1],k);
            if(y!=2)    madd(dp[l][r][0][2],k);
        }
        return;
    }
    dfs(l,nxt[l]);dfs(nxt[l]+1,r);
    for(int i=nxt[l]+1;i<=r;i++){
        rep(x) rep(y) rep(z) rep(q){
            if(!y||!z||y!=z)    madd(dp[l][i][x][q],immul(dp[l][nxt[l]][x][y],dp[nxt[l]+1][i][z][q]));
        }
    }
}
int main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0);cout.tie(0);
    cin>>s;n=s.length();
    s=' '+s;
    for(int i=1;i<=n;i++){
        if(!stk.empty()&&s[stk.top()]!=s[i]){lst[i]=stk.top();nxt[stk.top()]=i;stk.pop();}
        else stk.push(i);
    }
    // for(int i=1;i<=n;i++)   printf("%d %d\n",lst[i],nxt[i]);
    dfs(1,n);
    int ans=0;
    rep(x) rep(y) madd(ans,dp[1][n][x][y]);
    cout<<ans<<'\n';
}