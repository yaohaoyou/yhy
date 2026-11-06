#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pim pair<int,mit>
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
const int maxn=5e4+10,maxv=1e5+10,maxe=1e4+10,mod=1234567;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int n,m;
namespace Graph{
    const int maxm=maxn;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int cnt=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;cnt=1;}
}
using namespace Graph;
vector<int> v[maxn];
vector<pii> h[maxn][5];
int lst[5][maxv];
int pq[10];
mit ans;
void dfs(int u){
    // mit f[5][maxe];
    vector<int> f[5];
    for(int i=0;i<5;i++)f[i].resize(pq[i]);
    vector<mit> F(v[u].size()),G(v[u].size());
    for(int i=0;i<10;i++)   f[1][i]=1;
    for(int i=0;i<v[u].size();i++)  F[i]=mod-1;
    vector<pii> g[5];
    go(u,_){
        dfs(t);
        for(int i=1;i<5;i++){
            g[i].clear();
            for(int j=0;j<pq[i];j++)if(f[i][j])g[i].eb(j,f[i][j]),f[i][j]=0;
        }
        for(int i=0;i<v[u].size();i++)  G[i]=F[i],F[i]=0;
        for(int j=0;j<5;j++)for(auto [y,ft]:h[t][j]){
            for(int i=1;i<j;i++)for(auto [x,fu]:g[i])if(lst[i][y]==x)f[j][y]=(f[j][y]+1ull*fu*ft)%mod;
            for(int i=j;i<5;i++)for(auto [x,fu]:g[i])if(lst[j][x]==y)f[i][x]=(f[i][x]+1ull*fu*ft)%mod;
            for(int i=0;i<v[u].size();i++)if(lst[j][v[u][i]]==y)F[i]+=G[i]*ft;
        }
    }
    for(int i=1;i<5;i++)for(int x=0,y=0;x<pq[i];y++){
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
        if(f[i][x])(f[i-1][y]+=f[i][x])%=mod,f[i][x]=0;x++;
    }
    for(int i=0;i<v[u].size();i++)  f[4][v[u][i]/10]+=F[i],F[i]=0;
    for(int i=0;i<5;i++){
        for(int x=0;x<pq[i];x++)if(f[i][x])h[u][i].eb(x,f[i][x]);
    }
    if(!u)  ans-=f[0][0];
}
bool mem2;
int main(){
    // freopen("code.in","r",stdin);freopen("code.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    pq[0]=1;for(int i=1;i<=8;i++)pq[i]=pq[i-1]*10;
    for(int i=0;i<pq[5];i++)for(int j=0;j<5;j++)lst[j][i]=i%pq[j];
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++){int x;scanf("%d",&x);add(x,i);}
    for(int i=1;i<=m;i++){
        int x,y=0;char s[10];scanf("%d%s",&x,s);
        for(int j=4;~j;j--)y=y*10+s[j]-'0';
        v[x].eb(y);
    }
    for(int i=0;i<n;i++)    sort(v[i].begin(),v[i].end()),v[i].erase(unique(v[i].begin(),v[i].end()),v[i].end());
    ans=1;for(int i=1;i<=n;i++)ans*=10;
    dfs(0);
    printf("%d\n",ans);
}