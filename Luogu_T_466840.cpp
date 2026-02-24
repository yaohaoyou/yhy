#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
using namespace std;
const int maxn=2e5+10;
ll n,m;
int k,ans1,ans2;
int main(){
    scanf("%lld%lld%d",&n,&m,&k);
    for(int i=1;i<=k;i++){
        ll x,y;
        scanf("%lld%lld",&x,&y);
        if(y>=x) ans1++;
        else    ans2++;
    }
    printf("%d\n",ans1);
}