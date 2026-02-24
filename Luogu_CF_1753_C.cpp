#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10,mod=998244353;
int c,n;
int cnt,x;
int a[maxn];
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
void solve(){
    scanf("%d",&n);
    if(n==-3)   freopen("D:\\yhy\\GDFZ_yhy\\9.18down\\color\\color3.in","r",stdin),scanf("%d%d",&c,&n);
    if(n==-4)   freopen("D:\\yhy\\GDFZ_yhy\\9.18down\\color\\color4.in","r",stdin),scanf("%d%d",&c,&n);
    cnt=x=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(!a[i]) cnt++;
    }
    for(int i=1;i<=cnt;i++)
        if(a[i])    x++;
    int s=(1ll*n*(n-1)/2)%mod,ans=0;
    for(int i=1;i<=x;i++)
        madd(ans,1ll*s*qpow(immul(x-i+1,x-i+1),mod-2)%mod);
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)solve();}