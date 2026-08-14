#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define rep(x) for(int x=0;x<16;x++)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=1e5+10,mod=1e9+7;
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
int SG[]={3,3,0,1,1,3,0,2,1,1,0,4,5,3,7,4,8,1,1,2,0,3,1,1,0,3,3,2,2,4,4,5,5,9};
int n,k;
int sg[maxn],f[maxn][16],g[maxn][16],s[maxn][16],h[2][35][16];
int a[maxn],b[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i],&b[i]);
    for(int i=2;i<=52;i++){
        set<int> st;
        for(int j=0,k=i-2;j<=k;j++,k--) st.ep(sg[j]^sg[k]);
        int mx=0;while(st.count(mx))mx++;
        sg[i]=mx;
    }
    for(int i=53;i<=n;i++)sg[i]=SG[(i-53)%34];
    g[0][0]=1;s[1][0]=1;
    for(int i=1;i<=n;i++){
        int k=min(52,i);
        for(int j=1;j<=k;j++){
            rep(x)  mmul(s[j][x],a[i]);
            rep(x)  madd(f[i][x],s[j][x^sg[j]]);
        }
        for(int j=0;j<34;j++){
            rep(x)  mmul(h[i&1][j][x],a[i]);
            rep(x)  madd(f[i][x],h[i&1][j][x^SG[j]]);
        }
        for(int j=k;j;j--)  swap(s[j],s[j+1]);
        rep(j)  g[i][j]=immul(imadd(f[i-1][j],g[i-1][j]),b[i]);
        memc(s[1],g[i]);

        mems(h[(i+1)&1],0);
        if(k==52)rep(j)madd(h[(i+1)&1][0][j],s[k+1][j]);
        for(int j=0;j<34;j++)
            rep(x)  madd(h[(i+1)&1][(j+1)%34][x],h[i&1][j][x]);
        // rep(j)printf("%d ",f[i][j]);puts("");
        // rep(j)printf("%d ",g[i][j]);puts("");
        // rep(j)printf("%d ",s[i][j]);puts("\n");
        // rep(j)printf("%d ",h[i&1][j][0]);puts("");
    }
    printf("%d\n",imadd(f[n][0],g[n][0]));
}