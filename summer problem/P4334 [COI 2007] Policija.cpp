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
const int maxn=2e5+10;
int n,m,q;
set<pii> st;
vector<int> son[maxn];
int dfsn[maxn],low[maxn];
stack<int> stk;
namespace Graph{
    const int maxm=2e6+10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){debug("%d %d\n",u,v);add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
int dep[maxn],dfn[maxn],tot;
namespace stLCA{
    int Log[maxn],st[20][maxn];
    inline int mindfn(int x,int y){return dfn[x]<dfn[y]?x:y;}
    void dfs(int u,int ft){dep[u]=dep[ft]+1;st[0][dfn[u]=++tot]=ft;go(u,i)if(t^ft)dfs(t,u);}
    void build(){
        dfs(1,0);
        for(int i=2;i<=n;i++)   Log[i]=Log[i/2]+1;
        for(int i=1;i<=Log[n];i++)for(int j=1;j+(1<<i)-1<=n;j++)st[i][j]=mindfn(st[i-1][j],st[i-1][j+(1<<i>>1)]);
    }
    inline int LCA(int x,int y){if(x==y)return x;if((x=dfn[x])>(y=dfn[y]))swap(x,y);int k=Log[y-x++];return mindfn(st[k][x],st[k][y-(1<<k)+1]);}
    inline int dis(int x,int y,int l=0){return dep[x]+dep[y]-(dep[l?l:LCA(x,y)]<<1);}
}
using stLCA::LCA;using stLCA::dis;
void tarjan(int u){
    dfsn[u]=low[u]=++tot;stk.ep(u);
    for(int t:son[u]){
        if(!dfsn[t]){
            tarjan(t);
            low[u]=min(low[u],low[t]);
            if(low[t]==dfsn[u]){
                m++;int cur=1,tp=0;
                while(tp^t)  cur++,adde(tp=stk.top(),m),stk.pop();
                adde(u,m);
                if(cur==2)  st.ep(u,t),st.ep(t,u);
            }
        }
        else    low[u]=min(low[u],dfsn[t]);
    }
}
bool chk(int x,int s,int t){return dis(s,x)+dis(x,t)==dis(s,t);}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);son[u].eb(v);son[v].eb(u);}
    m=n;tarjan(1);n=m;tot=0;
    stLCA::build();
    scanf("%d",&q);
    while(q--){
        int op,x,y,a,b;
        scanf("%d%d%d%d",&op,&a,&b,&x);
        if(op==1){
            scanf("%d",&y);
            if(st.find(pii(x,y))==st.end()){puts("yes");continue;}
            else{
                if(chk(x,a,b)&&chk(y,a,b))  puts("no");
                else puts("yes");
            }
        }
        else    puts(chk(x,a,b)?"no":"yes");
    }
}