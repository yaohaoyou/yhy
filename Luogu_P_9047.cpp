#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10,B=350;
int n;
namespace Graph{
    #define go(u) for(auto [t,w]:son[u])
    vector<pii> son[maxn];
    inline void add(int u,int v,int w){son[u].eb(v,w);}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
ll dp[maxn][4];
inline void getmx(ll &x,ll y){(x<y)&&(x=y);}
ll(*g)[2] = new ll[B+B+2][2];
ll(*f)[2] = new ll[B+B+2][2];
void dfs(int u,int fa,int lst){
    random_shuffle(son[u].begin(),son[u].end());
    go(u){
        if(t==fa)   continue;   
        dfs(t,u,w);
    }
    memset(f,-0x3f,(B+B+2)*2*sizeof(ll));f[B][0]=0;
    go(u){
        if(t==fa)   continue;
        swap(f,g);memset(f,-0x3f,(B+B+2)*2*sizeof(ll));f[B][0]=0;
        for(int i=0;i<B+B;i++){
            for(bool j:{0,1}){
                getmx(f[i][j],g[i][j]+dp[t][0]);
                if(i)getmx(f[i-1][j],g[i][j]+dp[t][1]);
                getmx(f[i][!j],g[i][j]+dp[t][2]);
                if(i<B+B-1)getmx(f[i+1][j],g[i][j]+dp[t][3]);
            }
        }
    }
    if(u==1)    dp[u][0]=max(0ll,f[B][0]);
    else{
        dp[u][0]=max({0ll,f[B][0],f[B+1][0]+lst});
        dp[u][1]=max(0ll,f[B][0])+lst;
        dp[u][2]=f[B-1][0]+lst;
        dp[u][3]=f[B][1]+lst;
    }
}
int main(){
    srand(time(0));
    // freopen("monkey.in","r",stdin);freopen("monkey.out","w",stdout);
    scanf("%d",&n);
    for(int i=1,u,v,w;i<n;i++){
        scanf("%d%d%d",&u,&v,&w);
        adde(u,v,w);
    }
    dfs(1,0,0);
    printf("%lld\n",dp[1][0]);
}