#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e6+10,mod=998244353;
int inv2;
int n,m;
int ans;
int fac[maxn],inv[maxn];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace MyMod;
void init(){
    inv2=qpow(2,mod-2);
    fac[0]=1;
    for(int i=1;i<=maxn-10;i++)fac[i]=immul(fac[i-1],i);
    inv[maxn-10]=qpow(fac[maxn-10],mod-2);
    for(int i=maxn-11;~i;i--)   inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y||x<0?0:1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int S(int x,int y){int res=0;for(int i=0;i<=y;i++)madd(res,C(x,i));return res;}
int pl,pr,res1=1,res2=1;
int main(){
    freopen("game.in","r",stdin);freopen("game.out","w",stdout);
    init();
    scanf("%d%d",&n,&m);
    if(n==m)    return puts("1")&0;
    for(int i=0;i<=min(m,(n-1)/2);i++){
        int l=m-i-min(m-i,n-2*i-1)-1,r=m-i-max(0,m-i-i);
        res1=(2ll*res1-C(i-1,pl)+mod)%mod;res2=(2ll*res2-C(i-1,pr)+mod)%mod;
        if(l>r) continue;
        while(pl<l) madd(res1,C(i,++pl));
        while(pl>l) mdel(res1,C(i,pl--));
        while(pr<r) madd(res2,C(i,++pr));
        while(pr>r) mdel(res2,C(i,pr--));
        // while(pl<l) res=(2ll*res-C(pl++,pr)+mod)%mod;
        // while(pl>l) res=1ll*(res+C(--pl,pr))*inv2%mod;
        madd(ans,imdel(res2,res1));
        // printf("[%d,%d] : %d vs %d\n",l,r,imdel(res2,res1),S(i,r)-S(i,l-1));
        // madd(res,imdel(S(i,r),S(i,l-1)));
    }
    for(int i=(n+1)/2;i<=m;i++) madd(ans,C(n-i-1,m-i));
    printf("%d\n",ans);
}