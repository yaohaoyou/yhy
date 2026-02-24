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
const int maxn=2.5e5+10,mod=998244353;
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
int n,l,k;
int a[maxn],pq[maxn];
int main(){
    scanf("%d%d%d",&l,&k,&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    pq[0]=1;for(int i=1;i<=n;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    int ans=0;
    for(int i=1;i<=n;i++){
        int x=a[i]-k+1,m;
        if(x<0){
            x+=l;
            if(x>a[n]) m=i-1;
            else m=n-(lower_bound(a+1,a+n+1,x)-a)+1+i-1;
        }
        else m=i-1-(lower_bound(a+1,a+n+1,x)-a)+1;
        
        int res;
        if(m==0)    res=1;
        else if(m==1)   res=2;
        else res=immul(m+3,pq[m-2]);
        madd(ans,immul(pq[n-m-1],res));
    }
    printf("%d\n",ans);
}