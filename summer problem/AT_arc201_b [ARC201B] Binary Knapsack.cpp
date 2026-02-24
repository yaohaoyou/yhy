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
int n;ll w;
vector<ll> v[61];
void matt(){
    for(int i=0;i<61;i++)   v[i].clear();
    scanf("%d%lld",&n,&w);
    for(int i=1;i<=n;i++){
        int x,y;scanf("%d%d",&x,&y);
        v[x].eb(y);
    }
    ll ans=0;
    for(int i=0;i<60;i++){
        if(w<(1ll<<i))  break;
        if(v[i].empty())    continue;
        sort(v[i].begin(),v[i].end(),greater<ll>());
        if(w&(1ll<<i))   ans+=v[i][0];
        int j=bool(w&(1ll<<i));
        for(;j+1<v[i].size();j+=2) v[i+1].eb(v[i][j]+v[i][j+1]);
        if(j<v[i].size())   v[i+1].eb(v[i][j]);
    }
    printf("%lld\n",ans);
}
int main(){int T;scanf("%d",&T);while(T--)matt();}