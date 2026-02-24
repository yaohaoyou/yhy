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
const int maxn=22,maxN=(1<<21)+10,mod=998244353;
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
int a[maxn][maxn],x[maxn],y[maxn];
bool ban[maxN];
int f[2][maxn][maxN],str[maxn][maxn];  // f[i][j][s] 表示前 i 个选定，有 j 个独立集，后 n-i 个的选定状态为 s 的方案数
inline int A(int x,int y){
    if(x<y)return 0;
    int res=1;
    for(int i=x-y+1;i<=x;i++)mmul(res,i);
    return res;
}
void init(){
    const int N=21;
    str[0][0]=1;for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)str[i][j]=imadd(str[i-1][j-1],immul(str[i-1][j],i-1));
}
int main(){
    init();
    scanf("%d",&n);
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)scanf("%d",&a[i][j]);
    int T;scanf("%d",&T);
    for(int i=1;i<=n;i++)if(a[i][i]){while(T--)puts("0");return 0;}
    for(int i=0;i<(1<<n);i++){
        for(int j=1;j<=n;j++)if(i&(1<<j-1)){
            for(int k=1;k<=n;k++)if((i&(1<<k-1))&&a[j][k]){ban[i]=true;break;}
            if(ban[i])  break;
        }
    }
    f[0][0][0]=1;
    ll cnt=0;
    for(int i=0;i<n;i++){
        int U=(1<<n-i)-1;
        for(int j=0;j<=i+1;j++)for(int s=0;s<=(U>>1);s++)f[(i+1)&1][j][s]=0;
        for(int j=0;j<=i;j++){
            for(int s=0;s<=U;s++){
                int dp=f[i&1][j][s];
                if(!dp)continue;
                if(s&1){madd(f[(i+1)&1][j][s>>1],dp);continue;}
                int rs=(U^s)>>1;
                for(int t=rs;;t=(t-1)&rs){
                    cnt++;
                    if(ban[(t<<1|1)<<i])   continue;
                    madd(f[(i+1)&1][j+1][t|(s>>1)],dp);
                    if(!t)  break;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)x[i]=f[n&1][i][0];
    for(int i=1;i<=n;i++){
        for(int j=0;j<=i;j++)if((i-j)&1)mdel(y[j],immul(x[i],str[i][j]));else madd(y[j],immul(x[i],str[i][j]));
    }
    for(int i=0;i<=n;i++)   printf("%d ",y[i]);puts("");
}