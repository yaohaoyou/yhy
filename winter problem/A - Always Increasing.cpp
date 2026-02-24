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
int n,q;
ll ad[maxn];
ll c[maxn];
inline void gmn(ll &x,ll y){(x>y)&&(x=y);}
inline void gmx(ll &x,ll y){(x<y)&&(x=y);}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++)    c[i]=1;
    while(q--){
        int x,y;scanf("%d%d",&x,&y);
        ad[x]+=y;
        gmx(c[x],ad[x]+1-ad[x+1]);
    }
    ll ans=0,now=1;
    for(int i=1;i<=n;i++)   ans+=now,now+=c[i];
    printf("%lld\n",ans);
}