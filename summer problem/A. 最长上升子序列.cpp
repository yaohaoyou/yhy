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
const int maxn=5e4+10;
int n;
int a[maxn],b[maxn],ans[maxn];
int c[maxn];
int dp[maxn];
struct BIT{
    int tr[maxn];
    inline int lowbit(int x){return x&-x;}
    inline void add(int x,int s){while(x<=n){tr[x]=max(tr[x],s);x+=lowbit(x);}}
    inline int query(int x){int res=0;while(x){res=max(res,tr[x]);x^=lowbit(x);}return res;}
    inline void clear(){mems(tr,0);}
}T;
inline int calc(int x){
    if(ans[x])  return ans[x];
    mems(c,0);
    for(int i=1;i<=x;i++)   c[b[i]]=a[b[i]];
    T.clear();
    int len=0;
    for(int i=1;i<=n;i++){
        if(!c[i])   continue;
        int dp=T.query(c[i]-1)+1;
        T.add(c[i],dp);
    }
    return ans[x]=T.query(n);
}
int main(){
    // srand(time(0));
    // n=5e4;
    // printf("%d\n",n);
    // iota(a+1,a+n+1,1);iota(b+1,b+n+1,1);
    // random_shuffle(a+1,a+n+1);random_shuffle(b+1,b+n+1);
    // for(int i=1;i<=n;i++)   printf("%d ",a[i]);puts("");
    // for(int i=1;i<=n;i++)   printf("%d ",b[i]);puts("");
    // return 0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&b[i]);
    // {
    //     int mx=0;
    //     for(int i=1;i<=n;i++)for(int j=0;j<i;j++)if(a[i]>a[j])dp[i]=max(dp[i],dp[j]+1),mx=max(mx,dp[i]);
    //     printf("%d\n",mx);
    //     return 0;
    // }
    for(int now=1,lst=0;;now++){
        int l=lst+1,r=l,p=0;
        while(r<=n&&(!ans[r]||ans[r]==now))r++;r--;
        while(l<=r){
            int mid=(l+r)>>1;
            if(calc(mid)==now)  p=mid,l=mid+1;
            else    r=mid-1;
        }
        for(int i=lst+1;i<=p;i++)   ans[i]=now;
        if(p==n)    break;
        lst=p?p:lst;
    }
    for(int i=1;i<=n;i++)   printf("%d ",ans[i]);
}