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
int n;
namespace Graph{
    const int maxm=maxn<<1;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=0;}
}
using namespace Graph;
int L[maxn],R[maxn],rnk[maxn],tot;
void dfs(int u,int ft){L[u]=++tot;rnk[tot]=u;go(u,i)if(t^ft)dfs(t,u);R[u]=tot;}
void divide(int l,int r,vector<int> vec){
    // printf("\n[%d,%d]\n",l,r);
    if(l==r){for(int i:vec)printf("=%d",i);return;}
    int mid=(l+r)>>1;
    vector<int> v,vl,vr;
    for(int i:vec){
        if(R[i]<=mid)    vl.eb(i);
        else if(L[i]>mid)   vr.eb(i);
        else    v.eb(i);
    }
    sort(v.begin(),v.end(),[&](int x,int y){return L[x]==L[y]?R[x]>R[y]:L[x]<L[y];});
    int pl=l,pr=r,cur=0;
    for(int u:v){
        while(pl<L[u])  printf("+%d",rnk[pl++]),cur++;
        while(pr>R[u])  printf("+%d",rnk[pr--]),cur++;
        printf("=%d",u);
    }
    while(cur--)printf("-");
    if(!vl.empty()){
        cur=0;
        pr=r;while(pr>mid)printf("+%d",rnk[pr--]),cur++;
        divide(l,mid,vl);
        while(cur--)printf("-");
    }
    if(!vr.empty()){
        cur=0;
        pl=l;while(pl<=mid)printf("+%d",rnk[pl++]),cur++;
        divide(mid+1,r,vr);
        while(cur--)printf("-");
    }
}
void matt(){
    tot=0;rebuild();
    for(int i=2;i<=n;i++){int x;scanf("%d",&x);adde(i,x);}
    dfs(1,0);
    vector<int> all;for(int i=1;i<=n;i++)all.eb(i);
    // for(int i=1;i<=n;i++)   printf("%d %d\n",L[i],R[i]);
    divide(1,n,all);
    puts("!");
}
int main(){while(~scanf("%d",&n))matt();}