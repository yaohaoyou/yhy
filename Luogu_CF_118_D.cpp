#include<bits/stdc++.h>
using namespace std;
const int maxn=110,maxk=15,mod=1e8;
int n1,n2,k1,k2;
int dp[maxn][maxn][maxk][maxk];
namespace MyMod{
    inline void madd(int &x,int y){x+=y;(x>mod)&&(x-=mod);}
    inline void mdel(int &x,int y){x-=y;(x<0)&&(x+=mod);}
    inline void mmul(int &x,int y){x=1ll*x*y%mod;}
    inline int imadd(int x,int y){madd(x,y);return x;}
    inline int imdel(int x,int y){mdel(x,y);return x;}
    inline int immul(int x,int y){mmul(x,y);return x;}
}
using namespace MyMod;
int ans;
int main(){
    scanf("%d%d%d%d",&n1,&n2,&k1,&k2);
    dp[0][0][0][0]=1;
    for(int o=0;o<=n1;o++){
        for(int t=0;t<=n2;t++){
            for(int i=0;i<=k1;i++){
                for(int j=0;j<=k2;j++){
                    int k=dp[o][t][i][j];
                    if(i!=k1)   madd(dp[o+1][t][i+1][0],k);
                    if(j!=k2)   madd(dp[o][t+1][0][j+1],k);
                    if(o==n1&&t==n2)    madd(ans,k);
                }
            }
        }
    }
    printf("%d\n",ans);
}