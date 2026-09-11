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
const int maxn=2e5+10;
bool mem1;
int n;
bool f[maxn];
ll a[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+2,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]+=s;x+=lowbit(x);}}
    inline int que(int x){int res=0;while(x){res+=tr[x];x^=lowbit(x);}return res;}
    inline int query(int l,int r){return l>r?0:que(r)-que(l-1);}
    void clear(){for(int i=0;i<=n;i++)tr[i]=0;}
}T;
bool chk(int ps,int x){
    x=U.find(x);if(x>n)return false;
    ll now=a[ps];
    for(int i=ps;i;i--){
        if(!f[i]){
            if(i==ps)   T.add(x,-1),now-=T.query(x,n);
            else{
                now-=a[i];
                break;
            }
        }
        else{
            T.add(a[i],-1);
            now-=T.query(a[i],n);
        }
    }
    for(int i=ps;i;i--){
        if(!f[i]){
            if(i==ps)   T.add(x,1);
            else    break;
        }
        else T.add(a[i],1);
    }
    return now<=0;
}
bool mem2;
void matt(int _cases){
    T.clear();scanf("%d",&n);U.init();
    for(int i=1;i<=n;i++){char c[5];scanf("%s%lld",c,&a[i]);f[i]=c[0]=='p';if(f[i])U.merge(a[i]+1,a[i]);}
    // if(_cases==34){
    //     printf("%d\n",n);
    //     for(int i=1;i<=n;i++)   printf("%d %d\n",f[i],a[i]);
    // }
    for(int i=1;i<=n;i++)   T.add(i,1);
    for(int i=n;i;i--){
        if(f[i]){T.add(a[i],-1);continue;}
        int l=1,r=n,p=U[1];
        while(l<=r){
            int mid=(l+r)>>1;
            if(chk(i,mid))  p=mid,l=mid+1;
            else    r=mid-1;
        }
        a[i]=U[p];
        U.merge(a[i]+1,a[i]);
        T.add(a[i],-1);
    }
    for(int i=1;i<=n;i++)printf("%d ",a[i]);puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}