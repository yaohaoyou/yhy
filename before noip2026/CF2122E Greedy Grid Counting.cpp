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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=510,mod=998244353;
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
inline mit sum(int l,int r){return 1ull*(l+r)*(r-l+1)/2%mod;}
bool mem1;
int n,k;
int a[2][maxn];
mit f[2][maxn*maxn],c[maxn*maxn],d[maxn*maxn];
bool mem2;
void matt(int _cases){
    mems(f,0);mems(c,0);mems(d,0);
    scanf("%d%d",&n,&k);
    for(int i=0;i<2;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    f[(n+1)&1][0]=1;
    for(int i=n;i>1;i--){
        fll(f[i&1],0,n*(k+5));
        for(int j=0;j<=n*k;j++){
            int xl=a[0][i],xr=a[0][i],yl=a[1][i-1],yr=a[1][i-1];if(xl<0)xl=1,xr=k;if(yl<0)yl=1,yr=k;
            if(a[0][i]==-1&&a[1][i-1]==-1&&j<k)    f[i&1][0]+=f[(i+1)&1][j]*sum(1,k-j);
            if(a[0][i]==-1&&a[1][i-1]>=j)   f[i&1][0]+=f[(i+1)&1][j]*min(yl-j,k);
            if(a[0][i]>0&&a[1][i-1]==-1&&k>=j+xl)   f[i&1][0]+=f[(i+1)&1][j]*(k-j-xl+1);
            if(a[0][i]>0&&a[1][i-1]>0&&yl>=xl&&j<=yl-xl)    f[i&1][0]+=f[(i+1)&1][j];
            if(a[0][i]>0&&a[1][i-1]>0){
                if(yl<xl||(yl==xl&&j+xl-yl>0))  f[i&1][j+xl-yl]+=f[(i+1)&1][j];
            }
            else if(a[0][i]==-1&&a[1][i-1]==-1){
                if(j)   f[i&1][j]+=f[(i+1)&1][j]*k;
                c[j+1]+=f[(i+1)&1][j]*k;
                d[j+1]-=f[(i+1)&1][j];
                d[j+k+1]+=f[(i+1)&1][j];
            }
            else if(a[0][i]==-1){c[j+(!j)]+=f[(i+1)&1][j];c[j+k-yl+1]-=f[(i+1)&1][j];}
            else{c[j+(!j)]+=f[(i+1)&1][j];c[j+xl]-=f[(i+1)&1][j];}
                // for(int x=0;x<=k;x++){
                //     if(!x&&!j)  continue;
                //     if(a[0][i]==-1&&a[1][i-1]==-1)  f[i&1][j+x]+=f[(i+1)&1][j]*(k-x);
                //     else if(a[0][i]==-1){if(x<=k-yl)f[i&1][j+x]+=f[(i+1)&1][j];}
                //     else{if(xl>x)f[i&1][j+x]+=f[(i+1)&1][j];}
                // }
            // for(int x=xl;x<=xr;x++){
            //     for(int y=yl;y<=yr;y++){
                    // if(y>=x&&-j+y-x>=0) f[i&1][0]+=f[(i+1)&1][j];
        //             if(y<x||(y==x&&j+x-y>0))   f[i&1][j+x-y]+=f[(i+1)&1][j];
        //         }
        //     }
        }
        for(int j=1;j<=n*k;j++){
            d[j]+=d[j-1];
            c[j]+=c[j-1]+d[j];
            f[i&1][j]+=c[j];
        }
        fll(c,0,n*(k+5));fll(d,0,n*(k+5));
    }
    mit ans=accumulate(f[0],f[0]+n*k,0ll)%mod;
    if(a[0][1]==-1)ans*=k;
    if(a[1][n]==-1)ans*=k;
    printf("%d\n",ans);
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}