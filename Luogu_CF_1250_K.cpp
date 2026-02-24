#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define NO return puts("NO"),void()
using namespace std;
const int maxn=310,maxp=maxn<<2;
int n,m,x,y,tim;
int id[maxn];
int a[maxn],b[maxn],P[maxn],Q[maxn];
int ans[maxn<<1];
int sx[maxp],sy[maxp];
vector<int> v,st[maxp],en[maxp];
namespace Graph{
    const int maxm=maxp<<2;
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,0);}
}
using namespace Graph;
int d[maxp],now[maxp];
int S,T;
queue<int> q;
void discrete(){
    for(int i=1;i<=n;i++){v.eb(a[i]);v.eb(b[i]);}
    for(int i=1;i<=m;i++){v.eb(P[i]);v.eb(Q[i]);}
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    tim=v.size();
    for(int i=1;i<=n;i++){a[i]=lower_bound(v.begin(),v.end(),a[i])-v.begin()+1;b[i]=lower_bound(v.begin(),v.end(),b[i])-v.begin()+1;sx[a[i]]++;sx[b[i]]--;st[a[i]].eb(i);en[b[i]].eb(i);}
    for(int i=1;i<=m;i++){P[i]=lower_bound(v.begin(),v.end(),P[i])-v.begin()+1;Q[i]=lower_bound(v.begin(),v.end(),Q[i])-v.begin()+1;sy[P[i]]++;sy[Q[i]]--;st[P[i]].eb(i+n);en[Q[i]].eb(i+n);}
    for(int i=1;i<=tim;i++)   sx[i]+=sx[i-1],sy[i]+=sy[i-1];
}
const int inf=0x3f3f3f3f;
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
int dfs(int u,int flw){
    if(u==T)    return flw;
    int res=0;
    for(int i=now[u];i&&flw;i=e[i].nxt){
        now[u]=i;
        int t=e[i].to;
        if(d[t]!=d[u]+1||!e[i].w)    continue;
        int k=dfs(t,min(e[i].w,flw));
        if(!k)  d[t]=inf;
        e[i].w-=k;e[i^1].w+=k;
        res+=k;flw-=k;
    }
    return res;
}
int dinic(){
    int ans=0;
    while(bfs())    ans+=dfs(S,inf);
    return ans;
}
stack<int> stk1,stk2;
void init(){
    for(int i=0;i<=tim;i++){st[i].clear();en[i].clear();}
    mems(sx,0);mems(sy,0);mems(head,0);v.clear();
    cnt=1;
    while(!q.empty())q.pop();
    while(!stk1.empty())stk1.pop();
    while(!stk2.empty())stk2.pop();
}
void AbsMatt(){
    init();
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=1;i<=m;i++)   scanf("%d%d",&P[i],&Q[i]);
    discrete();
    for(int i=1;i<=m;i++){adde(P[i],Q[i],1);id[i]=cnt^1;}
    for(int i=1;i<tim;i++)
        if(sx[i]>x||x+y<sx[i]+sy[i])    NO;
        else    adde(i,i+1,x+y-sx[i]-sy[i]);
    if(sx[tim]>x||x+y<sx[tim]+sy[tim])   NO;
    S=0;T=tim+1;adde(S,1,y);adde(tim,T,inf);
    if(dinic()!=y)  NO;
    puts("YES");
    for(int i=1;i<=x;i++)   stk1.push(i);
    for(int i=1;i<=y;i++)   stk2.push(i+x);
    for(int i=1;i<=tim;i++){
        for(int j:en[i]){
            if(ans[j]<=x)    stk1.push(ans[j]);
            else    stk2.push(ans[j]);
        }
        for(int j:st[i]){
            if(j<=n||e[id[j-n]].w)  ans[j]=stk1.top(),stk1.pop();
            else    ans[j]=stk2.top(),stk2.pop();
        }
    }
    for(int i=1;i<=n+m;i++) printf("%d ",ans[i]);puts("");
}
int main(){int TT;scanf("%d",&TT);while(TT--)AbsMatt();}