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
const int maxn=2e4+10,maxm=1e6+10;
struct poly{
    int k;
    vector<int> v;
    int& operator[](int x){return v[x];}
    inline void mul(int x,int y){
        k-=min(x,y);x=abs(x-y);
        if(!x)return;
        for(int i=1;i<=x;i++)v.eb(0);
        for(int i=v.size()-1;i>=x;i--)v[i]+=v[i-x];
    }
    inline void div(int x,int y){
        k+=min(x,y);x=abs(x-y);
        assert(v.size()>=x);
        if(!x)return;
        if(x==v.size()) return v={1},void();
        vector<int> res;res.resize(v.size()-x);
        for(int i=v.size()-1;i>=x;i--)res[i-x]=v[i],v[i-x]-=v[i];
        v.swap(res);
    }
    void print(){for(int i:v)printf("%d ",i);puts("");}
};
int n,m;
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n*2+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
void data(){
    srand(time(0));
    n=200;m=10000;
    printf("%d %d\n",n,m);n<<=1;
    for(int i=1;i<=m;i++)   printf("%d %d\n",rand()%n+1,rand()%n+1);
    exit(0);
}
pii a[maxm];
int ans[maxn];
poly now;
void mrg(int u,int v){
    if(U[u]==U[v]||U[u]==U[v+n])    return;
    int A0=0,A1=0,B0=0,B1=0;
    for(int i=1;i<=n;i++){
        if(U[i]==U[u])A0++;else if(U[i]==U[u+n])A1++;
        else if(U[i]==U[v])B0++;else if(U[i]==U[v+n])B1++;
    }
    poly tmp=now;
    tmp.div(A0,A1);
    tmp.div(B0,B1);
    tmp.mul(A0+B1,A1+B0);
    if(tmp.k<tmp.v.size()&&tmp[tmp.k]){
        U.merge(u,v+n);U.merge(u+n,v);
        now=tmp;
    }
    else{
        now.div(A0,A1);
        now.div(B0,B1);
        now.mul(A0+B0,A1+B1);
        U.merge(u,v);U.merge(u+n,v+n);
    }
}
int main(){
    // data();
    scanf("%d%d",&n,&m);n<<=1;
    for(int i=1;i<=m;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    U.init();
    now.v={1};now.k=n>>1;
    for(int i=1;i<=n;i++)   now.mul(1,0);
    for(int i=m;i;i--)  mrg(a[i].fi,a[i].se);
    for(int i=2;i<=n;i++)   mrg(1,i);
    for(int i=1;i<=n;i++)   printf("%d",U[i]==U[1]);
}