#include<bits/stdc++.h>
#define db double
#define fl float
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5010;
int n,m;
struct Graph{
    vector<int> son[maxn];int deg[maxn];
    inline void add(int u,int v){son[u].eb(v);deg[v]++;}
    inline void init(){for(int i=1;i<=n;i++)son[i].clear(),deg[i]=0;}
}G,rG;
namespace IO{
    const int SIZ=1000000;
    static char buf[SIZ+10],*p1=buf,*p2=buf,obuf[SIZ+10],*p3=obuf,cc[40];
    #define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,SIZ,stdin),p1==p2)?EOF:*p1++
    #define putchar(x) (p3-obuf<SIZ)?(*p3++=x):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x)
    #define flush fwrite(obuf,p3-obuf,1,stdout)
    #define if(sth) if(__builtin_expect(sth,1))
    #define while(sth) while(__builtin_expect(sth,1))
    inline int read(){
        int x=0; int f=1; char c=getchar();
        while(c<48||c>57){if(c=='-')f=-1;c=getchar();}
        while(c>=48&&c<=57)x=(x<<3)+(x<<1)+(c^48),c=getchar();
        x*=f;
        return x;
    }
}
using namespace IO;
queue<int> q;
db dp[maxn];  // dp[u] 表示从 u 到 n 的最大概率
db g[maxn][maxn];  // g[i][j] 表示当前有 i 个儿子，最后走向 dp 值第 j 大的概率
void topu(){
    for(int i=1;i<=n;i++){
        if(!rG.deg[i])  q.push(i);
        dp[i]=0;
    }
    dp[n]=1;
    while(!q.empty()){
        int u=q.front();q.pop();
        int d=G.deg[u];
        if(d){
            vector<db> v;
            for(int t:G.son[u])
                v.eb(dp[t]);
            stable_sort(v.begin(),v.end(),greater<db>());
            dp[u]=0;
            for(int i=0;i<v.size();i++)
                dp[u]+=v[i]*g[d][i+1];
        }
        for(int t:rG.son[u])
            if(!--rG.deg[t])    q.push(t);
    }
}
void solve(){
    G.init();rG.init();
    n=read();m=read();
    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        G.add(u,v);rG.add(v,u);
    }
    for(int i=1;i<=n;i++)   G.deg[i]=rG.deg[i];
    for(int i=1;i<=n;i+=2)
        for(int j=1;j<=i;j++)   g[i][j]=1.0/i;
    for(int i=2;i<=n;i+=2){
        g[i][1]=1.0/i;
        for(int j=2;j<=i;j++)
            g[i][j]=g[i-2][j-2]*(j-2)/i+g[i-2][j-1]*(i-j)/i;
    }
    topu();
    printf("%.12lf\n",dp[1]);
}
int main(){int T=read();while(T--)solve();}