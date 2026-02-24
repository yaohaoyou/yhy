#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define PQLI priority_queue<pli,vector<pli>,greater<pli>>
using namespace std;
const int maxn=2e5+10,mod=1e9+7;
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
ll a[maxn],b[maxn];
int p[maxn];
PQLI q;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%lld",&a[i]);
    sort(a+1,a+n+1);memc(b,a);
    int N=min(n,100);
    int x=0;
    for(int _=1;_<n;_++){
        for(int i=1;i<=N;i++)   a[i]=b[i];
        madd(x,x);madd(x,a[1]);madd(x,a[2]);
        for(int i=1;i<N;i++)   q.ep(a[i]+a[p[i]=i+1]-a[1]-a[2],i);
        int i=0;
        while((++i)<N){
            b[i]=q.top().fi;int u=q.top().se;q.pop();
            if((++p[u])<=N) q.ep(a[u]+a[p[u]]-a[1]-a[2],u);
        }
        PQLI().swap(q);
    }
    printf("%d\n",x);
}