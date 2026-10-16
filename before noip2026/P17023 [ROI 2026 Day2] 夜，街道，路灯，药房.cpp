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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=1e6+10,mod=1e9+7;
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
int n,m;
pii a[maxn],b[maxn];
bool bk[maxn];
int f[maxn][2],g[maxn];
int buc[3][maxn];
unordered_map<int,int> mp[maxn],m2[maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    int ans=0;
    for(int i=1;i<=n;i++){
        f[i][0]=f[i][1]=1;g[i]=1;
        if(a[i].fi>=a[i].se)madd(f[i][0],buc[0][a[i].fi-a[i].se]);
        madd(f[i][1],buc[1][a[i].fi]);
        if(mp[a[i].fi].count(a[i].se))madd(g[i],mp[a[i].fi][a[i].se]);
        if(m2[a[i].fi].count(a[i].se))madd(g[i],m2[a[i].fi][a[i].se]);
        madd(buc[1][a[i].fi+a[i].se],f[i][1]);madd(mp[a[i].fi+a[i].se][a[i].se],g[i]);
        madd(buc[0][a[i].fi],f[i][0]);madd(buc[0][a[i].fi+a[i].se],f[i][1]);

        if(a[i].fi==a[i-1].fi){
            if(a[i-1].se>a[i].se)   swap(a[i-1],a[i]);
            {
                int w=a[i-1].fi>=a[i-1].se?buc[0][a[i-1].fi-a[i-1].se]:0;madd(w,1);
                madd(f[i][1],w);
                madd(buc[0][a[i].fi+a[i].se],w);
                madd(buc[1][a[i].fi+a[i].se],w);
            }
            if(a[i].se^a[i-1].se){
                int w=a[i].fi>=a[i].se?buc[0][a[i].fi-a[i].se]:0;madd(w,1);
                madd(f[i][1],w);
                madd(buc[0][a[i-1].fi+a[i-1].se],w);
                madd(buc[1][a[i-1].fi+a[i-1].se],w);
            }
            if(a[i].se^a[i-1].se){
                int w=a[i-1].fi>=a[i-1].se?mp[a[i-1].fi-a[i-1].se][a[i].se-a[i-1].se]:0;madd(w,1);
                if(a[i].fi>=a[i-1].se)madd(w,m2[a[i].fi-a[i-1].se][a[i].se-a[i-1].se]);
                madd(m2[a[i].fi+a[i].se][a[i].se-a[i-1].se],w);
                madd(g[i],w);
            }
            else{
                madd(g[i],a[i-1].fi>=a[i-1].se?mp[a[i-1].fi-a[i-1].se][a[i].se-a[i-1].se]:0);
            }
        }
        madd(ans,f[i][0]);madd(ans,f[i][1]);
        mdel(ans,g[i]);
        // printf("%d %d %d\n",g[i],f[i][0],f[i][1]);
    }
    printf("%d\n",ans);
}