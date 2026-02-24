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
const int maxn=1e6+10;
int n,m;
pii a[maxn];
int f[22][maxn];
void matt(int _cases){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+m+1);
    int mn=n+1;
    {
        for(int i=m;i;i--){
            if(mn<=a[i].se) a[i].se=0;
            else mn=a[i].se;
        }
        const int M=m;m=0;
        for(int i=1;i<=M;i++)if(a[i].se)a[++m]=a[i];
    }
    for(int i=1,j=1;i<=m;i++){
        while(j<=m&&a[j].fi<=a[i].se)j++;
        f[0][i]=j;
        // printf("%d ",f[0][i]);
    }
    // puts("");
    int ans=0;
    if(f[0][1]>m)ans=1;
    else{
        for(int i=1;i<=20;i++){
            for(int j=1;j<=m;j++){
                if(f[i-1][j]>m||f[0][f[i-1][j]]>m) f[i][j]=m+1;
                else f[i][j]=f[i-1][f[0][f[i-1][j]]];
                // printf("%d %d : %d\n",i,j,f[i][j]);
            }
            if(f[i][1]>m){ans=i+1;break;}
        }
    }
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}