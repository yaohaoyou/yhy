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
const int maxn=1e6+10;
bool mem1;
int n;
int a[maxn],b[maxn],id[maxn][2];
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
pii mn[maxn];
int f[maxn];
queue<int> q;
bool mem2;
void matt(int _cases){
    rebuild();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]),adde(a[i],b[i]);
    n<<=1;
    fill(f,f+cnt+1,1e9);
    for(int i=1;i<=n;i++)   mn[i]=pii(1e9,1e9);
    f[3]=0;q.ep(3);
    while(!q.empty()){
        int w=q.front(),u=e[w].to;q.pop();
        go(u,i)if(i^w^1){
            if(f[i]>f[w]+1){
                f[i]=f[w]+1;
                q.ep(i);
            }
        }
    }
    printf("%d\n",f[4]==f[0]?-1:f[4]);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}