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
inline void gmn(auto &x,auto y){(x>y)&&(x=y);}
inline void gmx(auto &x,auto y){(x<y)&&(x=y);}
const int maxn=1e5+10;
int n;
pii a[maxn];
bool mk[maxn];
int pr[maxn];
int main(){
    freopen("graph.in","r",stdin);freopen("graph.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d%d",&a[i].fi,&a[i].se);
    sort(a+1,a+n+1);
    int pre=0,ans=n;
    for(int i=1,mn=1e9+1;i<=n;i++)if(mn>a[i].se)mk[i]=true,mn=a[i].se,pr[i]=pre,pre=i;else ans--;
    for(int i=n,mx=-1e9-1;i;i--){
        gmx(mx,a[i].se);
        if(mk[i]){
            int x=pr[i];
            if(x&&mx>=a[x].se)  ans--;
        }
    }
    printf("%d\n",ans);
}