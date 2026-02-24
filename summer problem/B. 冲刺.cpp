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
const int maxn=4e6+10,maxp=4e6+10;
int n,q,k;
pii a[maxn];
int w[maxn],pt[maxn][2],sum[maxn];
int dis[maxp];
inline void gmx(int &x,int y){(x<y)&&(x=y);}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
inline int id(int x){return lower_bound(a+1,a+n+1,pii(x,0))-a-1;}
namespace Graph{
    const int maxm=1e8+10;
    #define go(x,i) for(int i=head[x],t=e[i].to,w=e[i].w;i;i=e[i].nxt,t=e[i].to,w=e[i].w)
    int cnt=1;
    int head[maxp];
    struct edge{int nxt,to,w;}e[maxm];
    inline void add(int u,int v,int w){e[++cnt]={head[u],v,w};head[u]=cnt;}
    inline void adde(int u,int v,int w){add(u,v,w);add(v,u,w);}
}
using namespace Graph;
int tot;
priority_queue<pii,vector<pii>,greater<pii>> pq;
bool vis[maxp];
void dijkstra(){
    mems(dis,0x3f);mems(vis,0);
    for(int i=1;i<=tot;i++)dis[i]=1e9,vis[i]=0;
    pq.ep(dis[pt[0][1]]=0,pt[0][1]);
    while(!pq.empty()){
        int u=pq.top().se;pq.pop();if(vis[u])continue;vis[u]=true;
        // printf("dis[%d] = %d\n",u,dis[u]);
        go(u,i){
            if(dis[t]>dis[u]+w){
                dis[t]=dis[u]+w;
                pq.ep(dis[t],t);
            }
        }
    }
}
int main(){
    // freopen("C:\\Users\\noi017\\Downloads\\problem_3338\\ex_data2.in","r",stdin);
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)   sum[i]=sum[i-1]+a[i].se;
    // for(int i=1;i<=n;i++)   debug("%d %d\n",a[i].fi,a[i].se);
    tot=0;
    for(int i=0;i<=n;i++)   pt[i][0]=++tot,pt[i][1]=++tot;
    if(n==1000) printf("tot = %d\n",tot),exit(0);
    a[0].fi=-2e9;
    while(q--){
        scanf("%d",&k);
        if(k>a[n].fi){
            puts("0");
            continue;
        }
        cnt=1;for(int i=1;i<=tot;i++)head[i]=0;
        for(int i=0;i<n;i++){
            adde(pt[i][0],pt[i+1][0],a[i+1].se);
            adde(pt[i][1],pt[i+1][1],a[i+1].se);
            add(pt[i][1],pt[i][0],0);
            int l=id(a[i].fi+1+k),r=id(a[i+1].fi+k);
            for(int j=l;j<=r;j++){
                add(pt[i][0],pt[j][1],sum[j]-sum[i]),add(pt[i][1],pt[j][0],0);
                // add(pt[j][1],pt[i][0],0),add(pt[j][0],pt[i][1],sum[j]-sum[i]);
            }
            l=id(a[i].fi+1-k),r=id(a[i+1].fi-k);
            for(int j=l;j<=r;j++){
                add(pt[i][0],pt[j][1],sum[i]-sum[j]),add(pt[i][1],pt[j][0],0);
            }
            // for(int j=a[i-1].fi+1;j<=a[i].fi;j++){
            //     int c=calc(j),p=id(j+k)-1;
            //     gmn(dp[id(j+k)][0],dp[i][1]);
            //     gmn(dp[id(j+k)][1],min(dp[i][0],dp[i][1])+c);
            //     p++;
            //     if(p>=i){
            //         for(int l=a[p-1].fi+1;l<=a[p].fi;l++)
            //             gmn(dp[id(l-k)][1],dp[i][1]+calc(l-k));
            //     }
            // }
            // printf("dp[%d] = %d %d\n",i,dp[i][0],dp[i][1]);
        }
        dijkstra();
        printf("%d\n",min(dis[pt[n][0]],dis[pt[n][1]]));
    }
}