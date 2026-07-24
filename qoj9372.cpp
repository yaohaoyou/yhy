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
const int maxn=3e5+10;
int n;
int s[maxn],a[maxn],b[maxn],nxt[maxn];
vector<int> v[maxn];
int main(){
    scanf("%d",&n);
    ll ans=0,now=0;
    for(int i=1;i<=n;i++){
        scanf("%d%d%d",&s[i],&a[i],&b[i]);
        s[i]=(s[i]+ans)%n;
        int j=nxt[i-1];
        while(j&&s[j+1]!=s[i]) v[i].eb(j),now-=b[i-j],j=nxt[j];
        if((i^1)&&s[j+1]==s[i])j++;nxt[i]=j;
        if(s[1]==s[i])  now+=b[i];
        for(int j:v[nxt[i]]) now-=b[i-j],v[i].eb(j);
        ans+=1ll*now*a[i];printf("%lld\n",ans);
    }
}