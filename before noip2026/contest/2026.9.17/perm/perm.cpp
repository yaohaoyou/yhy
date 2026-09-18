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
const int maxn=1e5+10;
bool mem1;
int n,k;
int a[maxn],p[maxn],q[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
int siz[maxn];
bool mem2;
void matt(int _cases){
    fill(siz+1,siz+n+1,0);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]),a[p[i]]=i;
    for(int i=1;i<=n;i++)   scanf("%d",&q[i]),q[i]=a[q[i]];
    U.init();
    for(int i=1;i<=n;i++)   U.merge(i,q[i]);
    for(int i=1;i<=n;i++)   siz[U[i]]++;
    int cnt=0;
    for(int i=1;i<=n;i++)if(U[i]==i)cnt+=siz[i]-1;
    puts(k>=cnt&&(k&1)==(cnt&1)?"Yes":"No");
}
int main(){freopen("perm.in","r",stdin);freopen("perm.out","w",stdout);debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}