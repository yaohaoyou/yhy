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
const int maxn=1e3+10;
int n,m,k,k0;
int a[maxn][maxn],b[maxn][maxn],c[maxn][maxn],out[maxn][maxn];
struct DSU{
    int fa[maxn*maxn*2];
    void init(){iota(fa+1,fa+n*m*2+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){fa[find(y)]=find(x);}
    inline int operator[](int x){return find(x);}
}U;
inline int id(int x,int y){return (x-1)*m+y;}
void dfs(int i,int j){
    if(a[i][j]>=0&&(!~out[i][j+1])) out[i][j+1]=out[i][j]^a[i][j],dfs(i,j+1);
    if(b[i][j]>=0&&(!~out[i+1][j])) out[i+1][j]=out[i][j]^b[i][j],dfs(i+1,j);
    if(a[i][j-1]>=0&&(!~out[i][j-1]))   out[i][j-1]=out[i][j]^a[i][j-1],dfs(i,j-1);
    if(b[i-1][j]>=0&&(!~out[i-1][j]))   out[i-1][j]=out[i][j]^b[i-1][j],dfs(i-1,j);
}
void matt(int _cases){
    scanf("%d%d%d%d",&n,&m,&k,&k0);
    for(int i=0;i<=n+1;i++)for(int j=0;j<=m+1;j++)a[i][j]=b[i][j]=-1;
    for(int i=1;i<=k;i++){
        int x0,y0,x1,y1,o;scanf("%d%d%d%d%d",&x0,&y0,&x1,&y1,&o);
        if(x0>x1)   swap(x0,x1),swap(y0,y1);
        if(y0>y1)   swap(x0,x1),swap(y0,y1);
        if(y1==y0+1)    a[x0][y0]=o;
        else    b[x0][y0]=o;
    }
    for(int i=1;i<n;i++)
        for(int j=1;j<m;j++){
            if(a[i][j]>=0&&b[i][j]>=0&&a[i+1][j]>=0&&b[i][j+1]>=0)  c[i][j]=(a[i][j]+b[i][j]+a[i+1][j]+b[i][j+1])&1;
            else c[i][j]=0;
        }
    for(int i=1;i<n;i++){
        int res=0;
        vector<int> v;v.clear();
        for(int j=1;j<m;j++)if(c[i][j])v.eb(j);
        if(v.empty())   continue;
        if(v.size()&1)  v.eb(m);
        for(int j=0;j<v.size();j+=2)    res+=v[j+1]-v[j];
        if(res<=m/2){
            for(int j=0;j<v.size();j+=2){
                int l=v[j],r=v[j+1];
                for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
            }
            continue;
        }
        res=v[0];
        for(int j=1;j+1<v.size();j+=2)  res+=v[j+1]-v[j];
        assert(res<=m/2);
        {
            int l=0,r=v[0];
            for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
        }
        for(int j=1;j+1<v.size();j+=2){
            int l=v[j],r=v[j+1];
            for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
        }
        {
            int l=v.back(),r=m;
            for(int x=l+1;x<=r;x++)if(b[i][x]>=0)b[i][x]^=1;
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)out[i][j]=-1;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(!~out[i][j])out[i][j]=0,dfs(i,j);
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=m;j++)printf("%d",out[i][j]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}