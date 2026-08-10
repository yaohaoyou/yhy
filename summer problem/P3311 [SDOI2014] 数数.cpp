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
const int maxn=1210,maxs=1510,mod=1e9+7;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
bool mem1;
char n[maxn];int len;
int m;char s[maxs];
int dp[maxn][maxs][2];
int ans;
struct AC{
    int cnt;
    int nex[maxs][10],fail[maxs];
    bool mk[maxs];
    inline void ins(){
        int p=0,sl=strlen(s+1);
        for(int i=1;i<=sl;i++){
            int o=s[i]-'0',&t=nex[p][o];
            if(!t)  t=++cnt;
            p=t;
        }
        mk[p]=true;
    }
    queue<int> q;
    void build(){
        for(int i=0;i<10;i++)if(nex[0][i])q.ep(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();mk[u]|=mk[fail[u]];
            for(int i=0;i<=9;i++){
                if(nex[u][i]){
                    fail[nex[u][i]]=nex[fail[u]][i];
                    q.ep(nex[u][i]);
                }
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
    void DP(){
        for(int i=1;i<=9;i++)if(!mk[nex[0][i]])dp[1][nex[0][i]][0]++;
        for(int i=1;i<len;i++){
            for(int j=0;j<=cnt;j++){
                madd(ans,dp[i][j][0]);
                if(!dp[i][j][0]||i==len-1)    continue;
                for(int k=0;k<=9;k++)
                    if(!mk[nex[j][k]])  madd(dp[i+1][nex[j][k]][0],dp[i][j][0]);
            }
        }
        mems(dp,0);
        for(int i=1;i<n[1]-'0';i++) if(!mk[nex[0][i]])dp[1][nex[0][i]][0]++;
        if(!mk[nex[0][n[1]-'0']])   dp[1][nex[0][n[1]-'0']][1]++;
        for(int i=1;i<len;i++){
            for(int j=0;j<=cnt;j++){
                if(dp[i][j][0]){
                    for(int k=0;k<=9;k++)if(!mk[nex[j][k]]){madd(dp[i+1][nex[j][k]][0],dp[i][j][0]);}
                }
                if(dp[i][j][1]){
                    for(int k=0;k<n[i+1]-'0';k++)if(!mk[nex[j][k]])madd(dp[i+1][nex[j][k]][0],dp[i][j][1]);
                    if(!mk[nex[j][n[i+1]-'0']])madd(dp[i+1][nex[j][n[i+1]-'0']][1],dp[i][j][1]);
                }
            }
        }
        for(int i=0;i<=cnt;i++)madd(ans,imadd(dp[len][i][0],dp[len][i][1]));
    }
}A;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%s%d",n+1,&m);len=strlen(n+1);
    for(int i=1;i<=m;i++){scanf("%s",s+1);A.ins();}
    A.build();A.DP();
    printf("%d\n",ans);
}