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
const int maxn=100,mod=998244353;
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
const int inv3=qpow(3,mod-2);
int n,m,ans;
int p[maxn],q[maxn],a[maxn];
void dfs(int x){
    if(x>n){
        int sa=accumulate(a+1,a+n+1,0);
        if(!sa)    return;
        int P=0,Q=0,k=1;
        for(int i=1;i<=n;i++)if(a[i]){
            if(a[i]==1||a[i]==2)    mmul(k,3);
            madd(P,immul(p[i],immul(a[i],inv3)));
            madd(Q,immul(q[i],immul(a[i],inv3)));
        }
        int x=imdel(1,P);x=qpow(x,m-1);mmul(x,imdel(1,Q));
        x=qpow(imdel(1,x),mod-2);mmul(x,k);
        if(sa&1)    madd(ans,x);
        else mdel(ans,x);
        return;
    }
    for(int i=0;i<4;i++){
        a[x]=i;
        dfs(x+1);
    }
}
int main(){
    freopen("carddraw.in","r",stdin);freopen("carddraw.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&q[i]);
    dfs(1);
    printf("%d\n",ans);
}