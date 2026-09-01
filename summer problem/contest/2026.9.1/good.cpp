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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e7+10;
int n,x,k;
namespace Graph{
    const int maxm=maxn*10;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
inline int f(int x){int res=0;while(x)res+=x%10,x/=10;return res;}
queue<int> q;
bool vis[maxn];
int main(){
    freopen("good.in","r",stdin);freopen("good.out","w",stdout);
    scanf("%d%d%d",&n,&x,&k);
    for(int i=1;i<=n;i++){
        if(i-f(i)*k>0)  add(i-f(i)*k,i);
        if(i^1){
            for(ll j=i;j<=n;j*=i)   add(j,i);
        }
    }
    q.ep(x);vis[x]=true;
    while(!q.empty()){
        int u=q.front();q.pop();
        go(u,i)if(!vis[t])vis[t]=true,q.ep(t);
    }
    printf("%d\n",count(vis+1,vis+n+1,1));
}