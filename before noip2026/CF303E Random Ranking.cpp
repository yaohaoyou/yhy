#include<bits/stdc++.h>
#define db double
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
const int maxn=82,mod=1e9+9;
int n,m,x;
pii a[maxn];
int d[maxn<<1];
db f[maxn][maxn],t[maxn][maxn];  // f[j][k] 表示有 j 个 < 当前区间，k 个在当前区间的概率
db ans[maxn][maxn];
void trans(int i,int sz){
    memc(t,f);mems(f,0);
    int len=d[a[i].se]-d[a[i].fi];
    for(int j=0;j<=sz;j++)for(int k=0;j+k<=sz;k++)if(t[j][k]){
        db pa=0,pb=0,pc=0;
        if(a[i].fi<=x&&a[i].se>x)   pa=db(d[x]-d[a[i].fi])/len,pb=db(d[x+1]-d[x])/len,pc=db(d[a[i].se]-d[x+1])/len;
        else if(a[i].fi>x)  pc=1;
        else    pa=1;
        f[j+1][k]+=t[j][k]*pa;
        f[j][k+1]+=t[j][k]*pb;
        f[j][k]+=t[j][k]*pc;
    }
}
void dvd(int l,int r){
    if(l==r){
        int p=l;
        if(a[p].fi<=x&&x<a[p].se){
            db P=db(d[x+1]-d[x])/(d[a[p].se]-d[a[p].fi]);
            for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)if(f[i][j])for(int k=1;k<=j+1;k++){
                ans[p][i+k]+=f[i][j]/(j+1)*P;
            }
        }
        return;
    }
    db g[maxn][maxn];memc(g,f);
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
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),d[++m]=a[i].fi,d[++m]=a[i].se;
    sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=n;i++)   a[i].fi=lower_bound(d+1,d+m+1,a[i].fi)-d,a[i].se=lower_bound(d+1,d+m+1,a[i].se)-d;
    for(x=1;x<=m;x++){
        mems(f,0);
        f[0][0]=1;
        dvd(1,n);
    }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%.6lf ",ans[i][j]);
}