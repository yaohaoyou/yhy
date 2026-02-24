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
const int maxn=1e5+10,mod=1e9+7,p[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int n,cnt;
int a[maxn];
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
struct Linear_basis{
    int p[19];
    void ins(int x){
        int X=x;
        for(int i=19;~i;i--){
            if(!(x&(1<<i))) continue;
            if(!p[i])   return p[i]=x,void();
            x^=p[i];
        }
        cnt++;
    }
}L;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        int x=0;
        for(int j=0;j<19;j++){
            int c=0;while(a[i]%p[j]==0) a[i]/=p[j],c++;
            if(c&1) x|=1<<j;
        }
        L.ins(x);
    }
    printf("%d\n",imdel(qpow(2,cnt),1));
}