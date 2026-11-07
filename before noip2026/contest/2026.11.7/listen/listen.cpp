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
const int maxn=5e5+10;
int n,q;
int deg[maxn],to[maxn],bel[maxn];
vector<int> v[maxn],son[maxn];
struct hsh{
    size_t operator()(const pii &x)const{return ((ll)x.fi<<30)^x.se;}
};
unordered_multiset<pii,hsh> st;
bool used[maxn];
struct DSU{
    int fa[maxn],cir[maxn];
    void init(){iota(fa+1,fa+n+1,1);fll(cir,0,n);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){x=find(x);y=find(y);if(x==y)cir[x]=true;else cir[x]|=cir[y],fa[y]=x;}
    inline int operator[](int x){return find(x);}
}U;
bool mem2;
void solve(){
    for(auto [x,y]:st)deg[x]++,deg[y]++;
    int mex=0;while(deg[mex]>=2)mex++;
    U.init();
    for(auto [x,y]:st){
        if(y<mex)to[x]=y;
        else son[x].eb(y);
        if(x<mex)to[y]=x;
        else son[y].eb(x);
        if(x<mex&&y<mex)U.merge(x,y);
    }
    for(int i=0;i<mex;i++){
        int x=U[i];
        if(U.cir[x])deg[i]=1e9;
        else    v[x].eb(i);
    }
    int x=mex;
    while(true){
        if(!deg[x]) break;
        if(deg[x]==1){
            if((~to[x])&&deg[to[x]]<=1)   break;
            if(~to[x]){
                for(int j:v[U[to[x]]])deg[j]--;
            }
            for(int j:son[x])deg[j]--;
        }
        x++;
    }
    // printf("%d %d\n",x,mex);
    printf("%d\n",x+mex);
    for(auto [x,y]:st)  deg[x]=deg[y]=0,to[x]=to[y]=-1,son[x].clear(),son[y].clear();
    for(int i=0;i<mex;i++)  v[i].clear();
}
int a[maxn],b[maxn];
bool A[100],B[100];
int main(){
    // freopen("listen.in","r",stdin);freopen("listen.out","w",stdout);
    mems(to,-1);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++){
        int x,y;scanf("%d%d",&x,&y);
        gmn(x,maxn-1);gmn(y,maxn-1);
        a[i]=x;b[i]=y;
        st.ep(x,y);
    }
    // if(n<=20&&!q){
    //     int ans=0,mx=0;pii res;
    //     for(int i=0;i<(1<<n);i++){
    //         mems(A,0);mems(B,0);
    //         for(int j=1;j<=n;j++)if(i&(1<<j-1))A[a[j]]=B[b[j]]=true;else A[b[j]]=B[a[j]]=true;
    //         int x=0,y=0;
    //         while(A[x])x++;while(B[y])y++;
    //         // printf("%d %d\n",x,y);
    //         gmx(mx,min(x,y));
    //         if(ans<x+y) ans=x+y,res=pii(x,y);
    //     }
    //     // printf("(%d,%d) %d\n",res.fi,res.se,mx);
    //     printf("%d\n",ans);
    //     return 0;
    // }
    solve();
    while(q--){
        char c[5];int x,y;scanf("%s%d%d",c,&x,&y);
        gmn(x,maxn-1);gmn(y,maxn-1);
        if(c[0]=='+')   st.ep(x,y);
        else    st.erase(st.find(pii(x,y)));
        solve();
    }
    // int ans=0,mx=0;pii res;
    // for(int i=0;i<(1<<n);i++){
    //     mems(A,0);mems(B,0);
    //     for(int j=1;j<=n;j++)if(i&(1<<j-1))A[a[j]]=B[b[j]]=true;else A[b[j]]=B[a[j]]=true;
    //     int x=0,y=0;
    //     while(A[x])x++;while(B[y])y++;
    //     // printf("%d %d\n",x,y);
    //     gmx(mx,min(x,y));
    //     if(ans<x+y) ans=x+y,res=pii(x,y);
    // }
    // // printf("(%d,%d) %d\n",res.fi,res.se,mx);
    // assert(min(res.fi,res.se)==mx&&mex==mx);
    // if(min(res.fi,res.se)^mx)   return 0;
    // if(mex^mx)  return 0;
    // printf("%d\n",ans);
}