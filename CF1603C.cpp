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
const int maxn=1e5+10,mod=998244353;
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
int a[maxn],mn[maxn],mx[maxn],c[maxn];
void matt(int _cases){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int now=0,ans=0;
    for(int i=1;i<=n;i++){
        mn[i]=mx[i]=a[i];c[i]=0;
        for(int j=i-1;j;j--){
            if(mx[j]>mn[j+1]){
                if(c[j])    mdel(now,immul(c[j],j));
                c[j]=(a[j]+mn[j+1]-1)/mn[j+1]-1;
                madd(now,immul(c[j],j));
                mn[j]=a[j]/(c[j]+1);
                mx[j]=mn[j]+bool(a[j]%mn[j+1]);
            }
            else break;
        }
        madd(ans,now);
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}