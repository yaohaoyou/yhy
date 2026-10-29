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
bool mem1;
const int maxn=20,maxN=(1<<18)+10,mod=998244353;
struct mit{
    int v;
    mit(ll _x=0){v=_x%mod;}
    operator int()const{return v;}
    inline void operator+=(int y){v+=y;(v>=mod)&&(v-=mod);}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline void operator-=(int y){v-=y;(v<0)&&(v+=mod);}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline void operator*=(int y){v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
int n,m;
mit f[maxN],g[maxN];
int h[maxN];
int G[maxn],out[maxn],in[maxn];
bool bk[maxN];
inline int lb(int x){return x&-x;}
inline int cross(int s,int t){
    int res=0;
    for(int i=1;i<=n;i++)if(s&(1<<i-1))res+=__builtin_popcount(out[i]&t);
    return res;
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);const int N=(1<<n)-1;
    for(int i=1;i<=m;i++){int u,v;scanf("%d%d",&u,&v);G[u]|=(1<<v-1);G[v]|=(1<<u-1);out[u]|=(1<<v-1);in[v]|=(1<<u-1);}
    bk[0]=true;
    for(int i=1;i<=N;i++)   bk[i]=bk[i^lb(i)]&&!(G[__lg(lb(i))+1]&i);
    g[0]=1;
    for(int s=1;s<=N;s++){
        h[s]=0;
        for(int t=s&(s-1);t;t=(t-1)&s){
            int x=__lg(lb(s^t))+1;
            h[t]=h[t|(1<<x-1)]-__builtin_popcount(in[x]&(s^t^(1<<x-1)))+__builtin_popcount(out[x]&t);
            // assert(h[t]==cross(s^t,t));
        }
        for(int t=s;t;t=(t-1)&s)if(bk[t]){
            if(__builtin_popcount(t)&1) g[s]+=g[s^t],f[s]+=f[s^t]+g[s^t]*h[t];
            else    g[s]-=g[s^t],f[s]-=f[s^t]+g[s^t]*h[t];
        }
        // printf("%d %d\n",f[s],g[s]);
    }
    printf("%d\n",f[N]);
}