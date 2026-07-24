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
const int maxn=1010,mod=998244353;
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
bool mem1;
int n,m;
int a[maxn],p[maxn];
int f[2][maxn<<1][maxn],g[2][maxn<<1][maxn];  // f[i&1][j][k] 表示前 i 个数的最大后缀和为 j，sum(a)=k 的贡献和，g[i][j][k] 表示 [i,n] 中的最小前缀和为 j，sum(a)=k 的贡献和
int sf[maxn][maxn<<1],sg[maxn][maxn<<1],s1[maxn<<1][maxn],s2[maxn<<1][maxn],ss[maxn][maxn];
bool mem2;
void upd_f(int i,bool flag=true){
    for(int k=0;k+abs(a[i])<=m;k++){
        int w=sf[k][m];if(!w)continue;
        if(a[i]<0)  mmul(w,p[i]);
        madd(f[i&1][a[i]+m][k+abs(a[i])],w);
    }
    if(flag){
        for(int k=abs(a[i]);k<=m;k++){
            for(int j=a[i]+1;j<=m;j++){
                int w=f[(i-1)&1][j-a[i]+m][k-abs(a[i])];if(!w)continue;
                if(j<0) mmul(w,p[i]);
                madd(f[i&1][j+m][k],w);
            }
        }
    }
}
void upd_all_f(int i){
    for(int j=-m;j<=m;j++){
        for(int k=0;k<=m;k++){
            int l=max(j-m,-k),r=min(j-1,k);
            int w=imdel(s1[j-l+m][k+l],s1[j+m][k]);
            if(r>0) madd(w,imdel(s2[j-1+m][k-1],s2[j-r-1+m][k-r-1]));
            if(!w)continue;
            if(j<0) mmul(w,p[i]);
            madd(f[i&1][j+m][k],w);
        }
    }
}
void upd_g(int i,bool flag=true){
    for(int k=0;k+abs(a[i])<=m;k++){
        int w=sg[k][m];if(!w)continue;
        if(a[i]>0) mmul(w,p[i]);
        madd(g[i&1][a[i]+m][k+abs(a[i])],w);
    }
    if(flag){
        for(int k=abs(a[i]);k<=m;k++){
            for(int j=-m;j<a[i];j++){
                int w=g[(i+1)&1][j-a[i]+m][k-abs(a[i])];
                if(j>0) mmul(w,p[i]);
                madd(g[i&1][j+m][k],w);
            }
        }
    }
}
void upd_all_g(int i){
    for(int j=-m;j<=m;j++){
        for(int k=0;k<=m;k++){
            int l=max(j+1,-k),r=min(j+m,k);
            int w=l<0?imdel(s1[j-l+m][k+l],s1[j+m][k]):0;
            l=max(1,j+1);
            if(l<=r)    madd(w,imdel(s2[j-l+m][k-l],s2[j-r-1+m][k-r-1]));
            if(!w)continue;
            if(j>0) mmul(w,p[i]);
            madd(g[i&1][j+m][k],w);
        }
    }
}
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]);
    g[(n+1)&1][m][0]=1;
    for(int i=n;i;i--){
        mems(g[i&1],0);
        for(int k=0;k<=m;k++){
            sg[k][m+m]=g[(i+1)&1][m+m][k];
            for(int j=m+m-1;~j;j--)   sg[k][j]=imadd(sg[k][j+1],g[(i+1)&1][j][k]);
        }
        for(int j=0;j<=m+m;j++){
            for(int k=0;k<=m;k++){
                if(k==m||j==0)  s1[j][k]=g[(i+1)&1][j][k];
                else    s1[j][k]=imadd(s1[j-1][k+1],g[(i+1)&1][j][k]);
                if(!k||j==0)    s2[j][k]=g[(i+1)&1][j][k];
                else    s2[j][k]=imadd(s2[j-1][k-1],g[(i+1)&1][j][k]);
            }
        }
        if(a[i]){upd_g(i);a[i]*=-1;upd_g(i);}
        else{
            for(int j=1;j<=m;j++){
                a[i]=j;upd_g(i,0);
                a[i]=-j;upd_g(i,0);
            }
            a[i]=0;
            upd_all_g(i);
        }
        for(int j=0;j<=m;j++)
            for(int k=0;k<=m;k++)   madd(ss[i][j],g[(i+1)&1][k+m][j]);
    }
    mems(s1,0);mems(s2,0);
    int ans=0;
    f[0][m][0]=1;
    for(int i=1;i<=n;i++){
        mems(f[i&1],0);
        for(int k=0;k<=m;k++){
            sf[k][0]=f[(i-1)&1][0][k];
            for(int j=1;j<=m+m;j++)   sf[k][j]=imadd(sf[k][j-1],f[(i-1)&1][j][k]);
        }
        for(int j=1;j<=m+m;j++){
            for(int k=0;k<=m;k++){
                if(k==m||j==1)  s1[j][k]=f[(i-1)&1][j][k];
                else    s1[j][k]=imadd(s1[j-1][k+1],f[(i-1)&1][j][k]);
                if(!k||j==1)    s2[j][k]=f[(i-1)&1][j][k];
                else    s2[j][k]=imadd(s2[j-1][k-1],f[(i-1)&1][j][k]);
            }
        }
        if(a[i]){upd_f(i);a[i]*=-1;upd_f(i);}
        else{
            for(int j=1;j<=m;j++)   a[i]=j,upd_f(i,0);
            a[i]=0;
            upd_all_f(i);
        }
        for(int l=i;l<=m;l++)if(ss[i][m-l])
            for(int j=-m;j<0;j++)
                if(f[i&1][j+m][l])madd(ans,immul(f[i&1][j+m][l],ss[i][m-l]));
    }
    for(int i=0;i<=m;i++)   madd(ans,g[1][i+m][m]);
    printf("%d\n",ans);
}