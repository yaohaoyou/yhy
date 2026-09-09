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
const int maxn=50,B=24,maxN=(1<<17)+10;
int n,m,N;
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
queue<int> q1;
queue<pii> q2;
bitset<(1<<B-1)+10> st[maxn];
int son[maxn][2],dep[maxn],p[maxn],id[maxn];
ll stp[maxn][maxN];
pii f[maxn][maxN];
void data(){
    n=40;printf("%d\n",n);
    for(int i=1;i<n;i++)printf("%d %d\n",rand()%n+1,rand()%n+1);
    exit(0);
}
void matt(int _cases){
    // data();
    printf("Case #%d: ",_cases);
    queue<int>().swap(q1);queue<pii>().swap(q2);
    rebuild();mems(dep,0);mems(id,0);mems(f,0);for(int i=1;i<=n;i++)st[i].reset();
    scanf("%d",&n);
    for(int i=1;i<n;i++)    scanf("%d%d",&son[i][1],&son[i][0]),add(son[i][0],i),add(son[i][1],i);
    dep[n]=1;q1.ep(n);
    while(!q1.empty()){
        int u=q1.front();q1.pop();
        go(u,i)if(!dep[t]){dep[t]=dep[u]+1;q1.ep(t);}
    }
    iota(p+1,p+n+1,1);sort(p+1,p+n+1,[&](int x,int y){return dep[x]<dep[y];});
    m=0;for(int i=B;i<=n;i++)id[p[i]]=++m;
    for(int i=1;i<B;i++)    id[p[i]]=-i;
    N=(1<<m)-1;
    // printf("N = %d %d\n",N,m);return;
    for(int i=1;i<=n-m;i++)
        for(int j=0;j<=N;j++)   f[p[i]][j]=pii(p[i],j),stp[p[i]][j]=0,q2.ep(p[i],j);
    while(!q2.empty()){
        int u=q2.front().fi,s=q2.front().se;q2.pop();
        go(u,i)if(id[t]>0){
            int ns=s^(1<<id[t]-1);
            bool o=i&1;
            if(!f[t][ns].fi&&bool(s&(1<<id[t]-1))!=o){
                f[t][ns]=f[u][s];
                stp[t][ns]=stp[u][s]+1;
                q2.ep(t,ns);
            }
        }
    }
    {
        int x=1,s=N,sb=(1<<B-1)-1;ll stp=0;
        while(x^n){
            if(id[x]>0){
                int nx=f[x][s].fi,ns=f[x][s].se;stp+=::stp[x][s];
                x=nx;s=ns;
            }
            else{
                if(st[x][sb]) return puts("Infinity"),void();
                st[x].set(sb);
                bool o=sb&(1<<(-id[x]-1));
                sb^=(1ll<<(-id[x]-1));x=son[x][o];stp++;
            }
        }
        printf("%lld\n",stp);
    }
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}