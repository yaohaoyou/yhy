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
const int maxn=1e6+10,B=470,mod=998244353;
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
const int inv2=qpow(2,mod-2);
int q;
struct ques{int n,m,id;}a[maxn];
int ans[maxn],fac[maxn],inv[maxn];
int now;
void init(){
    int N=maxn-10;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;}
inline void addn(int n,int m){mdel(now,C(m,n));}
inline void deln(int n,int m){madd(now,C(m,n+1));}
inline void delm(int n,int m){madd(now,C(m-1,n));mmul(now,inv2);}
inline void addm(int n,int m){mmul(now,2);mdel(now,C(m,n));}
int main(){
    init();
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        scanf("%d%d",&a[i].n,&a[i].m);
        ans[i]=imdel(qpow(2,a[i].n),1);a[i].n--;a[i].m--;swap(a[i].n,a[i].m);
        a[i].id=i;
    }
    sort(a+1,a+q+1,[&](ques x,ques y){return (x.n/B==y.n/B)?(x.m==y.m?0:((x.n/B)&1)^(x.m<y.m)):(x.n<y.n);});
    now=1;
    for(int i=1,l=0,r=0;i<=q;i++){
        int ql=a[i].n,qr=a[i].m;
        while(r<qr) addm(l,r++);
        while(l>ql) addn(l--,r);
        while(l<ql) deln(l++,r);
        while(r>qr) delm(l,r--);
        mmul(ans[a[i].id],now);
    }
    for(int i=1;i<=q;i++)   printf("%d\n",ans[i]);
}