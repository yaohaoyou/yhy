#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define bsB bitset<maxB>
#define bsN bitset<maxn>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e4+10,maxm=1e5+10,B=200,maxB=B+B+10;
int n,m;
int tot,cscc;
int dfsn[maxn],low[maxn],scc[maxn],deg[maxn];
bool ins[maxn];
pii E[maxm];
unordered_set<int> ust;
vector<int> vkp;  //  vector of key point
int kid[maxn];
stack<int> stk;
bool ikey[maxm],blk[maxm];
struct ques{int op,u,v;}Q[maxm];
vector<int> G[maxn];
bsB to[maxn],G1[maxB],G2[maxB],bsq,vis;
unordered_map<int,int> mp[maxn];
void tarjan(int u){
    stk.ep(u);ins[u]=true;
    dfsn[u]=low[u]=++tot;
    for(int t:G[u]){
        if(!dfsn[t]){tarjan(t);low[u]=min(low[u],low[t]);}
        else if(ins[t]) low[u]=min(low[u],dfsn[t]);
    }
    if(dfsn[u]==low[u]){
        int p=0;
        cscc++;
        do{
            p=stk.top();stk.pop();
            ins[p]=false;scc[p]=cscc;
        }while(p^u);
    }
}
void solve(int L,int R){
    auto addkeypoint=[&](int u){if(ust.find(u)==ust.end())ust.ep(u),vkp.eb(u),kid[u]=vkp.size();};
    vkp.clear();ust.clear();
    mems(ikey,0);mems(dfsn,0);mems(deg,0);cscc=tot=0;
    for(int i=1;i<=n;i++)G[i].clear(),to[i].reset(),G1[i].reset(),G2[i].reset();
    for(int i=L;i<=R;i++)
        if(Q[i].op==1){
            ikey[Q[i].u]=true;
            int u=E[Q[i].u].fi,v=E[Q[i].u].se;
            addkeypoint(u);addkeypoint(v);
        }
        else{
            int u=Q[i].u,v=Q[i].v;
            addkeypoint(u);addkeypoint(v);
        }
    for(int i=1;i<=m;i++)if(blk[i]&&!ikey[i])G[E[i].fi].eb(E[i].se);
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
    for(int i=1;i<=n;i++)    to[i].reset(),G[i].clear();
    for(int i=1;i<=vkp.size();i++)  to[scc[vkp[i-1]]].set(i);
    for(int i=1;i<=m;i++){
        if(blk[i]&&!ikey[i]){
            int u=E[i].fi,v=E[i].se;
            if(scc[u]^scc[v])   G[scc[v]].eb(scc[u]),deg[scc[u]]++;
        }
    }
    queue<int> q;
    for(int i=1;i<=cscc;i++)if(!deg[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int t:G[u]){
            to[t]|=to[u];
            if(!(--deg[t])) q.ep(t);
        }
    }
    for(int i=1;i<=cscc;i++)assert(!deg[i]);
    for(int i=1;i<=vkp.size();i++)  G1[i].reset(),G2[i].reset();
    for(int i=1;i<=vkp.size();i++)for(int j=1;j<=vkp.size();j++)G1[i][j]=to[scc[vkp[i-1]]][j];
    // printf("cscc = %d\n",cscc);
    // for(int i=1;i<=cscc;i++,puts(""))for(int j=1;j<=vkp.size();j++)printf("%d ",bool(to[i][j]));
    // puts("");
    // for(int i:vkp)  debug("%d ",i);debug("\n");
    // for(int i=1;i<=n;i++)   debug("%d ",scc[i]);debug("\n\n");
    // for(int i=1;i<=vkp.size();i++,puts(""))for(int j=1;j<=vkp.size();j++)printf("%d ",bool(G1[i][j]));
    for(int i=1;i<=m;i++)if(blk[i]&&ikey[i])G2[kid[E[i].fi]].set(kid[E[i].se]);
    for(int _=L;_<=R;_++){
        auto [op,u,v]=Q[_];
        if(op==1){
            int i=u;blk[i]^=1;
            u=E[i].fi;v=E[i].se;
            if(blk[i]){
                mp[u][v]++;
                if(mp[u][v])    G2[kid[u]].set(kid[v]);
            }
            else{
                mp[u][v]--;
                if(!mp[u][v])   G2[kid[u]].reset(kid[v]);
            }
        }
        else{
            u=kid[u];v=kid[v];
            bsq.reset();vis.reset();
            bsq.set(u);
            // printf("# %d %d\n",u,v);
            while(!bsq[v]){
                int x=(bsq&(~vis))._Find_first();
                // printf("x = %d\n",x);
                if(x==bsq.size()){puts("NO");break;}
                vis.set(x);
                bsq|=G1[x]|G2[x];
            }
            if(bsq[v])  puts("YES");
        }
    }
    // puts("-----------------");
}
int main(){
    int q;
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++){
        scanf("%d%d",&E[i].fi,&E[i].se);
        blk[i]=true;mp[E[i].fi][E[i].se]++;
    }
    for(int i=1;i<=q;i++){
        scanf("%d%d",&Q[i].op,&Q[i].u);
        if(Q[i].op==2)  scanf("%d",&Q[i].v);
    }
    for(int i=1;i<=q;i+=B)  solve(i,min(i+B-1,q));
}