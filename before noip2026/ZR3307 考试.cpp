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
    inline int& operator+=(int y){v+=y;(v>=mod)&&(v-=mod);return v;}
    inline mit operator+(int y){y+=v;(y>=mod)&&(y-=mod);return y;}
    inline int& operator-=(int y){v-=y;(v<0)&&(v+=mod);return v;}
    inline mit operator-(int y){y=v-y;(y<0)&&(y+=mod);return y;}
    inline int& operator*=(int y){return v=1ull*v*y%mod;}
    inline mit operator*(int y){return 1ull*v*y%mod;}
};
inline mit qpow(mit x,int y){mit res=1;while(y){if(y&1)res*=x;x*=x;y>>=1;}return res;}
int n,m,x;
pii a[maxn];
int d[maxn<<1];
mit f[maxn][maxn],inv[maxn],I[maxn];  // f[j][k] 表示有 j 个 < 当前区间，k 个在当前区间的概率
mit ans[maxn][maxn];
void trans(int i,int sz){
    sz++;
    mit pa=0,pb=0,pc=0;
    if(a[i].fi<=x&&a[i].se>x)   pa=I[i]*(d[x]-d[a[i].fi]),pb=I[i]*(d[x+1]-d[x]),pc=I[i]*(d[a[i].se]-d[x+1]);
    else if(a[i].fi>x)  pc=1;
    else    pa=1;
    for(int j=sz;~j;j--)for(int k=sz-j;~k;k--){
        f[j][k]*=pc;
        if(j)f[j][k]+=f[j-1][k]*pa;
        if(k)f[j][k]+=f[j][k-1]*pb;
    }
}
void dvd(int l,int r){
    if(l==r){
        int p=l;
        if(a[p].fi<=x&&x<a[p].se){
            mit P=mit(d[x+1]-d[x])*I[p];
            for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)if(f[i][j]){
                ans[p][i+1]+=f[i][j]*inv[j+1]*P;
                ans[p][i+j+2]-=f[i][j]*inv[j+1]*P;
            }
        }
        return;
    }
    mit g[maxn][maxn];int sz=l-1+n-r;
    for(int i=0;i<=sz;i++)for(int j=0;j<=sz;j++)g[i][j]=f[i][j];
    int mid=(l+r)>>1;
    for(int i=r;i>mid;i--)   trans(i,l-1+n-i);
    dvd(l,mid);
    memc(f,g);
    for(int i=l;i<=mid;i++) trans(i,i-1+n-r);
    dvd(mid+1,r);
}
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),d[++m]=a[i].fi,d[++m]=a[i].se,I[i]=qpow(a[i].se-a[i].fi,mod-2);
    for(int i=1;i<=n;i++)   inv[i]=qpow(i,mod-2);
    sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=n;i++)   a[i].fi=lower_bound(d+1,d+m+1,a[i].fi)-d,a[i].se=lower_bound(d+1,d+m+1,a[i].se)-d;
    for(x=1;x<=m;x++){
        mems(f,0);
        f[0][0]=1;
        dvd(1,n);
    }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%d ",ans[i][j]+=ans[i][j-1]);
}