#include<bits/stdc++.h>
using namespace std;
const int maxn=360;
int n;
int a[maxn][maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i][i]);
    }
    for(int i=1;i<=n;i++){
        for(int j=i-1;j;j--)    a[i][j]=(a[i][j+1]-i+n)%n;
        for(int j=i+1;j<=n;j++) a[i][j]=(a[i][j-1]+i)%n;
    }
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=n;j++)   printf("%d ",a[i][j]);
}