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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10;
bool mem1;
int n;
int a[maxn],p[maxn];
vector<int> v[maxn];
struct DSU{
    int fa[maxn];
    void init(){iota(fa+1,fa+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
queue<int> q;
bool mem2;
void matt(int _cases){
    fll(p,0,n);for(int i=1;i<=n;i++)v[i].clear();
    scanf("%d",&n);
    U.init();
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),v[a[i]].eb(i);
    for(int i=1;i<=n;i++){
        for(int j:v[i])q.ep(j);
        if(q.empty())return puts("No"),void();
        p[i]=q.front();q.pop();
        U.merge(i,p[i]);
    }
    // for(int i=1;i<=n;i++)printf("%d ",U[i]);puts("");
    stack<int> stk;
    for(int i=1;i<=n;i++){
        while(!stk.empty()&&U[stk.top()]==U[i])stk.pop();
        if(!stk.empty()&&a[p[i]]<=stk.top())    U.merge(stk.top(),i),swap(p[i],p[stk.top()]),stk.pop();
        stk.ep(i);
    }
    vector<int> v;
    int u=1;do{v.eb(u);u=p[u];}while(u^1);
    reverse(v.begin(),v.end());
    if(v.size()==n){
        puts("Yes");
        for(int i:v)printf("%d ",i);
        puts("");
    }
    else    puts("No");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}