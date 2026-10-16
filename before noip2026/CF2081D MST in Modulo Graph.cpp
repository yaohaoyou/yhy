#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<int,pii>
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
int a[maxn],b[maxn];
piii E[maxn*14];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
bool mem2;
void matt(int _cases){
    m=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    sort(a+1,a+n+1);
    U.init();
    for(int i=1;i<=n;i++){
        int j=i+1;
        while(j<=n&&a[j]==a[i]){
            U.merge(i,j);
            j++;
        }
        b[a[j-1]]=j-1;
        i=j-1;
    }
    int mx=a[n];
    for(int i=1;i<=mx;i++)if(b[i]){
        for(int j=i;j<=mx;j+=i){
            int k=lower_bound(a+b[i]+1,a+n+1,j)-a;
            if(k<=n&&a[k]<j+i)E[++m]=piii(a[k]-j,pii(b[i],k));
        }
        b[i]=0;
    }
    ll ans=0;
    sort(E+1,E+m+1);
    for(int i=1;i<=m;i++){
        int u=E[i].se.fi,v=E[i].se.se;
        u=U[u];v=U[v];
        if(u^v){
            ans+=E[i].fi;
            U.merge(u,v);
        }
    }
    printf("%lld\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}