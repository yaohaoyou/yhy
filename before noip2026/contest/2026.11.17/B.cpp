#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
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
const int maxn=210,mod=1e9+7;
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
bool mem1;
mit pq[maxn];
int n,m,k;
piii a[maxn];
int b[maxn];
mit f[maxn][maxn][maxn],g[maxn][maxn][maxn];
void discrete(){
    k=0;for(int i=1;i<=n;i++)b[++k]=a[i].fi.fi,b[++k]=a[i].fi.se;
    sort(b+1,b+k+1);k=unique(b+1,b+k+1)-b-1;
    for(int i=1;i<=n;i++)   a[i].fi.fi=lower_bound(b+1,b+k+1,a[i].fi.fi)-b,a[i].fi.se=lower_bound(b+1,b+k+1,a[i].fi.se)-b;
}
bool mem2;
void matt(int _cases){
    mems(f,0);mems(g,0);
    scanf("%d%d",&m,&n);
    pq[0]=1;for(int i=1;i<=n+5;i++)pq[i]=pq[i-1]*2;
    bool f1=0,fm=0;
    for(int i=1;i<=n;i++)   scanf("%d%d%d",&a[i].fi.fi,&a[i].fi.se,&a[i].se),f1|=a[i].fi.fi==1,fm|=a[i].fi.se==m;
    if(m==1){
        int c[2]={};
        for(int i=1;i<=n;i++)c[a[i].se-1]++;
        printf("%d\n",pq[c[1]+1]-2+pq[c[1]]*(pq[c[0]]-1));
        return;
    }
    if(!f1||!fm)    return puts("0"),void();
    discrete();
    sort(a+1,a+n+1);
    f[0][1][1]=g[0][1][1]=1;
    for(int i=1,cnt=0;i<=n;i++){
        if(a[i].se==1&&a[i].fi.fi==1){
            // 表示走 0 步到 1，走 1 步到 x
            int x=a[i].fi.se;
            f[0][1][x]+=pq[cnt];
            g[0][1][x]+=pq[cnt];
            cnt++;
        }
    }
    // printf("%d %d %d\n",b[1],a[1].fi.fi,a[1].fi.se);
    for(int i=0;i<=k;i++){
        for(int j=i;j<=k;j++)for(int r=j;r<=k;r++)if(f[i][j][r]||g[i][j][r]){
            vector<int> v;int cnt=0;
            for(int x=1;x<=n;x++)if((a[x].fi.fi>i&&a[x].fi.fi<=j&&a[x].se==2)||(a[x].fi.fi>j&&a[x].fi.fi<=r&&a[x].se==1)){
                if(a[x].fi.se>r)v.eb(x);
                else    cnt++;
            }
            sort(v.begin(),v.end(),[&](int x,int y){return a[x].fi.se<a[y].fi.se;});
            for(int o=0;o<v.size();o++){
                f[j][r][a[v[o]].fi.se]+=(f[i][j][r]+g[i][j][r])*pq[o+cnt];
                g[j][r][a[v[o]].fi.se]+=g[i][j][r]*pq[o+cnt];
            }
            // (F[i],F[i+1],F[i+2])=(i,j,r) -> (F[i+1],F[i+2],F[i+3])=(j,r,r)
            if((r^k)&&((i^j)||(j^r))){
                f[j][r][r]+=(f[i][j][r]+g[i][j][r])*pq[cnt];
                g[j][r][r]+=g[i][j][r]*pq[cnt];
            }
        }
    }
    mit ans=0;
    for(int i=0;i<=k;i++){
        int x=0;
        for(int o=1;o<=n;o++)if(a[o].se==2&&a[o].fi.fi>i)x++;
        for(int j=i;j<=k;j++)if(f[i][j][k]){
            int y=0;
            for(int o=1;o<=n;o++)if(a[o].se==1&&a[o].fi.fi>j)y++;
            // printf("add %d %d %d : %d\n",i,j,k,f[i][j][k]*pq[x+y]);
            ans+=f[i][j][k]*pq[x+y];
        }
    }
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}