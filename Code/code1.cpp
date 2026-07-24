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
inline void gmn(int &x,int y){(x>y)&&(x=y);}
const int maxn=1e6+10;
int n,k;
int a[maxn],b[maxn];
inline __int128 C(int x,int y){__int128 w=1;for(int i=1;i<=y;i++)w*=x-i+1;for(int i=1;i<=y;i++)w/=i;return w;}
void matt(int _cases){
    scanf("%d%d",&n,&k);
    if(ceil(log2(k))>n) return puts("-1"),void();
    for(int i=1;i<=k;i++)   b[i]=log10(i)+1;
    reverse(b+1,b+k+1);
    int m=k,p=0;
    for(int i=0;k;i++){
        int x=min(C(n,i),__int128(k));
        k-=x;while(x--) a[++p]=i;
    }
    k=m;
    ll ans=0;
    for(int i=1;i<=k;i++)   ans+=1ll*a[i]*b[i];
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}
