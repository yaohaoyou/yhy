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
const int maxn=2e6+10,mod=998244353;
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
int n,m;
pii a[maxn],b[maxn];
int fac[maxn],inv[maxn];
void init(){
    const int N=2e6;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
bool mem2;
void matt(int _cases){
    scanf("%d",&n);m=0;
    int cl=0,cr=0,sl=0,sr=0,s=0;
    for(int i=1;i<=n;i++){
        int l,r;scanf("%d%d",&l,&r);
        a[i]=pii(l,r);
        b[++m]=pii(l,-i);b[++m]=pii(r,i);
        cr++;madd(sr,l+r);
    }
    sort(b+1,b+m+1);
    int ans=0;
    for(int i=1;i<=m;i++){
        if(b[i].se<0){
            int x=-b[i].se;
            cr--;mdel(sr,a[x].fi+a[x].se);
            int w=qpow(2,n-1-cr-cl),al=0,res=0;
            res=immul(C(cl+cr-1,cr),sr);
            mdel(res,immul(C(cl+cr-1,cl),sl));
            al=C(cl+cr,cl);
            // for(int j=1;j<=cl&&j<=cr;j++){
                // madd(res,1ull*C(cr-1,j-1)*C(cl,j)%mod*sr%mod);
                // mdel(res,1ull*C(cl-1,j-1)*C(cr,j)%mod*sl%mod);
                // madd(al,immul(C(cl,j),C(cr,j)));
            // }
            madd(res,immul(al,a[x].se-a[x].fi));
            if(s&&al)   mmul(al,qpow(2,n-2-cr-cl));
            mmul(res,w);
            madd(ans,immul(al,s));
            madd(ans,res);
            madd(s,a[x].se-a[x].fi);
        }
        else{
            int x=b[i].se;
            mdel(s,a[x].se-a[x].fi);
            int w=qpow(2,n-1-cr-cl),al=0,res=0;
            res=immul(C(cl+cr-1,cr-1),sr);
            mdel(res,immul(C(cl+cr-1,cl+1),sl));
            al=C(cl+cr,cl+1);
            // for(int j=0;j<=cl&&j+1<=cr;j++){
                // madd(res,1ull*C(cr-1,j)*C(cl,j)%mod*sr%mod);
                // if(j)mdel(res,1ull*C(cl-1,j-1)*C(cr,j+1)%mod*sl%mod);
                // madd(al,immul(C(cl,j),C(cr,j+1)));
            // }
            mdel(res,immul(al,a[x].fi+a[x].se));
            if(s&&al)   mmul(al,qpow(2,n-2-cr-cl));
            mmul(res,w);
            madd(ans,immul(al,s));
            madd(ans,res);
            cl++;madd(sl,a[x].fi+a[x].se);
        }
        // printf("%d %d %d %d : %d\n",cl,sl,cr,sr,ans);
    }
    int w=0;
    for(int i=1;i<=n;i++)   madd(w,a[i].se-a[i].fi);
    mdel(ans,immul(w,qpow(2,n-1)));
    mmul(ans,qpow(2,mod-2));
    printf("%d\n",ans);
}
int main(){init();debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}