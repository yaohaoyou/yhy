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
bool mem1;
const int maxn=5010;
int n,a,b;
int p[maxn];
ll f[maxn][maxn];
bool mem2;
int main(){
    debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);
    scanf("%d%d%d",&n,&a,&b);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i]);
    mems(f,0x3f);f[0][0]=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(j==p[i]){
                for(int k=0;k<j;k++)    gmn(f[i][j],f[i-1][k]);
            }
            else if(j>p[i]) gmn(f[i][j],f[i-1][j]+b);
            else    gmn(f[i][j],f[i-1][j]+a);
        }
    }
    printf("%lld\n",*min_element(f[n],f[n]+n+1));
}