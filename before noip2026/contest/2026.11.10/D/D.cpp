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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=6e5+10;
int n,m,q;
int a[maxn],b[maxn],c[maxn],d[maxn];
// unordered_set<int> v[maxn];
int H[maxn],B[maxn];
struct List{
    int pre[maxn],nxt[maxn];
    void init(){nxt[0]=m+1;pre[m+1]=0;}
    inline void eb(int x,int i){int y=pre[B[i]];nxt[y]=x;pre[x]=y;nxt[x]=B[i];pre[B[i]]=x;}
    inline void erase(int x){int pr=pre[x],nx=nxt[x];pre[nx]=pr;nxt[pr]=nx;}
    inline int nx(int x){return nxt[x];}
    inline int pr(int x){return pre[x];}
}ls;
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    while(q--){
        int x,bb;scanf("%d%d",&x,&bb);
        for(int i=1;i<=n;i++)   H[i]=m+i,B[i]=m+n+i,ls.nxt[H[i]]=B[i],ls.pre[B[i]]=H[i];
        b[x]=bb;
        for(int i=1;i<=m;i++)   ls.eb(i,b[i]);
        // printf("%d %d\n",ls.nx(H[1]),b[4]);
        // for(int i=1;i<=n;i++){
        //     for(int j=ls.nx(H[i]);j!=B[i];j=ls.nx(j))printf("%d ",j);
        //     puts("");
        // }
        cpy(d,b,m);
        int T=0;
        while((++T)<=n*1000+100){
            int p=(T-1)%n+1;bool fl=false;
            for(int i=ls.nx(H[p]);i!=B[p];i=ls.nx(i))c[i]=b[a[i]],fl=true;
            if(!fl) break;
            for(int i=ls.nx(H[p]);i!=B[p];){
                int N=ls.nx(i);
                if(b[i]^c[i]){
                    ls.erase(i);
                    b[i]=c[i];
                    ls.eb(i,b[i]);
                    // v[b[i]].ep(i);
                    // it=v[p].erase(it);
                }
                i=N;
            }
        }
        printf("%d\n",T<=n*2+100?T:-1);
        cpy(b,d,m);
    }
}