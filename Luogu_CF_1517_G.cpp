#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1100,maxp=maxn<<1,inf=0x3f3f3f3f,dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
int n;
namespace Graph{
    const int maxm=maxp<<4;
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to;ll w;}e[maxm];
    inline void add(int u,int v,ll w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,ll w){add(u,v,w);add(v,u,0);}
}
using namespace Graph;
int d[maxp],now[maxp];
int S,T;
queue<int> q;
inline bool bfs(){
    while(!q.empty())   q.pop();
    memset(d,0x3f,sizeof(d));
    memcpy(now,head,sizeof(head));
    d[0]=0;
    q.push(S);
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=e[i].nxt){
            int t=e[i].to;
            if(d[t]!=inf||e[i].w<=0)  continue;
            d[t]=d[u]+1;
            q.push(t);
            if(t==T)    return true;
        }
    }
    return false;
}
ll dfs(int u,ll flw){
    if(u==T)    return flw;
    ll res=0;
    for(int i=now[u];i&&flw;i=e[i].nxt){
        now[u]=i;
        int t=e[i].to;
        if(d[t]!=d[u]+1||!e[i].w)    continue;
        int k=dfs(t,min(1ll*e[i].w,flw));
        if(!k)  d[t]=inf;
        e[i].w-=k;e[i^1].w+=k;
        res+=k;flw-=k;
    }
    return res;
}
ll dinic(){
    ll ans=0;
    while(bfs())    ans+=dfs(S,inf);
    return ans;
}
int tot;ll sum;
pii p[maxn];ll w[maxn];
map<pii,int> mp;
int main(){
    scanf("%d",&n);
    T=n<<1|1;
    for(int i=1;i<=n;i++){
        scanf("%d%d%lld",&p[i].first,&p[i].second,&w[i]);
        sum+=w[i];
        mp[p[i]]=i;
        if((p[i].fi&1)&&(p[i].se&1))  adde(S,i,inf);
        adde(i,i+n,w[i]);
        if((p[i].fi&1)&&!(p[i].se&1))  adde(i+n,T,inf);
    }
    for(int a=1;a<=n;a++){
        if(!(p[a].first&1)||!(p[a].second&1))   continue;
        for(int o1:{0,1}){
            int b=mp[{p[a].fi+dir[o1][0],p[a].se+dir[o1][1]}];
            if(!b)  continue;
            for(int o2:{2,3}){
                int c=mp[{p[b].fi+dir[o2][0],p[b].se+dir[o2][1]}];
                if((p[c].first&1)||(p[c].second&1))   continue;
                if(!c)  continue;
                for(int o3:{0,1}){
                    int d=mp[{p[c].fi+dir[o3][0],p[c].se+dir[o3][1]}];
                    if(!d||b==d)  continue;
                    adde(a+n,b,inf);adde(b+n,c,inf);adde(c+n,d,inf);
                }
            }
        }
    }
    printf("%lld\n",sum-dinic());
}