//  P3389 【模板】高斯消元法
#include<bits/stdc++.h>
#define db double
using namespace std;
constexpr int maxn=110;
int n;
db a[maxn][maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        for(int j=1,x;j<=n+1;j++){
            scanf("%d",&x);
            a[i][j]=x;
        }
    }
    for(int i=1;i<=n;i++){
        int p=0;
        // for(int j=1;j<=n;j++){
        //     for(int k=1;k<=n+1;k++)   printf("%.2f ",a[j][k]);
        //     puts("");
        // }
        // puts("");
        for(int j=i;j<=n;j++)
            if(a[j][i]){p=j;break;}
        if(!p)  return 0&puts("No Solution");
        for(int j=i;j<=n+1;j++)
            swap(a[i][j],a[p][j]);
        for(int j=n+1;j>=i;j--)
            a[i][j]/=a[i][i];
        for(int j=1;j<=n;j++){
            if(i==j)    continue;
            db tmp=a[i][i]/a[j][i];
            // for(int k=n+1;k>=i;k--) a[j][k]*=tmp;
            // printf("j = %d  tmp = %.2f\n",j,tmp);
            for(int k=n+1;k>=i;k--) a[j][k]-=a[i][k]*a[j][i];
            // for(int j=1;j<=n;j++){
                // for(int k=1;k<=n+1;k++)   printf("%.2f ",a[j][k]);
                // puts("");
            // }
            // puts("");
            // if(i==j)    continue;
            // for(int k=n+1;k>=j;k--)
            //     a[j][k]-=tmp;
        }
        // puts("---------------------------------------");
    }
    for(int i=1;i<=n;i++)   printf("%.2f\n",a[i][n+1]);
}