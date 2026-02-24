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
const int maxn=2e5+10,maxm=110;
int n,m;
int a[maxn],b[maxn];
int nx[maxn][maxm],buc[maxm];
void matt(){
    mems(buc,0);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]);
    for(int i=n;i;i--){
        memc(nx[i],buc);
        buc[a[i]]=i;
    }
    int len=m;
    for(int i=1;i<=m;i++)
        if(b[i]!=b[1]){len=i-1;break;}
    ll ans=0;
    for(int i=1;i+m-1<=n;i++){
        if(a[i]^b[1])   continue;
        int l=m+1;
        for(int j=i;j<=i+m;j++)
            if(a[j]!=a[i]){l=j-i;break;}
        if(l>len){
            if(len==m)  ans++;
            continue;
        }
        int x=i;
        for(int j=2;j<=m;j++){
            x=nx[x][b[j]];
            if(!x)  break;
        }
        if(x)ans+=n-x+1;
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}