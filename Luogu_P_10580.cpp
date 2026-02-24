#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=1e5+10,mod=998244353;
int n,ans;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,int y){int res=1;while(y){if(y&1) res=1ll*res*x%mod;x=1ll*x*x%mod;y>>=1;}return res;}
}
using namespace FastMod;
// inline int lcm(int x,int y){return x/__gcd(x,y)*y;}
// void dfs(int x,int y){
//     if(x>n){
//         int g=a[1],l=a[1];
//         for(int i=2;i<=n;i++){
//             g=__gcd(g,a[i]);
//             l=lcm(l,a[i]);
//         }
//         ans+=(g==1&&y%l==0);
//         return;
//     }
//     for(int i=1;i<=y;i++){
//         a[x]=i;
//         dfs(x+1,y);
//     }
// }
int f[33];  // f[i] 表示 gcd=1,lcm=x^i 的方案数
vector<pii> fac;
void MakeFactors(int x){
    fac.clear();
    for(int i=2;i*i<=x;i++){
        if(x%i==0){
            int k=0;
            while(x%i==0){x/=i;k++;}
            fac.eb(i,k);
        }
    }
    if(x^1) fac.eb(x,1);
}
void solve(){
    ans=0;
    int x,y;
    scanf("%d%d%d",&x,&y,&n);
    if(y%x)  return puts("0"),void();
    y/=x;
    MakeFactors(y);
    f[0]=1;int sum=1,ans=1;
    for(int i=1;i<=30;i++){
        f[i]=imdel(qpow(i+1,n),qpow(i,n));mdel(f[i],sum);
        madd(sum,f[i]);
    }
    for(int l=0;l<fac.size();l++)   mmul(ans,f[fac[l].se]);
    printf("%d\n",ans);
}
int main(){
    // freopen("totoro.in","r",stdin);freopen("totoro.out","w",stdout);
    // srand(time(0));
    // puts("100");
    // for(int i=1;i<=100;i++){
    //     int n=rand()%8+1,x=rand()%100+1,y=x*(rand()%10+1);
    //     printf("%d %d %d\n",n,x,y);
    // }
    int T;
    scanf("%d",&T);
    while(T--)solve();
}