#include<bits/stdc++.h>
#define ppc(x) __builtin_popcount(x)
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
const int maxn=20,maxN=(1<<15)+10,mod=1e9+7;
int n,m;
int to[maxn],fr[maxn],f[maxN],g[maxN],h[maxN],p[maxN],pq[maxn*maxn],cr[maxN];
inline int lowbit(int x){return x&-x;}
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
inline int cross(int s,int t){
    int ret=0;
    while(s){
        int u=__lg(lowbit(s))+1;
        ret+=ppc(to[u]&t);
        s^=lowbit(s);
    }
    return ret;
}
int main(){
    scanf("%d%d",&n,&m);const int N=1<<n;
    pq[0]=1;for(int i=1;i<=m;i++)pq[i]=imadd(pq[i-1],pq[i-1]);
    for(int i=1,u,v;i<=m;i++){scanf("%d%d",&u,&v);to[u]|=(1<<v-1);fr[v]|=(1<<u-1);}
    for(int i=1;i<N;i++){
        int x=i^lowbit(i),u=__lg(lowbit(i))+1;
        h[i]=h[x]+ppc(to[u]&x)+ppc(fr[u]&x);
    }
    for(int i=0;i<N;i++)    h[i]=pq[h[i]];
    for(int s=0;s<N;s++){
        int lb=lowbit(s),x=s^lb;
        for(int y=x&(x-1);1;y=(y-1)&x){
            int t=y|lb;
            mdel(g[s],immul(f[t],g[s^t]));
            if(!y)  break;
        }
        p[s]=g[s];f[s]=imdel(h[s],p[s]);
        cr[s]=0;
        for(int t=s&(s-1);t;t=(t-1)&s){
            int y=s^t,x=t^lowbit(y),z=y^lowbit(y),u=__lg(lowbit(y))+1;
            cr[t]=cr[x]-ppc(to[u]&z)+ppc(fr[u]&t);
            mdel(f[s],1ull*g[t]*pq[cr[t]]%mod*h[s^t]%mod);
        }
        madd(g[s],f[s]);
    }
    printf("%d\n",f[N-1]);
}