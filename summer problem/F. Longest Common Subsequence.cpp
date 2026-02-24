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
const int maxn=1e6+10;
int n,m,p,x,a,b,c;
unordered_map<int,int> mp;
int get(){
    x=((1ll*a*x+b)%p*x+c)%p;
    return x;
}
void matt(int __){
    mp.clear();
    scanf("%d%d%d%d%d%d%d",&n,&m,&p,&x,&a,&b,&c);
    // if(__==22)   printf("%d %d %d %d %d %d %d\n",n,m,p,x,a,b,c);
    // for(int i=1;i<=n;i++)   printf("%d ",get());puts("");
    // for(int i=1;i<=m;i++)   printf("%d ",get());puts("");
    for(int i=1;i<=n;i++){int s=get();if(mp.find(s)==mp.end())mp[s]=i;}
    int ans=0;
    for(int i=1;i<=m;i++){int s=get();if(mp.find(s)!=mp.end())ans=max(ans,min(n-mp[s]+1,m-i+1));}
    printf("%d\n",ans);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}