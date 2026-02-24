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
#define NO return puts("NO"),void()
using namespace std;
const int maxn=2e5+10;
int n,lst,rt,mxson;
int siz[maxn];
bool a[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x];i;i=e[i].nxt)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    void rebuild(){for(int i=1;i<=n;i++)head[i]=0;cnt=1;}
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
}
using namespace Graph;
int fa[maxn];
void dfs(int u,int ft){
    fa[u]=ft;
    siz[u]=1;
    int son=0;
    go(u,i){
        int t=e[i].to;
        if(t==ft)   continue;
        dfs(t,u);
        son++;
        siz[u]+=siz[t];
    }
    if(siz[u]>=lst&&n-siz[u]>=lst&&son>1)  rt=u;
}
int ans[maxn];
bool in[maxn];
queue<int> subtr,out;
queue<int> q;
void bfs(int u){
    while(!subtr.empty())subtr.pop();while(!out.empty())out.pop();
    for(int i=1;i<=n;i++)   in[i]=false;
    q.ep(u);
    while(!q.empty()){
        int x=q.front();q.pop();
        subtr.ep(x);in[x]=true;
        go(x,i)if(e[i].to^fa[x])q.ep(e[i].to);
    }
    for(int i=1;i<=n;i++)   if(!in[i])out.ep(i);
}
void matt(){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<n;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    for(int i=1;i<=n;i++)   scanf("%1d",&a[i]);
    if(a[2])    NO;
    for(int i=1;i<=n;i++){
        if(!a[i]&&(i&1))    NO;
        if(!a[i])   lst=i/2;
    }
    rt=0;
    dfs(1,0);
    if(!rt) NO;
    bfs(rt);
    int tot=0;
    for(int i=2,sum=0;i<=n;i+=2){
        if(a[i]){
            if(sum==i/2){
                ans[++tot]=subtr.front();subtr.pop();sum++;
                ans[++tot]=out.front();out.pop();
            }
            else{
                ans[++tot]=subtr.front();subtr.pop();sum++;
                ans[++tot]=subtr.front();subtr.pop();sum++;
            }
        }
        else{
            if(sum==i/2){
                ans[++tot]=out.front();out.pop();
                ans[++tot]=out.front();out.pop();
            }
            else{
                ans[++tot]=subtr.front();subtr.pop();sum++;
                ans[++tot]=out.front();out.pop();
            }
        }
    }
    if(!subtr.empty())  ans[++tot]=subtr.front();
    if(!out.empty())    ans[++tot]=out.front();
    puts("YES");
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);puts("");
}
int main(){int T;scanf("%d%*d",&T);while(T--)matt();}