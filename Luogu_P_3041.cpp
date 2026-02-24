#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=25,maxm=1e3+10,maxp=maxn*18;
int n,m;
ll ans;
namespace AC{
    int tot;
    int nex[maxp][3],fail[maxp],len[maxp];
    ll f[maxp][maxm],dp[maxp];
    inline void insert(char *s){
        int l=strlen(s),p=0;
        for(int i=0;i<l;i++){
            int o=s[i]-'A';
            if(!nex[p][o])  nex[p][o]=++tot;
            len[nex[p][o]]=len[p]+1;
            p=nex[p][o];
        }
        len[p]=l;
        dp[p]++;
    }
    queue<int> q;
    void build_fail(){
        for(int i=0;i<3;i++)
            if(nex[0][i])   q.push(nex[0][i]);
        while(!q.empty()){
            int u=q.front();q.pop();
            // f[u][len[u]+=f[fail[u]][len[fail[u]]];
            dp[u]+=dp[fail[u]];
            for(int i=0;i<3;i++){
                int t=nex[u][i];
                if(t)   fail[t]=nex[fail[u]][i],q.push(t);
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
    void DP(){
        mems(f,-0x3f);f[0][0]=0;
        for(int i=0;i<=m;i++)
            for(int j=0;j<=tot;j++){
                if(i)f[j][i]=max(f[j][i],f[j][i-1]);
                for(int k=0;k<3;k++)
                    if(nex[j][k])   f[nex[j][k]][i+1]=max(f[nex[j][k]][i+1],f[j][i]+dp[nex[j][k]]);
                // printf("f[%d][%d] = %d\n",j,i,f[j][i]);
                f[0][i]=max(f[0][i],f[j][i]);
            }
        for(int i=0;i<=tot;i++) ans=max(ans,f[i][m]);
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        char ch[30];
        scanf("%s",ch);
        AC::insert(ch);
    }
    AC::build_fail();
    AC::DP();
    printf("%lld\n",ans);
}