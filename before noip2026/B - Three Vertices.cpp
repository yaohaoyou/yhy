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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=2e5+10;
int n,m,q;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
char s[maxn];
int dep[maxn];
pii fib[maxn];
bool G[10][10];
void dfs(int u,int ft){
    dep[u]=dep[ft]+1;
    go(u,i)if(t^ft)dfs(t,u);
}
bool bk[maxn];
void dfs(int sta){
    if(bk[sta])return;
    bk[sta]=true;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)if(G[i][j]){
            for(int k=1;k<=n;k++)if(k!=i&&G[j][k]){
                sta^=(1<<i-1);sta^=(1<<j-1);sta^=(1<<k-1);
                dfs(sta);
                sta^=(1<<i-1);sta^=(1<<j-1);sta^=(1<<k-1);
            }
        }
    }
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    scanf("%s",s+1);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    // if(n==3&&m==3){
    //     while(q--){
    //         int x;scanf("%d",&x);
    //         s[x]=s[x]=='0'?'1':'0';
    //         if(s[1]==s[2]&&s[2]==s[3])  puts("Yes");
    //         else    puts("No");
    //     }
    //     return 0;
    // }
    if(n<=6){
        for(int u=1;u<=n;u++)go(u,i)G[u][t]=true;
        dfs(0);
        while(q--){
            int x;scanf("%d",&x);
            s[x]=s[x]=='0'?'1':'0';
            int sta=0;for(int i=1;i<=n;i++)if(s[i]=='1')sta|=1<<i-1;
            puts(bk[sta]?"Yes":"No");
        }
        return 0;
    }
    if(m>n-1){
        while(q--)puts("Yes");
        return 0;
    }
    dfs(1,0);
    fib[1]=pii(0,1);
    for(int i=2;i<=n;i++)   fib[i]=pii(fib[i-1].se,(fib[i-1].fi+fib[i-1].se)&1);
    int f=0,g=0;
    for(int i=1;i<=n;i++)if(s[i]=='1')f^=fib[dep[i]].fi,g^=fib[dep[i]].se;
    while(q--){
        int x;scanf("%d",&x);
        f^=fib[dep[x]].fi,g^=fib[dep[x]].se;
        if(!f&&!g)  puts("Yes");
        else    puts("No");
    }
}