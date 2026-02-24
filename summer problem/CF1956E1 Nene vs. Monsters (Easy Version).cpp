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
const int maxn=2e5+10;
int n;
int a[maxn],b[maxn];
inline int nx(int x){return x%n+1;}
inline int pr(int x){return x==1?n:x-1;}
inline bool check(){
    for(int i=1;i<=n;i++)   if(a[i]&&a[nx(i)]&&a[nx(nx(i))]&&a[nx(nx(nx(i)))])  return false;
    return true;
}
void matt(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    while(!check()){for(int i=1;i<=n;i++)a[nx(i)]=max(0,a[nx(i)]-a[i]);}
    for(int i=1;i<=n;i++)if(a[nx(i)]&&a[i]) a[nx(i)]=max(0,a[nx(i)]-a[i]);else break;
    for(int i=1;i<=n;i++)b[i]=a[i];
    for(int i=1;i<=n;i++){
        if(!a[pr(i)]&&a[i]&&a[nx(i)]){
            int k=a[nx(i)]/a[i];
            b[nx(nx(i))]=max(0ll,a[nx(nx(i))]-1ll*k*a[nx(i)]+1ll*k*(k+1)/2*a[i]);
            b[nx(i)]=0;
        }
    }
    printf("%d\n",n-count(b+1,b+n+1,0));
    for(int i=1;i<=n;i++)if(b[i])printf("%d ",i);puts("");
}
int main(){int T;scanf("%d",&T);while(T--)matt();}