#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=70,maxp=maxn*100,maxm=110,mod=1e4+7;
int n,m;
int dp[maxm][maxp];  // dp[i][j] 表示长度为 i 到达 AC 自动机上 j 的方案数。
int tot;
int nex[maxp][30];
int en[maxp];
inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
void insert(char *s){
    int l=strlen(s),p=0;
    for(int i=0;i<l;i++){
        if(!nex[p][s[i]-'A'])   nex[p][s[i]-'A']=++tot;
        p=nex[p][s[i]-'A'];
    }
    en[p]=true;
}
queue<int> q;
int fail[maxp];
void build_fail(){
    for(int i=0;i<26;i++)
        if(nex[0][i]){q.push(nex[0][i]);}
    while(!q.empty()){
        int u=q.front();q.pop();
        en[u]|=en[fail[u]];
        for(int i=0;i<26;i++){
            if(nex[u][i]){fail[nex[u][i]]=nex[fail[u]][i];q.push(nex[u][i]);}
            else    nex[u][i]=nex[fail[u]][i];
        }
    }
}
int ans;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        char s[110];scanf("%s",s);
        insert(s);
    }
    build_fail();
    dp[0][0]=1;
    for(int i=0;i<m;i++)
        for(int j=0;j<=tot;j++)
            for(int k=0;k<26;k++)
                (!en[nex[j][k]])&&((dp[i+1][nex[j][k]]+=dp[i][j])%=mod);
    for(int i=0;i<=tot;i++) (ans+=dp[m][i])%=mod;
    printf("%d\n",(qpow(26,m)-ans+mod)%mod);
}