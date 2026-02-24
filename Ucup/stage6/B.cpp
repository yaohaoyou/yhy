#include<bits/stdc++.h>
#define ll long long
#define int long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=510,maxm=1e6+10;
int n,m;ll a,b;
int c[maxn][maxn];
int buc[maxm];
ll s[maxm],ss[maxm];
void matt(int _cases){
    scanf("%lld%lld%lld%lld",&n,&m,&a,&b);
    ll col=n*m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)scanf("%lld",&c[i][j]),buc[c[i][j]]++;
    sort(buc+1,buc+col+1,greater<int>());
    for(int i=1;i<=col;i++) s[i]=s[i-1]+buc[i];
    for(int i=1;i<=col;i++) ss[i]=ss[i-1]+s[i];
    ll ans=min((col-buc[0])*a,(col-buc[0]-buc[1])*a+buc[0]*b);
    // printf("%d\n",buc[2]);
    for(int i=1;i<=col;i++){
        ll now=(s[col]-s[i])*a+col*i*b+(s[i]-s[col])*b*i-ss[i]*b;
        // printf("%d\n",col*i*b);
        // for(int j=1;j<=i;j++){
        //     now+=(col-s[j]-s[col]+s[i])*b;
        //     printf("%d ",(col-s[j]-s[col]+s[i]));
        // }
        // puts("");
        // for(int j=1;j<=i;j++)   now-=s[j]*b;
        // printf("now = %d\n",now);
        ans=min(ans,now);
    }
    printf("%lld\n",ans);
    fill(buc,buc+col+1,0);
}
signed main(){int T;scanf("%lld",&T);for(int i=1;i<=T;i++)matt(i);}