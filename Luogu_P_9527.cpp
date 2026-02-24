#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,l,q;
int a[maxn];
namespace Graph{
    int cnt;
    int head[maxn];
    struct edge{int nxt,to;}e[maxn<<1];
    inline void add(int u,int v){e[++cnt]={head[u],v};head[u]=cnt;}
}
using namespace Graph;
int f[maxn],dp[maxn][45];
inline void getmx(int &x,int y){(x<y)&&(x=y);}
void dfs(int u,int fa){
    f[u]=fa;
    for(int i=head[u];i;i=e[i].nxt){
        int t=e[i].to;
        if(t==fa)   continue;
        dfs(t,u);
    }
}
int main(){
    scanf("%d%d",&n,&l);
    for(int i=1,u,v;i<n;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        for(int j=0;j<=40;j++)  dp[i][j]=1;
    }
    scanf("%d",&q);
    while(q--){
        int opt,x,d,w;
        scanf("%d%d",&opt,&x);
        if(opt==1){
            scanf("%d%d",&d,&w);
            d++;
            while(d--){
                // printf("%d %d\n",x,d);
                if(!f[x]){
                    for(int i=d;~i;i--) dp[x][i]=1ll*dp[x][i]*w%l;
                    break;
                }
                dp[x][d]=1ll*dp[x][d]*w%l;
                if(d>=1) dp[x][d-1]=1ll*dp[x][d-1]*w%l;
                x=f[x];
                if(!x)  break;
            }
        }
        else{
            w=a[x];
            d=0;
            while(d<=40){
                w=1ll*w*dp[x][d]%l;
                // printf("**%d %d\n",x,w);
                x=f[x];
                if(!x)  break;
                d++;
            }
            printf("%d\n",w);
        }
    }
}