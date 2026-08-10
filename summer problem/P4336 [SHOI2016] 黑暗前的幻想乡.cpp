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
const int maxn=20,mod=1e9+7;
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
int n;
int a[maxn][maxn][maxn],b[maxn][maxn],d[maxn][maxn];
inline int det(){
    n--;
    int res=1;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            while(d[i][i]){
                int x=d[j][i]/d[i][i];
                for(int k=i;k<=n;k++)   mdel(d[j][k],immul(x,d[i][k]));
                swap(d[i],d[j]);res*=-1;
            }
            swap(d[i],d[j]);res*=-1;
        }
    }
    (res==-1)&&(res+=mod);
    for(int i=1;i<=n;i++)   mmul(res,d[i][i]);
    n++;
    return res;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int x;scanf("%d",&x);
        while(x--){int u,v;scanf("%d%d",&u,&v);a[i][u][v]++;a[i][v][u]++;}
    }
    int ans=0;
    for(int s=(1<<n-1)-1;s;s--){
        mems(b,0);mems(d,0);
        for(int c=1;c<n;c++)if(s&(1<<c-1)){
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++)   d[i][i]+=a[c][i][j],mdel(d[i][j],a[c][i][j]);
            }
        }
        // for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)d[i][j]-=b[i][j];
        int w=det();
        // printf("%d %d\n",s,w);
        if((n-1-__builtin_popcount(s))&1) mdel(ans,w);
        else madd(ans,w);
    }
    printf("%d\n",ans);
}