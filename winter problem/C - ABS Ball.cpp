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
const int maxn=2e7+10,mod=998244353;
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
int n,m,ans;
int fac[maxn],inv[maxn];
void init(){
    const int N=2e7;
    fac[0]=1;for(int i=1;i<=N;i++)fac[i]=immul(fac[i-1],i);
    inv[N]=qpow(fac[N],mod-2);for(int i=N-1;~i;i--)inv[i]=immul(inv[i+1],i+1);
}
inline int C(int x,int y){return 1ull*fac[x]*inv[y]%mod*inv[x-y]%mod;}
void dfs(int x,int y,int z){
    if(x>m){
        if(y==n)    ans+=z;
        return;
    }
    for(int i=0;i<=n;i++){
        for(int j=0;i+j+y<=n;j++){
            if(i==j)    continue;
            dfs(x+1,i+j+y,z*abs(i-j));
        }
    }
}
int main(){
    init();
    scanf("%d%d",&n,&m);
    int ans=0,pq=qpow(2,m);
    for(int i=n&1;i<=n;i+=2){
        if(i<m) continue;
        // printf("%d\n",C(m+(n-i)/2-1,));
        int res=ans;
        if(i==n)    madd(ans,immul(pq,C(i+m-1,m+m-1)));
        else madd(ans,1ull*pq*C(i+m-1,m+m-1)%mod*C(m+(n-i)/2-1,m-1)%mod);
        // printf("%d ",C(i+m-1,m+m-1));
    }
    printf("%d\n",ans);
    // for(n=1;n<=20;n++){
    //     for(m=1;m<=n;m++){
    //         ans=0;
    //         dfs(1,0,1);
    //         printf("%d,",ans);
    //     }
    //     puts("");
    // }
}