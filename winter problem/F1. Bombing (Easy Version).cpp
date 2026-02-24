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
const int maxn=3010,mod=998244353;
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
int a[maxn],b[maxn],c[maxn],s[maxn],fac[maxn],inv[maxn];
vector<int> v;
void init(){
    const int N=3000;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return x<0||y<0||x<y?0:1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void matt(int _cases){
    v.clear();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   b[i]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        s[i]=s[i-1];
        if(~a[i])   b[a[i]]=i,v.eb(i);
        else s[i]++;
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        int res=1,k=0,c0=0,c1=0;
        for(int j:v){
            int n0,n1;
            if(a[j]<=i) n0=a[j],n1=j-n0,mmul(res,C(j-k-1,n0-c0-1));
            else    n1=a[j]-i,n0=j-n1,mmul(res,C(j-k-1,n1-c1-1));
            c0=n0;c1=n1;k=j;
        }
        mmul(res,C(n-k,i-c0));
        madd(ans,res);
    }
    bool flag=true;
    for(int i=1;i<=n;i++)
        if((~a[i])&&(a[i]^i))   flag=false;
    if(flag){mdel(ans,n);madd(ans,1);}
    printf("%d\n",ans);
}
int main(){init();int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}