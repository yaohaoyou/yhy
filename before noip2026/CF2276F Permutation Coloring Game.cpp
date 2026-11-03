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
const int maxn=2e5+10,maxk=50;
bool mem1;
int n,k;
int a[maxn],cnt[maxn];
int f[maxk][maxk][maxk];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
bool mem2;
void matt(int _cases){
    fill_n(cnt,n+1,0);
    scanf("%d%d",&n,&k);
    U.init();
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),U.merge(i,a[i]);
    for(int i=1;i<=n;i++)cnt[U[i]]++;
    sort(cnt+1,cnt+n+1,greater<int>());
    const int K=min(k*2+10,)
    puts("Alice");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}