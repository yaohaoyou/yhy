#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define ppc __builtin_popcountll
#define fi first
#define se second
#define debug(...) fprintf(stderr,__VA_ARGS__)
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=100010;
int n,q;
ll l,r;
bool a[maxn];
vector<ll> ans,v;
void dfs(ll x){
    if(v.size()+r-x+1<=ans.size())  return;
    if(x>r) return ans=v,void();
    bool f=true;
    for(ll i:v)if(__builtin_popcountll(x^i)<2){f=false;break;}
    if(f){v.eb(x);dfs(x+1);v.pop_back();}
    dfs(x+1);
}
void matt(int _cases){
    scanf("%d%lld%lld",&q,&l,&r);
    ans.clear();
    dfs(l);
    if(!q)  printf("%d\n",ans.size());
    else{mems(a,0);for(ll x:ans)a[x]=true;for(int i=l;i<=r;i++)printf("%d",a[i]);puts("");}
}
int cnt[2];
int main(){
    // srand(time(0));
    // // while(true){
    //     l=rand()%100,r=rand()%10;if(l>r)swap(l,r);
    //     // for(int i=l;i<=r;i++)for(int j=i+1;j<=r;j++)if(ppc(i^j)<=1)printf("%d %d\n",i,j);
    //     cnt[0]=cnt[1]=0;
    //     for(int i=l;i<=r;i++)   cnt[ppc(i)&1]++;printf("%d %d\n",cnt[0],cnt[1]);
    // //     debug("%d %d : %d %d\n",l,r,max(cnt[0],cnt[1]),(r-l+2)/2);
    // //     assert(max(cnt[0],cnt[1])==(r-l+2)/2);
    // // }
    // exit(0);
    int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);
}