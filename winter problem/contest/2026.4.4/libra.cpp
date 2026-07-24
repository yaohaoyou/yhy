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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=25,maxN=(1<<20)+10,mod=1e9+7;
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
bool mem1;
int n;
int a[maxn],f[2][maxN],g[2][maxN];
ll sum[maxN];
int cnt;
vector<int> v[maxN];
unordered_map<ll,int> id;
inline int calc(int x){return 1ull*x*(x+1)/2%mod;}
inline void ins(ll x){if(!id.count(sum[x]))id[sum[x]]=++cnt;v[id[sum[x]]].eb(x);}
inline void upd(int o,int s,int ope){
    int ppc=__builtin_popcount(ope);
    if(f[!o][s]+ppc<f[o][s^ope])    f[o][s^ope]=f[!o][s]+ppc,g[o][s^ope]=0;
    if(f[!o][s]+ppc==f[o][s^ope])   madd(g[o][s^ope],immul(g[!o][s],calc(ppc)));
}
int ans;
bool b[maxN];
void dfs(int x){
    int c=0;
    for(int i=1;i<=n;i++)if(!b[a[i]+100])c++,b[a[i]+100]=true;
    for(int i=1;i<=n;i++)b[a[i]+100]=false;
    // if(c>n-x+1)   return;
    if(x==n){
        ans+=c==1;
        return;
    }
    for(int i=1;i<=n;i++)for(int j=i;j<=n;j++)for(int k=-10;k<=10;k++){
        if(!k)  continue;
        for(int l=i;l<=j;l++)   a[l]+=k;
        dfs(x+1);
        for(int l=i;l<=j;l++)   a[l]-=k;
    }
}
bool mem2;
int main(){
    freopen("libra.in","r",stdin);freopen("libra.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=n;i>1;i--)    a[i]-=a[i-1];
    int id1;
    {
        int x=a[1];
        sort(a+1,a+n+1);
        id1=lower_bound(a+1,a+n+1,x)-a;
    }
    for(int i=1;i<=n;i++)   debug("%d ",a[i]);debug("\n");
    for(int s=0;s<(1<<n);s++)
        for(int i=0;i<n;i++)if(s&(1<<i))sum[s]+=a[i+1];
    mems(f,0x3f);
    f[0][0]=0;g[0][0]=1;
    for(int i=1;i<=n;i++){
        const int N=(1<<i)-1;const bool o=i&1;
        mems(f[o],0x3f);mems(g[o],0);
        if(id.count(-a[i])){
            const int ID=id[-a[i]];
            for(int j:v[ID]){
                for(int s=0;s<=N>>1;s++)if((s&j)==j)upd(o,s,j);
            }
        }
        if(a[i]){
            for(int s=0;s<=N>>1;s++)f[o][s|(1<<i-1)]=f[!o][s],g[o][s|(1<<i-1)]=g[!o][s];
        }
        else    memc(f[o],f[!o]),memc(g[o],g[!o]);
        for(int s=0;s<=N>>1;s++)    ins(s|(1<<i-1));
        // for(int j=0;j<=N;j++)if(g[o][j])printf("%d %d : %d %d %d\n",i,j,f[o][j],g[o][j],__builtin_popcount(j));puts("");
    }
    const int N=(1<<n)-1;
    int mn=1e9,ans=0;
    for(int i=0;i<=N;i++){
        int ppc=__builtin_popcount(i);
        int w=f[n&1][i]+ppc-bool(i&(1<<id1-1));
        if(w<mn)    mn=w,ans=0;
        if(w==mn)   madd(ans,immul(g[n&1][i],calc(ppc-1)));
    }
    for(int i=1;i<=mn;i++)  mmul(ans,i);
    printf("%d\n%d\n",mn,ans);
}