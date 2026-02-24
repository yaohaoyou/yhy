#include<bits/stdc++.h>
#define ll long long
#define eb emplace_back
#define ep emplace
#define pii pair<int,int>
#define fi first
#define se second
#define mems(arr,x) memset(arr,x,sizeof(arr))
#define memc(arr1,arr2) memcpy(arr1,arr2,sizeof(arr2))
using namespace std;
const int maxn=5e4+10;
int n,m;
ll ans;
int p[maxn],a[maxn];
bitset<maxn> bs[maxn],pre[maxn],suf[maxn];
void print(bitset<maxn> bbs){for(int j=1;j<=n;j++) printf(bbs[j]?"1 ":"0 ");puts("");}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){scanf("%d",&a[i]);p[a[i]]=i;}
    for(int i=n-1;i;i--){
        bs[i]|=bs[i+1];
        bs[i].set(p[i+1]);
    }
    for(int i=1;i<=n;i++)   bs[a[i]]>>=(i+1);
    // for(int i=1;i<=n;i++)   print(bs[a[i]]);
    int l=1;
    for(int i=m;i<=n;i+=m){
        pre[l]=bs[a[l]];
        suf[i]=bs[a[i]];
        for(int j=l+1;j<=i;j++)
            pre[j]=pre[j-1]&bs[a[j]];
        for(int j=i-1;j>=l;j--)
            suf[j]=suf[j+1]&bs[a[j]];
        l=i+1;
        if(l<=n&&i+m>n)   i=n-m;
    }
    for(int i=1;i+m-1<=n;i++){
        int l=i,r=i+m-1;
        ans+=(suf[l]&pre[r]).count();
    }
    printf("%lld\n",ans);
}