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
int n,k;
int rnk[maxn];
void matt(int _cases){
    scanf("%d%d",&n,&k);
    if(k<n-1||k>1ll*n*(n-1)/2)  return puts("-1"),void();
    rnk[0]=1;
    int mxd=0;
    for(int i=2;i<=n;i++){
        int fr=min(mxd,k-n+i-1);
        printf("%d %d\n",rnk[fr],i);
        k-=fr+1;
        rnk[fr+1]=i;
        if(mxd<fr+1)    mxd=fr+1;
    }
    puts("");
    assert(!k);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}