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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=4e5+10;
int n,cnt;
int a[maxn],b[maxn];
bool con[maxn];
ll s[maxn],ans;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
void mrg(int x,int y){
    int u=U[x],v=U[y];
    if(u==v)    return;
    U.merge(u,v);
    if(!con[x]&&!con[y])    ans+=1ll*(x+y)*(a[x]+a[y]-1);
    else if(!con[x])    ans+=1ll*(x+y)*a[x];
    else if(!con[y])    ans+=1ll*(x+y)*a[y];
    else    ans+=x+y;
    con[x]=con[y]=true;
    cnt++;
}
void data(){
    n=2e5;printf("%d\n",n);
    for(int i=1;i<=n;i++)printf("%d ",n);
    exit(0);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    // data();
    scanf("%d",&n);int m=0;
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        gmx(m,x);
        ans-=x;
        a[x]++;
    }
    a[0]++;
    n=m;
    U.init();
    int siz=n+1-count(a,a+n+1,0);
    for(int i=n+n;i;i--){
        for(int x=i;(i^x)<x;x=(x-1)&i){
            if(a[x]&&a[i^x])  mrg(x,i^x);
            if(!x)  break;
        }
        if(cnt==siz-1)  break;
    }
    printf("%lld\n",ans);
}