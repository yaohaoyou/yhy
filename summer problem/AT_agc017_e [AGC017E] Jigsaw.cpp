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
#define NO return puts("NO"),0;
using namespace std;
const int maxn=1e5+10,H=210,maxp=(H<<1)+10;
int n,h;
int in[maxp],out[maxp];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int cur;
bool vis[maxp];
void dfs(int u){
    vis[u]=true;cur+=(in[u]!=out[u]);
    go(u,i)if(!vis[t])dfs(t);
}
int main(){
    scanf("%d%d",&n,&h);
    for(int i=1;i<=n;i++){
        int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
        int l=c?-c:a,r=d?-d:b;
        r=-r;
        adde(l+H,r+H);
        // printf("%d %d\n",l,r);
        out[l+H]++;in[r+H]++;
    }
    for(int i=-h;i<0;i++)if(in[i+H]<out[i+H])NO;
    for(int i=1;i<=h;i++)if(in[i+H]>out[i+H])NO;
    for(int i=h;i>=-h;i--){
        if(vis[i+H]||(!out[i+H]))    continue;
        cur=0;
        dfs(i+H);
        // if(!cur)    printf("i = %d %d %d\n",i,in[i+H],out[i+H]),puts("");
        if(!cur)   NO;
    }
    puts("YES");
}