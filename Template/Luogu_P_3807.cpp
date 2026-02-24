//  P3807 【模板】卢卡斯定理/Lucas 定理
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=3e5+10;
int n,m,p;
int fac[maxn],inv[maxn];
inline int qpow(int x,int y){
    int res=1;
    while(y){
        if(y&1)	res=1ll*res*x%p;
        x=1ll*x*x%p;
        y>>=1;
    }
    return res;
}
inline void init(){
    fac[0]=inv[0]=1;
    for(int i=1;i<maxn;i++)   fac[i]=1ll*fac[i-1]*i%p;
    for(int i=1;i<maxn;i++)   inv[i]=qpow(fac[i],p-2);
    // for(int i=min(p-2,n-2);~i;i--)   inv[i]=1ll*inv[i+1]*(i+1)%p;
}
inline int C(int x,int y){return x<y?0:1ll*fac[x]*inv[y]%p*inv[x-y]%p;}
inline int Lucas(int x,int y){
    if(!x||!y)  return 1;
    return 1ll*C(x%p,y%p)*Lucas(x/p,y/p)%p;
}
void solve(){
    scanf("%d%d%d",&n,&m,&p);
    // swap(n,m);
    // n+=m;
    init();
    // printf("%d %d\n",n,m);
    // printf("%d %d\n",n,C(4,2));
    printf("%d\n",Lucas(n+m,n));
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) solve();
}