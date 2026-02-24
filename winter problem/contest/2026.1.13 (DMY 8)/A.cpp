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
const int maxn=1e5+10,maxm=30,mod=1e9+7;
bool mem1;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n,m,k;
int a[maxn],b[maxn],p[maxn],buc[maxn];
int len[maxm],sum[maxn],cnt[maxn];
int yuan,Iyuan[maxn];
int dp[maxm][maxm];
int siz[maxn];
int fac[maxn],inv[maxn],ff[maxn];
void init(){
    const int N=1e5;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    ff[1]=1;ff[2]=2;for(int i=3;i<=N;i++)ff[i]=immul(ff[i-2],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
struct DSU{
    int fa[maxn],edg[maxn];
    void init(){iota(fa+1,fa+n+1,1);fill(siz+1,siz+n+1,1);}
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    inline void merge(int x,int y){
        x=find(x);y=find(y);edg[x]++;if(x==y)return;
        siz[x]+=siz[y];fa[y]=x;edg[x]+=edg[y];
    }
    inline int operator[](int x){return find(x);}
}U;
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
bool can1=true,can0=true;
void solve1(){
    m=k;
    int ans=immul(fac[m],2);
    if(can1){
        for(int i=1;i<=n;i++)if(a[i]&&(!a[a[i]]))m--;
        dp[0][0]=1;
        for(int i=1;i<=m;i++){
            for(int j=0;j<=i;j++){
                dp[i][j]=dp[i-1][j];
                madd(dp[i][j],immul(j+1,dp[i-1][j+1]));
                if(j)madd(dp[i][j],dp[i-1][j-1]);
            }
        }
        mdel(ans,dp[m][0]);
        if(can0)    mdel(ans,1);
    }
    printf("%d\n",ans);
}
int ans,BEL;
int mem[maxn][maxm],g[maxn];
bool bk[maxn][maxm];
inline int f(int x,int y,int id){
    if(bk[x][id])return mem[x][id];
    int res=qpow(x,y);
    for(int i=1;i+i<=y;i++)madd(res,1ull*C(y,i+i)*ff[i+i-1]%mod*qpow(x,y-i)%mod);
    bk[x][id]=true;
    return mem[x][id]=res;
}
int mp[maxm];
bool mem2;
void dfs(int x,int y){
    if(x>k){
        BEL++;
        int res=yuan,mx=0;
        for(int i=1;i<=y;i++)   mx=max(mx,sum[i]);
        if(can1&&mx<=2) return madd(ans,1);
        for(int i=1;i<=y;i++)   mmul(res,fac[cnt[i]-1]),mp[i]=sum[i];
        sort(mp+1,mp+y+1);
        for(int l=1;l<=y;l++){
            int r=l+1;while(r<=y&&mp[l]==mp[r])r++;
            if(buc[mp[l]])  mmul(res,Iyuan[mp[l]]);
            mmul(res,f(mp[l],r-l+buc[mp[l]],r-l));
            l=r-1;
        }
        // for(int i=1;i<=n;i++)if(buc[i])mmul(res,f(i,buc[i]));
        madd(ans,res);
        return;
    }
    sum[y+1]=len[x];cnt[y+1]=1;
    dfs(x+1,y+1);
    sum[y+1]=cnt[y+1]=0;
    for(int i=1;i<=y;i++){
        sum[i]+=len[x];cnt[i]++;
        dfs(x+1,y);
        sum[i]-=len[x];cnt[i]--;
    }
}
void solve2(){
    m=0;
    for(int i=1;i<=n;i++)if(U[i]==i){
        if(U.edg[i]==siz[i])    buc[siz[i]]++;
        else len[++m]=siz[i];
    }
    g[0]=g[1]=1;
    for(int i=2;i<=n;i++)g[i]=imadd(g[i-1],immul(i-1,g[i-2]));
    for(int i=buc[1];i<=n&&i<=buc[1]+k;i++)  mem[1][i-buc[1]]=g[i],bk[1][i-buc[1]]=true;
    yuan=1;
    for(int i=1;i<=n;i++){
        if(buc[i]){
            int x=f(i,buc[i],0);mmul(yuan,x);
            Iyuan[i]=qpow(x,mod-2);
        }
        else Iyuan[i]=1;
    }
    dfs(1,0);
    printf("%d\n",ans);
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    init();
    scanf("%d%d",&n,&k);
    U.init();
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i])    U.merge(i,a[i]);
    }
    for(int i=1;i<=n;i++)if(a[i]&&(a[i]^i)){can0=false;break;}
    for(int i=1;i<=n;i++)if(a[i]&&a[a[i]]&&a[a[i]]!=i){can1=false;break;}
    solve1();
    solve2();
    debug("bel(%d) = %d\n",k,BEL);
}
// bel(12)=4213597