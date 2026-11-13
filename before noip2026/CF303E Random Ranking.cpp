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
const int maxn=120;
const db eps=1e-8;
int n,m;
pii a[maxn];
int d[maxn<<1];
db f[2][maxn][maxn];  // f[i][j][k] 表示前 i 个人有 j 个 < 当前区间，k 个在当前区间的概率
db ans[maxn][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se),d[++m]=a[i].fi,d[++m]=a[i].se;
    sort(d+1,d+m+1);m=unique(d+1,d+m+1)-d-1;
    for(int i=1;i<=n;i++)   a[i].fi=lower_bound(d+1,d+m+1,a[i].fi)-d,a[i].se=lower_bound(d+1,d+m+1,a[i].se)-d;
    for(int p=1;p<=n;p++){
        for(int x=a[p].fi;x<a[p].se;x++){
            mems(f,0);
            bool o=true;
            f[0][0][0]=1;
            for(int i=1;i<=n;i++)if(i^p){
                int len=d[a[i].se]-d[a[i].fi];
                mems(f[o],0);
                for(int j=0;j<=i;j++)for(int k=0;j+k<=i;k++)if(f[!o][j][k]>eps){
                    db pa=0,pb=0,pc=0;
                    if(a[i].fi<=x&&a[i].se>x)   pa=db(d[x]-d[a[i].fi])/len,pb=db(d[x+1]-d[x])/len,pc=db(d[a[i].se]-d[x+1])/len;
                    else if(a[i].fi>x)  pc=1;
                    else    pa=1;
                    f[o][j+1][k]+=f[!o][j][k]*pa;
                    f[o][j][k+1]+=f[!o][j][k]*pb;
                    f[o][j][k]+=f[!o][j][k]*pc;
                }
                o^=1;
            }
            o^=1;
            db P=1.0*(d[x+1]-d[x])/(d[a[p].se]-d[a[p].fi]);
            for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)if(f[o][i][j]>eps)for(int k=1;k<=j+1;k++){
                ans[p][i+k]+=f[o][i][j]*(1./(j+1))*P;
            }
        }
    }
    for(int i=1;i<=n;i++,puts(""))for(int j=1;j<=n;j++)printf("%.6f ",ans[i][j]);
}