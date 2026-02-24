#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=5e5+10;
int n;
pii p[maxn];
ll s[maxn];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i].fi);
    for(int i=1;i<=n;i++)   scanf("%d",&p[i].se);
    sort(p+1,p+n+1);
    for(int i=1;i<=n;i++)   s[i]=s[i-1]+p[i].se;
    int q;scanf("%d",&q);
    while(q--){
        int l,r;scanf("%d%d",&l,&r);
        l=lower_bound(p+1,p+n+1,pii(l,0))-p;
        r=upper_bound(p+1,p+n+1,pii(r,1e9+7))-p-1;
        printf("%lld\n",s[r]-s[l-1]);
    }
}