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
int n,m,q;
int a[maxn],b[maxn];
int main(){
    scanf("%d%d%d",&n,&q,&m);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    int cnt=0;
    while(q--){
        int l,r,v;scanf("%d%d%d",&l,&r,&v);
        cnt=0;
        for(int i=l;i<=r;i++)   b[++cnt]=a[i];
        b[++cnt]=v;sort(b+1,b+cnt+1);
        int ans=1e9;
        for(int i=1;i<=cnt;i++) b[i+cnt]=b[i]+m;
        for(int i=cnt;i<=cnt*2;i++) ans=min(ans,b[i]-b[i-cnt+1]);
        printf("%d\n",ans);
    }
}