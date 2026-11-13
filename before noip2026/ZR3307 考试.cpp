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
const int maxn=120,mod=1e9+9;
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
int d[maxn<<1];
mit f[2][maxn][maxn],inv[maxn],I[maxn];  // f[i][j][k] 表示前 i 个人有 j 个 < 当前区间，k 个在当前区间的概率
mit ans[maxn][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),d[++m]=a[i].fi,d[++m]=a[i].se,I[i]=qpow(a[i].se-a[i].fi,mod-2);
    for(int i=1;i<=n;i++)   inv[i]=qpow(i,mod-2);
    sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=n;i++)   a[i].fi=lower_bound(d+1,d+m+1,a[i].fi)-d,a[i].se=lower_bound(d+1,d+m+1,a[i].se)-d;
    for(int p=1;p<=n;p++){
        for(int x=a[p].fi;x<a[p].se;x++){
            mems(f,0);
            bool o=true;
            f[0][0][0]=1;
            for(int i=1;i<=n;i++)if(i^p){
                mems(f[o],0);
                for(int j=0;j<=i;j++)for(int k=0;j+k<=i;k++)if(f[!o][j][k]){
                    mit pa=0,pb=0,pc=0;
                    if(a[i].fi<=x&&a[i].se>x)   pa=I[i]*(d[x]-d[a[i].fi]),pb=I[i]*(d[x+1]-d[x]),pc=I[i]*(d[a[i].se]-d[x+1]);
                    else if(a[i].fi>x)  pc=1;
                    else    pa=1;
                    f[o][j+1][k]+=f[!o][j][k]*pa;
                    f[o][j][k+1]+=f[!o][j][k]*pb;
                    f[o][j][k]+=f[!o][j][k]*pc;
                }
                o^=1;
            }
            o^=1;
            mit P=mit(d[x+1]-d[x])*(d[a[p].se]-d[a[p].fi]);
            for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)if(f[o][i][j])for(int k=1;k<=j+1;k++){
                ans[p][i+k]+=f[o][i][j]*inv[j+1]*P;
            }
        }
    }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%d ",ans[i][j]);
}