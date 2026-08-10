#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=4e5+10;
int n,m,q;
int a[maxn],b[maxn];
pii c[maxn];
ll sa[maxn],sb[maxn],ss[maxn];
int s[maxn];
void matt(){
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]),c[i]=pii(a[i],0);
    for(int i=1;i<=m;i++)   scanf("%d",&b[i]),c[i+n]=pii(b[i],1);
    sort(a+1,a+n+1,greater<int>());sort(b+1,b+m+1,greater<int>());
    sort(c+1,c+n+m+1,greater<pii>());
    for(int i=1;i<=n;i++)   sa[i]=sa[i-1]+a[i];
    for(int i=1;i<=m;i++)   sb[i]=sb[i-1]+b[i];
    for(int i=1;i<=n+m;i++) s[i]=s[i-1]+c[i].se,ss[i]=ss[i-1]+c[i].fi;
    for(int i=1;i<=q;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        x=min(x,z);y=min(y,z);
        x=z-x;y=z-y;swap(x,y);
        if(z-s[z]>=x&&s[z]>=y)  printf("%lld\n",ss[z]);
        else if(s[z]>=y)  printf("%lld\n",sa[x]+sb[z-x]);
        else    printf("%lld\n",sa[z-y]+sb[y]);
    }
}
void dat(){
    n=2e3;m=2e3;q=1e3;const int V=100;
    printf("%d %d %d\n",n,m,q);
    for(int i=1;i<=n;i++)   printf("%d ",1ll*rand()*rand()%V+1);puts("");
    for(int i=1;i<=m;i++)   printf("%d ",1ll*rand()*rand()%V+1);puts("");
    while(q--){
        int x=rand()%n+1,y=rand()%m+1,z=rand()%(x+y)+1;
        printf("%d %d %d\n",x,y,z);
    }
    exit(0);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}