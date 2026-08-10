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
const int maxn=1e6+10,mod=998244353;
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
int n;
char s[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=1e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y||x<0||y<0?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline int f(int a,int b){int res=0;for(int i=0;i<=b;i++)madd(res,C(i+i+a,i));return res;}
int a,b,fab,gab; // fab=f(a,b),gab=f(a-1,b)
inline int F(int x,int y){
    if(y<0) return 0;
    while(a<x){
        int t=imdel(fab,gab);
        madd(t,C(b+b+a+1,b));
        gab=fab;fab=t;
        a++;
    }
    while(a>x){
        mdel(fab,C(b+b+a,b));
        int t=imdel(gab,fab);
        fab=gab;gab=t;
        a--;
    }
    while(b<y)  madd(fab,C(b+b+2+a,b+1)),madd(gab,C(b+b+1+a,b+1)),b++;
    while(b>y)  mdel(fab,C(b+b+a,b)),mdel(gab,C(b+b+a-1,b)),b--;
    return fab;
}
void matt(int _cases){
    scanf("%d",&n);scanf("%s",s+1);
    int x=0,y=0,ans=0;
    a=b=1;fab=f(a,b);gab=f(a-1,b);
    for(int i=1;i<=n;i++){
        if(s[i]=='(')   x++;
        else    y++;
        if(x==y)    madd(ans,1);
        if(s[i]==')')   madd(ans,F(2*x+2-i,n/2-x-1));
    }
    x=y=0;
    a=b=1;fab=f(a,b);gab=f(a-1,b);
    for(int i=1;i<=n;i++){
        if(s[i]=='(')   x++;
        else    y++;
        if(s[i]==')')   mdel(ans,F(2*x+4-i,n/2-x-2));
    }
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%*d%d",&T);for(int i=1;i<=T;i++)matt(i);}