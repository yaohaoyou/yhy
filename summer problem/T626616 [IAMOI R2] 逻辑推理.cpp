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
const int maxn=16,maxm=40;
int n,m,q,point;
int b[maxm][maxm];
int len[maxm],t[maxm];
bool a[maxn];
char s[5];
stack<bool> stk;
namespace Graph{
    const int maxp=1<<maxn,maxe=maxp*maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxp],deg[maxp];
    struct edge{int nxt,to;}e[maxe];
    inline void add(int u,int v){deg[v]++;e[++cnt]={head[u],v};head[u]=cnt;}
    void rebuild(){for(int i=0;i<(1<<n);i++)head[i]=deg[i]=0;cnt=1;}
}
using namespace Graph;
inline int calc(int o){
    while(!stk.empty())stk.pop();
    for(int i=1;i<=len[o];i++){
        if(b[o][i]>0)   stk.ep(a[b[o][i]]);
        else if(!b[o][i]){bool x=stk.top(),y;stk.pop();y=stk.top();stk.pop();stk.ep(x|y);}
        else{bool x=stk.top(),y;stk.pop();y=stk.top();stk.pop();stk.ep(x&y);}
    }
    assert(stk.size()==1);
    return stk.top();
}
int dp[1<<maxn][maxn];
queue<int> que;
void bfs(){
    mems(dp,0x3f);
    for(int i=0;i<=point;i++)
        for(int j=1;j<=n;j++)if(i&(1<<j-1))dp[i][j]=0;
    for(int i=0;i<=point;i++)
        if(!deg[i]) que.ep(i);
    while(!que.empty()){
        int u=que.front();que.pop();
        go(u,i){
            for(int j=1;j<=n;j++)dp[t][j]=min(dp[t][j],dp[u][j]+1);
            if(!(--deg[t])) que.ep(t);
        }
    }
}
void matt(){
    rebuild();
    scanf("%d%d%d",&n,&m,&q);point=(1<<n)-1;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&len[i],&t[i]);
        for(int j=1;j<=len[i];j++){
            scanf("%s",s);
            if(s[0]=='&')   b[i][j]=-1;
            else if(s[0]=='|')  b[i][j]=0;
            else if(strlen(s)==2)   b[i][j]=s[1]-'0';
            else    b[i][j]=(s[1]-'0')*10+s[2]-'0';
        }
    }
    for(int i=0;i<=point;i++){
        for(int j=1;j<=n;j++)   a[j]=i&(1<<j-1);
        for(int j=1;j<=m;j++){
            if(!a[t[j]]&&calc(j))   add(i|(1<<t[j]-1),i);
        }
    }
    bfs();
    while(q--){
        int sta=0;
        for(int i=1;i<=n;i++){int x;scanf("%1d",&x);if(x)sta|=1<<i-1;}
        int x;scanf("%d",&x);
        if(dp[sta][x]==dp[point+1][0])   puts("-1");
        else    printf("%d\n",dp[sta][x]);
    }
}
int main(){int T;scanf("%d",&T);while(T--)matt();}