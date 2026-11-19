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
#define fll(arr,x,siz) fill(arr,arr+siz+1,x)
#define cpy(arr1,arr2,siz) copy(arr2,arr2+siz+1,arr1)
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
using namespace std;
const int maxn=2e5+10;
bool mem1;
int n,m,k;
int a[maxn],b[maxn];
bool mem2;
void matt(int _cases){
    m=k=0;b[k]=1e9;
    scanf("%d",&n);
    ll ans=0;
    for(int i=1;i<=n;i++){
        int x;scanf("%d",&x);
        if(x>a[m]){
            a[++m]=x;
            ans+=k-(upper_bound(b+1,b+k+1,x,greater<int>())-b)+1;
        }
        else{
            int p=lower_bound(a+1,a+m+1,x)-a;
            ans-=k-(upper_bound(b+1,b+k+1,a[p],greater<int>())-b)+1;
            a[p]=x;
            ans+=k-(upper_bound(b+1,b+k+1,a[p],greater<int>())-b)+1;
        }
        if(x<b[k]){
            b[++k]=x;
            ans+=m-(upper_bound(a+1,a+m+1,x)-a)+1;
        }
        else{
            int p=lower_bound(b+1,b+k+1,x,greater<int>())-b;
            ans-=m-(upper_bound(a+1,a+m+1,b[p])-a)+1;
            b[p]=x;
            ans+=m-(upper_bound(a+1,a+m+1,b[p])-a)+1;
        }
        // for(int x=1;x<=m;x++)for(int y=1;y<=k;y++)ans+=a[x]>b[y];
        printf("%lld ",ans);
    }
    puts("");
}
int main(){debug("%.2fMB\n",abs(&mem1-&mem2)/1024./1024);int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}