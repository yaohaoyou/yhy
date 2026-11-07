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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
const int maxn=5010,mod=998244353;
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
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,m;
pii a[maxn];
mit I[maxn],f[maxn],c[maxn],g[maxn][maxn],s1[maxn][maxn],s2[maxn][maxn],ans[maxn];
bool mem2;
int main(){
    // freopen("tree.in","r",stdin);freopen("tree.out","w",stdout);
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=2;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),I[i]=qpow(a[i].se-a[i].fi+1,mod-2);
    scanf("%d",&m);
    while(m--){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        if(u>v)swap(u,v);
        f[u]+=w;f[v]+=w;
        g[u][v]+=w;
    }
    for(int i=n;i>1;i--){
        c[i]+=c[i+1];f[i]+=c[i];
        int val=f[i]*I[i];
        c[a[i].se]+=val;c[a[i].fi-1]-=val;
        ans[i]+=f[i];
    }
    for(int i=n;i;i--){
        for(int j=n;j;j--){
            s1[i][j]+=s1[i][j+1];
            s2[i][j]+=s2[i+1][j];
            g[i][j]+=s1[i][j]+s2[i][j];
            if(i==j)    continue;
            if(i<j){
                int val=g[i][j]*I[j];
                s1[i][a[j].se]+=val;s1[i][a[j].fi-1]-=val;
            }
            else{
                int val=g[i][j]*I[i];
                s2[a[i].se][j]+=val;s2[a[i].fi-1][j]-=val;
            }
        }
    }
    for(int i=n;i;i--){
        int val=g[i][i]*I[i];
        for(int j=a[i].fi;j<=a[i].se;j++)   g[j][j]+=val;
        ans[i]-=g[i][i]*2;
    }
    for(int i=2;i<=n;i++)   printf("%d ",ans[i]);
}