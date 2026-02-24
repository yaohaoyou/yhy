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
const int maxn=2.5e6+10,mod=998244353;
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
int n,q;
int a[maxn];
void matt(int _cases){
    scanf("%d%d",&n,&q);
    int s1=0,s2=0;
    for(int i=1;i<=n;i++){
        scanf("%1d",&a[i]);
        madd(s2,s2);
        if(a[i])    madd(s2,imadd(s1,imadd(s1,qpow(2,i-1))));
        else mdel(s2,imadd(s1,imdel(s1,qpow(2,i-1))));
        madd(s1,s1);
        if(a[i])    madd(s1,qpow(2,i-1));
        else mdel(s1,qpow(2,i-1));
        // printf("%d %d\n",s1,s2);
    }
    const int i2=qpow(2,mod-2),i4=qpow(4,mod-2),pq=qpow(2,n),pq1=qpow(2,n-1);
    while(q--){
        int x;scanf("%d",&x);
        if(!a[x]){
            int w=imadd(4ull*immul(s1-pq1+mod,i2)%mod,imadd(pq,pq));
            madd(s2,w);
            madd(s1,pq);
        }
        else{
            int w=imdel(4ull*immul(s1+pq1,i2)%mod,imadd(pq,pq));
            mdel(s2,w);
            mdel(s1,pq);
        }
        a[x]^=1;
        // printf("%d %d\n",s1,s2);
        printf("%d\n",immul(imdel(s2,pq1),i4));
    }
}
int main(){int T=1;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}