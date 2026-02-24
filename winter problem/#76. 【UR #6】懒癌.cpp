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
const int maxn=3010,mod=998244353;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
namespace Graph{
    const int maxm=maxn*maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn],deg[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;deg[v]++;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=deg[i]=0;cnt=1;}
}
using namespace Graph;
int tot,cscc;
char a[maxn][maxn];
bool kil[maxn];
vector<int> sc[maxn];
int dfsn[maxn],low[maxn];
stack<int> stk;bool instk[maxn];
bitset<maxn> bs[maxn];
void tarjan(int u){
    dfsn[u]=low[u]=++tot;
    stk.ep(u);instk[u]=true;
    go(u,i){
        if(!dfsn[t]){tarjan(t);gmn(low[u],low[t]);}
        else if(instk[t]) gmn(low[u],dfsn[t]);
    }
    if(dfsn[u]==low[u]){
        cscc++;
        int p=0;
        do{
            p=stk.top();stk.pop();instk[p]=false;
            sc[cscc].eb(p);
        }while(p^u);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%s",a[i]+1);
        for(int j=1;j<=n;j++){
            if(a[i][j]=='0'&&(i^j))  add(i,j);
        }
    }
    for(int i=1;i<=n;i++)if(!dfsn[i])tarjan(i);
    int cnt=n;
    for(int i=1;i<=cscc;i++){
        if(sc[i].size()>1)for(int j:sc[i])kil[j]=true,cnt--;
        else{
            int u=sc[i][0];
            go(u,_)if(kil[t]){kil[u]=true;cnt--;break;}
        }
    }
    queue<int> q;
    // for(int i=1;i<=n;i++)if(kil[i])q.ep(i);
    // while(!q.empty()){
    //     int u=q.front();q.pop();
    //     go(u,i){
    //         if(!kil[t]) kil[t]=true,q.ep(t),cnt--;
    //     }
    // }
    debug("cnt = %d\n",cnt);
    rebuild();
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(a[i][j]=='0'&&(i^j)&&!kil[i]&&!kil[j])add(i,j);
    for(int i=1;i<=n;i++)bs[i].set(i);
    for(int i=1;i<=n;i++)if(!deg[i]&&!kil[i])q.ep(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i){
            bs[t]|=bs[u];
            if(!(--deg[t])) q.ep(t);
        }
    }
    int ans1=0,ans2=0;
    for(int i=1;i<=n;i++)if(!kil[i]){
        int c=bs[i].count();
        madd(ans1,immul(imdel(qpow(2,c),1),qpow(2,cnt-c)));
        madd(ans2,qpow(2,cnt-c));
    }
    printf("%d %d\n",ans1,ans2);
}