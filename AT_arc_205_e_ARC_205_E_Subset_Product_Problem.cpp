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
const int maxn=4e5+10,maxm=(1<<20)+10,m=20,M=(1<<m)-1,mod=998244353,B=4500;
namespace FastMod{
    inline void madd(int &x,int y){x+=y;(x>=mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ull*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
    inline int qpow(int x,ll y){int res=1;while(y){if(y&1)mmul(res,x);mmul(x,x);y>>=1;}return res;}
}
using namespace FastMod;
int n;
int a[maxn],f[maxm],g[maxm];
inline void FMT(){
    memc(f,g);
    for(int i=0;i<m;i++)
        for(int j=0;j<=M;j++)
            if(j&(1<<i))mmul(f[j],f[j^(1<<i)]);
}
int main(){
    fill(f,f+M+1,1);fill(g,g+M+1,1);
    scanf("%d",&n);
    for(int i=1,l=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(i%B==0){
            for(int j=l;j<=i;j++)   mmul(g[a[j]],a[j]);
            FMT();
            l=i+1;
        }
        int ans=f[a[i]];
        for(int j=l;j<=i;j++)if((a[j]&a[i])==a[i])mmul(ans,a[j]);
        printf("%d\n",ans);
    }
}
// nB+(nVlogV)/B