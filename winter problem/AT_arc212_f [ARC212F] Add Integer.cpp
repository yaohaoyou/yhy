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
const int maxn=2e5+10,mod=998244353;
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
int ans;
void solve(int p,int x,int y){
    // debug("%d %d %d\n",p,x,y);
    if(p==1)    return madd(ans,immul(x,y));
    if(x>y) return solve(p-1,x-y,x);
    if(!x){
        if(p%3==0)  madd(ans,immul(y,y));
        return;
    }
    if(y<x+x||p<=3) return solve(p-1,y-x,x);
    int k=min((p-1)/3,y/(x+x));
    return solve(p-3*k,x,y-2*k*x);
}
int main(){
    int n,m,x;
    scanf("%d%d%d",&n,&m,&x);
    for(int i=0;i<=m;i++)   solve(n-1,i,x);
    printf("%d\n",ans);
}