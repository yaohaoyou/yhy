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
#define id(x) (((x)-1)/B+1)
using namespace std;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10,dir[][2]={
    {0,1},{0,2},{0,-1},{0,-2},
    {1,0},{1,1},{1,2},{1,-1},{1,-2},
    {2,0},{2,1},{2,2},{2,-1},{2,-2},
    {-1,0},{-1,1},{-1,2},{-1,-1},{-1,-2},
    {-2,0},{-2,1},{-2,2},{-2,-1},{-2,-2},
};
int n,r,B;
pii a[maxn];
bool ans[maxn],vis[maxn];
int col[maxn];
struct PII{size_t operator()(const pii &x)const{return ((unsigned ll)x.fi<<20)|x.se;}};
unordered_map<pii,vector<int>,PII> cnt;
namespace Graph{
    const int maxm=maxn*100;
    #define go(x,i) for(int i=head[x],t=e[i].to;i;i=e[i].nxt,t=e[i].to)
    int tot=1;
    int head[maxn];
    struct edge{int nxt,to;}e[maxm];
    inline void add(int u,int v){e[++tot]={head[u],v};head[u]=tot;}
    inline void adde(int u,int v){add(u,v);add(v,u);}
    inline void rebuild(){for(int i=0;i<=n;i++)head[i]=0;tot=1;}
}
using namespace Graph;
inline ll sqr(int x){return 1ll*x*x;}
inline bool chk(pii x,pii y){return sqr(x.fi-y.fi)+sqr(x.se-y.se)<=sqr(r);}
bool flag;
void dfs(int u){
    if(ans[u])  return flag=true,void();
    go(u,i){
        if(!~col[t])col[t]=col[u]^1,dfs(t);
        else if(col[t]==col[u]) flag=true;
        if(flag)return;
    }
}
void dfs2(int u){
    ans[u]=true;vis[u]=true;
    go(u,i)if(!vis[t])dfs2(t);
}
int main(){
    freopen("eightfour.in","r",stdin);freopen("eightfour.out","w",stdout);
    scanf("%d%d",&n,&r);B=(r+1)/2;
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    // for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)if(chk(a[i],a[j]))assert(abs(id(a[i].fi)-id(a[j].fi))<=2&&abs(id(a[i].se)-id(a[j].se))<=2);
    // printf("%d\n",chk(a[60],a[61]));
    for(int i=1;i<=n;i++)   cnt[pii(id(a[i].fi),id(a[i].se))].eb(i);
    for(auto [i,vec]:cnt){
        // if(vec.size()==2){for(int j:vec)printf("%d ",j);puts("");}
        if(vec.size()>=3){for(int j:vec)ans[j]=true;continue;}
        int x=i.fi,y=i.se;
        for(int k=0;k<24;k++){
            int xx=x+dir[k][0],yy=y+dir[k][1];
            if(cnt.find(pii(xx,yy))!=cnt.end()){
                for(int u:vec){
                    for(int j:cnt[pii(xx,yy)]){
                        if(u^j&&chk(a[u],a[j])) adde(u,j);
                    }
                }
            }
        }
        if(vec.size()==2)   adde(vec.front(),vec.back());
    }
    mems(col,-1);
    for(int i=1;i<=n;i++){
        if(!~col[i]){
            flag=col[i]=0;
            dfs(i);
            if(flag)    dfs2(i);
        }
    }
    for(int i=1;i<=n;i++)   putchar(ans[i]+'0');
}