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
const int maxn=100;
int mod;
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
int n,m;
int f[maxn][16][16][16][16];
#define rep(i,x) for(int i=x;i<(1<<m);i++)
bool chk(int x,int y){return __builtin_popcount(x^y)==1;}
int main(){
    scanf("%d%d%d",&n,&m,&mod);
    if(n==1)    return printf("%d\n",1<<m),0;
    if(n==2){
        int ans=0;
        rep(a,0)rep(b,0)if(a<=b||chk(a,b))ans++;
        printf("%d\n",ans);
        return 0;
    }
    if(n==3){
        int ans=0;
        rep(a,0)rep(b,0)rep(c,0){
            int x=a,y=b,z=c;
            if(y>z&&chk(y,z))swap(y,z);
            if(x>y&&chk(x,y))swap(x,y);
            if(y>z&&chk(y,z))swap(y,z);
            if(x<=y&&y<=z)  ans++;
        }
        printf("%d\n",ans);
        return 0;
    }
    int ans=(1<<m);
    rep(a,0)rep(b,0)if(a<=b||chk(a,b))ans+=n-1;
    rep(a,0)rep(b,0)rep(c,0){
        int x=a,y=b,z=c;
        if(y>z&&chk(y,z))swap(y,z);
        if(x>y&&chk(x,y))swap(x,y);
        if(y>z&&chk(y,z))swap(y,z);
        if(x<=y&&y<=z)  ans++;
    }
    rep(a,0)rep(b,0)rep(c,0)rep(d,0){
        int x=a,y=b,z=c,w=d;
        if(y>z&&chk(y,z))swap(y,z);
        if(x>y&&chk(x,y))swap(x,y);
        if(y>z&&chk(y,z))swap(y,z);
        if(z>w&&chk(z,w))swap(z,w);
        if(y>z&&chk(y,z))swap(y,z);
        if(x>y&&chk(x,y))swap(x,y);
        if(x<=y&&y<=z&&z<=w)    f[4][x][y][z][w]++;
    }
    for(int i=1;i<=n;i++){
        rep(a,0)rep(b,a+1)rep(c,b+1)rep(d,c+1)rep(x,0){

        }
    }
}