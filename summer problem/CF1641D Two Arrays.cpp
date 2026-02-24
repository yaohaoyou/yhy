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
const int maxn=1e5+10,maxm=8,N=(1<<16)-1,inf=1e9;
int n,m;
int tot;
int a[maxn][maxm],b[maxn*maxm],c[maxn],w[maxn];
int f[N+10];
mt19937 matt(time(0));
int rd(){return abs(int(matt()));}
void discrete(){
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)b[++tot]=a[i][j];
    sort(b+1,b+tot+1);tot=unique(b+1,b+tot+1)-b-1;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]=lower_bound(b+1,b+tot+1,a[i][j])-b;
}
inline void gmn(int &x,int y){(x>y)&&(x=y);}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){for(int j=1;j<=m;j++)scanf("%d",&a[i][j]);scanf("%d",&w[i]);}
    discrete();
    int ans=INT_MAX;
    while(clock()/CLOCKS_PER_SEC<2.3){
        for(int i=1;i<=tot;i++) b[i]=rd()%15;
        mems(f,0x3f);
        for(int i=1;i<=n;i++){
            c[i]=0;
            for(int j=1;j<=m;j++)c[i]|=1<<b[a[i][j]];
            gmn(f[c[i]],w[i]);
        }
        for(int i=0;i<=15;i++)
            for(int j=0;j<=N;j++)if(j&(1<<i))gmn(f[j],f[j^(1<<i)]);
        for(int i=1;i<=n;i++)if(f[N^c[i]]<=inf)gmn(ans,w[i]+f[N^c[i]]);
    }
    printf("%d\n",ans==INT_MAX?-1:ans);
}