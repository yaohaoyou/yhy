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
const int maxn=5e5+10;
bool mem1;
int n,m;
vector<int> son[maxn];
inline void adde(int u,int v){son[u].eb(v);son[v].eb(u);}
priority_queue<pii> q;
int cnt[maxn];
// set<pii,greater<pii>> q;
int f[maxn];
int ans;
bool mem2;
void matt(int _cases){
    ans=0;for(int i=1;i<=n;i++)son[i].clear(),cnt[i]=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);adde(u,v);}
    fill(f+1,f+n+1,1e9);
    q.ep(f[1]=0,-1);
    while(!q.empty()){
        int d=q.top().fi,u=-q.top().se;q.pop();
        if(f[u]^d)  continue;
        cnt[u]++;
        assert(f[u]==d);
        ans++;
        for(int t:son[u])if(f[t]>f[u]+1){
            f[t]=f[u]+1;
            q.ep(f[t],-t);
        }
    }
    // for(int i=1;i<=n;i++)   assert((1<<__lg(cnt[i]))==cnt[i]);
    printf("%d %d\n",n,m);
    for(int i=1;i<=n;i++)   printf("%d ",f[i]);puts("");
    for(int i=1;i<=n;i++)   printf("%d ",cnt[i]);puts("");
    // printf("%d\n",ans);
    printf("%d\n",accumulate(cnt+1,cnt+n+1,0));
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}