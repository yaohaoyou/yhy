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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1.5e5+10;
int n,m,q;
int p[maxn],ip[maxn];
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
#define bs bitset<32000>
bs to[maxn],now;
vector<int> Ix[maxn],Iy[maxn],Dx[maxn],Dy[maxn];
vector<int> topu;
queue<int> que;
int x[maxn][2],y[maxn][2],ans[maxn];
void bfs(){
    for(int i=1;i<=n;i++)if(!deg[i])que.ep(i);
    while(!que.empty()){
        int u=que.front();que.pop();
        topu.eb(u);
        go(u,i)if(!(--deg[t]))que.ep(t);
    }
}
vector<bs> solve(int l,int r){
    if(l==r)    return vector<bs>({to[l]});
    int mid=(l+r)>>1;
    vector<bs> L=solve(l,mid),R=solve(mid+1,r);
    if(L.size()<R.size())   L.swap(R);
    bs add=bs(),tmp;
    for(int i=0;i<L.size();i++){
        if(i<R.size()){
            tmp=L[i]&R[i];
            L[i]^=R[i];
            tmp|=(L[i]&add);
            L[i]^=add;
            add=tmp;
        }
        else{
            tmp=L[i]&add;
            L[i]^=add;add=tmp;
        }
    }
    if(add.any())   L.eb(add);
    return L;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]),ip[p[i]]=i;
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);add(u,v);}
    bfs();
    scanf("%d",&q);
    for(int i=1;i<=q;i++)   scanf("%d%d%d%d",&x[i][0],&y[i][0],&x[i][1],&y[i][1]);
    for(int l=1,r=min(q,32000);l<=q;l=r+1,r=min(q,r+32000)){
        for(int i=1;i<=n;i++)to[i].reset();
        for(int i=l;i<=r;i++){
            Ix[x[i][0]].eb(i-l);Dx[x[i][1]+1].eb(i-l);
            Iy[y[i][0]].eb(i-l);Dy[y[i][1]+1].eb(i-l);
        }
        now.reset();
        for(int i=1;i<=n;i++){
            for(int j:Ix[i])    now.set(j);
            for(int j:Dx[i])    now.reset(j);
            to[i]=now;
        }
        now.reset();
        for(int i=1;i<=n;i++){
            for(int j:Iy[i])    now.set(j);
            for(int j:Dy[i])    now.reset(j);
            to[ip[i]]&=now;
        }
        for(int u:topu)go(u,i)to[t]|=to[u];
        // for(int i=1;i<=n;i++)
        //     for(int j=to[i]._Find_first();j<32000;j=to[i]._Find_next(j))ans[j+l]++;
        vector<bs> res=solve(1,n);
        for(int i=l;i<=r;i++){
            for(int j=0;j<res.size();j++)
                if(res[j][i-l]) ans[i]|=(1<<j);
        }
        for(int i=1;i<=n;i++)Ix[i].clear(),Iy[i].clear(),Dx[i].clear(),Dy[i].clear();
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}