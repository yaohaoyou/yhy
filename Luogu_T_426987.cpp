#include<bits/stdc++.h>
using namespace std;
const int maxn=1e3+10;
int n,m;
int a[maxn];
namespace GenHelper
{
    unsigned z1, z2, z3, z4, b;
    unsigned rand_()
    {
        b = ((z1 << 6) ^ z1) >> 13;
        z1 = ((z1 & 4294967294U) << 18) ^ b;
        b = ((z2 << 2) ^ z2) >> 27;
        z2 = ((z2 & 4294967288U) << 2) ^ b;
        b = ((z3 << 13) ^ z3) >> 21;
        z3 = ((z3 & 4294967280U) << 7) ^ b;
        b = ((z4 << 3) ^ z4) >> 12;
        z4 = ((z4 & 4294967168U) << 13) ^ b;
        return (z1 ^ z2 ^ z3 ^ z4);
    }
}
void srand_(unsigned x, int n)
{
    using namespace GenHelper;
    z1 = x;
    z2 = (~x) ^ 0x233333333U;
    z3 = x ^ 0x1234598766U;
    z4 = (~x) + 51;
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    if (!x)
        return;
    for (int i = 1; i <= n; ++i)
    {
        int j = rand_() % i + 1, k;
        k = a[i], a[i] = a[j], a[j] = k;
    }
}
int o[maxn][maxn];
int main(){
    cin>>n>>m;
    if(!m){printf("%d\n",n+n-1);return 0;}
    srand_(m,n);
    for(int i=1;i<=n;i++){
        o[i][i]=1;
        int l=i,r=i;
        for(int j=2;j<=n;j++){
            if(l==1){o[i][r+1]=j;r++;}
            else if(r==n){o[i][l-1]=j;l--;}
            else if(a[l-1]<a[r+1]){o[i][l-1]=j;l--;}
            else{o[i][r+1]=j;r++;}
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n;j++){
            if(o[i][j]==o[j][i])ans++;
        }
    }
    printf("%d\n",ans);
}