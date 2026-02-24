#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=22,maxp=maxn*maxn,maxt=2e6+10;
int n,m;
int a[maxn];
namespace AC{
    int tot;
    int nex[maxp][30];
    int fail[maxp],dep[maxp],dp[maxp];
    bool en[maxp];
    queue<int> q;
    void insert(char *s){
        int p=0,len=strlen(s);
        for(int i=0;i<len;i++){
            int o=s[i]-'a';
            if(!nex[p][o])  nex[p][o]=++tot;
            printf("%d %d %c\n",p,nex[p][o],s[i]);
            p=nex[p][o];
        }
        en[p]=true;
    }
    void build_fail(){
        for(int i=0;i<26;i++)
            if(nex[0][i]){
                dep[nex[0][i]]=1;
                q.push(nex[0][i]);
            }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            dp[u]=dp[fail[u]];
            if(en[u]) dp[u]|=(1<<dep[u]);
            for(int i=0;i<26;i++){
                if(nex[u][i]){
                    dep[nex[u][i]]=dep[u]+1;
                    fail[nex[u][i]]=nex[fail[u]][i];
                    q.push(nex[u][i]);
                }
                else    nex[u][i]=nex[fail[u]][i];
            }
        }
    }
    int query(char *s){
        int p=0,len=strlen(s),ans=0;
        ull sta=1;
        for(int i=0;i<len;i++){
            int o=s[i]-'a';
            sta<<=1;
            p=nex[p][o];
            printf("%d : %d %d\n",p,dp[p],sta);
            if(dp[p]&sta){sta|=1;ans=i+1;}
        }
        return ans;
    }
}

char t[maxt];
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        char s[maxn];
        scanf("%s",s);
        AC::insert(s);
    }
    AC::build_fail();
    for(int i=0;i<=AC::tot;i++) printf("%d ",AC::dp[i]);puts("");
    while(m--){
        scanf("%s",t);
        printf("%d\n",AC::query(t));
    }
}