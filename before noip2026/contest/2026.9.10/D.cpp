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
const int maxn=2000+10;
int n;
int p[maxn];
pii a[maxn];
int g[maxn][maxn];
bool G[maxn][maxn];
// vector<int> son[maxn];
vector<piii> vec;
// inline void adde(int u,int v){son[u].eb(v);son[v].eb(u);}
inline void adde(int u,int v){G[u][v]=G[v][u]=1;}
int col[maxn];
bool chk(){
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)if(G[i][j])
            for(int k=j+1;k<=n;k++)if(G[i][k]&&G[j][k])
                for(int l=k+1;l<=n;l++)if(G[i][l]&&G[j][l]&&G[k][l])return false;
    return true;
}
int get(int x){
    bool c[4]={0,0,0,0};
    for(int i=1;i<=n;i++)if(G[x][i])c[col[i]]=true;
    if(!c[1])   return 1;
    if(!c[2])   return 2;
    if(!c[3])   return 3;
    return 0;
}
bool dfs(int x){
    for(int i=1;i<=n;i++)if(G[x][i]){
        if(col[x]==col[i])  return false;
        if(!col[i]){
            col[i]=get(i);
            if(!col[i]||!dfs(i)) return false;
        }
    }
    return true;
}
int suf[maxn];
int ans,res,cnt;
void dfs(int x,int s){
    cnt++;if(cnt%100000){
        if(clock()/CLOCKS_PER_SEC>0.7)  exit(printf("%d\n",ans+res)&0);
    }
    if(x==vec.size())   return gmx(res,s);
    if(s+suf[x]<=res)    return;
    auto [u,v]=vec[x].se;
    if(G[u][v]) return dfs(x+1,s);
    adde(u,v);
    if(chk())   dfs(x+1,s+vec[x].fi);
    G[u][v]=G[v][u]=false;
    dfs(x+1,s);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]);
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            for(int k=i;k<=j;k++)   a[k]=pii(p[k],k);
            sort(a+i,a+j+1,greater<pii>());
            adde(a[i].se,a[i+1].se);
            if(j-i+1>=3){
                int x=a[i].se,y=a[i+1].se,z=a[i+2].se;
                if((x<=z&&z<=y)||(y<=z&&z<=x))  ans++;
                else    g[min({x,y,z})][max({x,y,z})]++;
            }
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(g[i][j])vec.eb(g[i][j],pii(i,j));
    sort(vec.begin(),vec.end(),greater<piii>());
    for(int i=vec.size()-1;~i;i--)    suf[i]=(i+1==vec.size()?0:suf[i+1])+vec[i].fi;
    dfs(0,0);
    // for(auto [w,e]:vec){
    //     int u=e.fi,v=e.se;
    //     // printf("%d %d %d\n",u,v,w);
    //     if(G[u][v]){ans+=w;continue;}
    //     adde(u,v);
    //     if(chk())  ans+=w;
    //     else    G[u][v]=G[v][u]=false;
    // }
    printf("%lld\n",ans+res);
}