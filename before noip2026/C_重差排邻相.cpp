#include<bits/stdc++.h>
#define ll long long
#define fi first
#define se second
#define ep emplace
#define eb emplace_back
#define pii pair<int,int>
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
bool mem1;
namespace OIMATT{
    const int maxn=2e5+10,inf=1e9;
    int n;
    int a[maxn],b[maxn],c[maxn];
    int f[2][maxn][2];
    int F[2][(1<<20)+1][22];
    // void dfs(int x,int c0,int t){
    //     if(x>n){
    //         if(c0)return;
    //         int w=0;
    //         for(int i=1;i<=n;i++)if(c[i]^c[i%n+1])w++;
    //         gmx(mx,w);
    //         return;
    //     }
    //     if(~a[x]){
    //         c[x]=a[x]>t;
    //         dfs(x+1,c0,t);
    //     }
    //     else{
    //         if(c0){c[x]=0;dfs(x+1,c0-1,t);}
    //         c[x]=1;dfs(x+1,c0,t);
    //     }
    // }
    void matt(int _c){
        fll(b,0,n);for(int i=0;i<=n;i++)f[0][i][0]=f[0][i][1]=f[1][i][0]=f[1][i][1]=-inf;
        scanf("%d",&n);
        int p=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
            if(~a[i]){
                b[a[i]]++;
                if(!p)p=i;
            }
        }
        if(p)rotate(a+1,a+p,a+n+1);
        else{
            ll ans=0;
            for(int i=2;i<=n;i+=2)  ans+=i*2;
            if(!(n&1))  ans-=n;
            printf("%lld\n",ans);
            return;
        }
        if(n<=20){
            int sta=0;
            for(int i=1;i<=n;i++)if(~a[i])sta|=1<<a[i]-1;
            vector<int> vs;
            for(int i=0;i<(1<<n);i++)if((i&sta)==sta)vs.eb(i);
            for(int i:vs)mems(F[0][i],-0x3f),mems(F[1][i],-0x3f);
            F[1][sta][a[1]]=0;
            for(int i=2;i<=n;i++){
                if(~a[i]){
                    for(int j:vs){
                        F[i&1][j][a[i]]=-1e9;
                        for(int k=1;k<=n;k++)gmx(F[i&1][j][a[i]],F[(i-1)&1][j][k]+abs(a[i]-k));
                    }
                }
                else{
                    for(int j:vs)for(int x=1;x<=n;x++)if(!(j&(1<<x-1))){
                        int nj=j|(1<<x-1);
                        F[i&1][nj][x]=-1e9;
                        for(int k=1;k<=n;k++)gmx(F[i&1][nj][x],F[(i-1)&1][j][k]+abs(x-k));
                    }
                }
                // for(int j:vs)for(int k=1;k<=n;k++)printf("%d %d %d : %d\n",i,j,k,F[i&1][j][k]);
            }
            int ans=0;
            for(int i=1;i<=n;i++)gmx(ans,F[n&1][(1<<n)-1][i]+abs(a[1]-i));
            printf("%d\n",ans);
            return;
        }
        for(int i=1;i<=n;i++)   b[i]+=b[i-1];
        int ans=0;
        for(int t=1;t<=n;t++){
            int c0=t-b[t];
            for(int i=0;i<=n;i++)f[0][i][0]=f[0][i][1]=f[1][i][0]=f[1][i][1]=-inf;
            f[1][0][a[1]>t]=0;f[1][0][a[1]<=t]=-inf;
            for(int j=2;j<=n;j++){
                for(int k=0;k<=c0&&k<=j;k++){
                    if(~a[j]){
                        bool o=a[j]>t;
                        f[j&1][k][o]=max(f[(j-1)&1][k][!o]+1,f[(j-1)&1][k][o]);
                        f[j&1][k][!o]=-inf;
                    }
                    else{
                        if(k)   f[j&1][k][0]=max(f[(j-1)&1][k-1][1]+1,f[(j-1)&1][k-1][0]);
                        else    f[j&1][k][0]=-inf;
                        f[j&1][k][1]=max(f[(j-1)&1][k][0]+1,f[(j-1)&1][k][1]);
                    }
                }
            }
            ans+=max(f[n&1][c0][0]+(a[1]>t),f[n&1][c0][1]+(a[1]<=t));
            // printf("mx = %d %d\n",c0,max(f[n&1][c0][0]+(a[1]>t),f[n&1][c0][1]+(a[1]<=t)));
        }
        printf("%d\n",ans);
    }
}
bool mem2;
int main(){
    mems(OIMATT::f,-0x3f);
    // debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    int T=1;scanf("%d",&T);for(int i=1;i<=T;i++)OIMATT::matt(i);
}