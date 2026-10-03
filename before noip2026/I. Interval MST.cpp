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
bool mem1;
const int maxn=2e6+10;
int n,q;
int a[maxn];
vector<int> c[maxn];
piii b[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        for(int i=1;i<=n;i++)c[i].clear();
        int m=0;pii mx=pii(a[l],l);ll ans=0;
        // c[l]=a[l];
        for(int i=l+1;i<=r;i++){
            if(a[i]>mx.fi){
                c[mx.se].eb(a[i]);
                // c[mx.se]=a[i];
                ans+=a[i]-mx.fi;
            }
            else{
                c[mx.se].eb(a[i]);
                ans+=a[i]-mx.fi;
                for(int j=l;j<i;j++){
                    for(int &k:c[j])
                    if(k>a[i]){
                        ans-=k-a[i],k=a[i];
                    }
                }
            }
            mx=max(mx,pii(a[i],i));
            for(int j=l;j<i;j++){
                for(int k:c[j]) printf("%d,",k);
                printf(" ");
            }
            printf("\n%d\n",ans);
            // for(int j=l;j<i;j++)printf("%d ",c[j]-a[j]);puts("");
            // printf("%d\n",ans);
            // if(i>l){
                // int j=max_element(a+l,a+i)-a;
                // b[++m]=piii(a[i]-a[j],pii(i,j));
            // }
            // if(i<r){
                // int j=min_element(a+i+1,a+r+1)-a;
                // b[++m]=piii(a[j]-a[i],pii(j,i));
            // }
            // for(int j=l;j<i;j++)
            //     b[++m]=piii(a[i]-a[j],pii(i,j));
        }
        // sort(b+1,b+m+1);
        // U.init();
        // int ans=0;
        // for(int i=1;i<=m;i++){
        //     int u=b[i].se.fi,v=b[i].se.se,w=b[i].fi;
        //     // printf("%d %d %d\n",u,v,w);
        //     u=U[u];v=U[v];
        //     if(u==v)    continue;
        //     // puts("pick");
        //     U.merge(u,v);ans+=w;
        // }
        printf("%lld\n",ans);
    }
}