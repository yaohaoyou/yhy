#pragma GCC optimize(2,3,"Ofast","inline")
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
const int maxn=2e5+10,inf=1e9;
int n,v,m;
int a[maxn],t[maxn],aa[maxn];
int b[maxn],c[maxn];ll d[maxn];
int dp[maxn];
ll arr[2][maxn];
inline int lowbit(int x){return x&-x;}
inline void getmx(int &x,int y){(x<y)&&(x=y);}
struct Tree1{
    int len;
    vector<int> tr;
    void build(int siz){len=siz;tr=vector<int>(siz+1,-inf);}
    inline void add(int x,int s){while(x){getmx(tr[x],s);x^=lowbit(x);}}
    inline int query(int x){int res=-inf;while(x<=len){getmx(res,tr[x]);x+=lowbit(x);}return res;}
};
struct Tree2{
    int len;
    vector<int> tr;
    void build(int siz){len=siz;tr=vector<int>(siz+1,-inf);}
    inline void add(int x,int s){while(x<=len){getmx(tr[x],s);x+=lowbit(x);}}
    inline int query(int x){int res=-inf;while(x){getmx(res,tr[x]);x^=lowbit(x);}return res;}
};
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,m
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    vector<ll> tr[2][maxn<<2];
    Tree1 mx1[maxn<<2];Tree2 mx2[maxn<<2];
    void build(setpos){
        sort(tr[0][p].begin(),tr[0][p].end());sort(tr[1][p].begin(),tr[1][p].end());
        tr[0][p].erase(unique(tr[0][p].begin(),tr[0][p].end()),tr[0][p].end());
        tr[1][p].erase(unique(tr[1][p].begin(),tr[1][p].end()),tr[1][p].end());
        mx1[p].build(tr[0][p].size());mx2[p].build(tr[1][p].size());
        if(l==r)return;setmid;build(lson);build(rson);
    }
    inline void ins(int x){
        int p=1,l=1,r=m;
        while(l^r){
            tr[0][p].eb(arr[0][x]);tr[1][p].eb(arr[1][x]);
            setmid;(aa[x]<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        tr[0][p].eb(arr[0][x]);tr[1][p].eb(arr[1][x]);
    }
    inline void upd(int x,int s){
        int p=1,l=1,r=m;
        while(l^r){
            mx1[p].add(lower_bound(tr[0][p].begin(),tr[0][p].end(),arr[0][x])-tr[0][p].begin()+1,s);
            mx2[p].add(lower_bound(tr[1][p].begin(),tr[1][p].end(),arr[1][x])-tr[1][p].begin()+1,s);
            setmid;(aa[x]<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);
        }
        mx1[p].add(lower_bound(tr[0][p].begin(),tr[0][p].end(),arr[0][x])-tr[0][p].begin()+1,s);
        mx2[p].add(lower_bound(tr[1][p].begin(),tr[1][p].end(),arr[1][x])-tr[1][p].begin()+1,s);
    }
    inline int query0(setpos,int x,int pl,int pr){
        if(l>=pl&&r<=pr){
            if(arr[0][x]>tr[0][p].back())   return -inf;
            return mx1[p].query(lower_bound(tr[0][p].begin(),tr[0][p].end(),arr[0][x])-tr[0][p].begin()+1);
        }
        setmid,res=-inf;if(pl<=mid)res=query0(lson,x,pl,pr);if(pr>mid)getmx(res,query0(rson,x,pl,pr));return res;
    }
    inline int query1(setpos,int x,int pl,int pr){
        if(l>=pl&&r<=pr){
            if(arr[1][x]<tr[1][p].front())   return -inf;
            return mx2[p].query(upper_bound(tr[1][p].begin(),tr[1][p].end(),arr[1][x])-tr[1][p].begin());
        }
        setmid,res=-inf;if(pl<=mid)res=query1(lson,x,pl,pr);if(pr>mid)getmx(res,query1(rson,x,pl,pr));return res;
    }
}
using namespace SegmentTree;
void discrete(){
    for(int i=1;i<=n;i++)   d[i]=a[i];d[n+1]=a[0];
    sort(d+1,d+n+2);m=unique(d+1,d+n+2)-d-1;
    for(int i=1;i<=n;i++)   aa[i]=lower_bound(d+1,d+m+2,a[i])-d;
    aa[0]=lower_bound(d+1,d+m+2,0)-d;
}
int main(){
    scanf("%d%d",&n,&v);
    for(int i=1;i<=n;i++)   scanf("%d",&t[i]);
    for(int i=1;i<=n;i++)   scanf("%d",&a[i]);
    discrete();
    for(int i=0;i<=n;i++)   arr[0][i]=a[i]-1ll*v*t[i];
    for(int i=0;i<=n;i++)   arr[1][i]=a[i]+1ll*v*t[i];
    for(int i=0;i<=n;i++)   ins(i);
    build(all);
    mems(dp,-0x3f);upd(0,dp[0]=0);
    int ans=0;
    for(int i=1;i<=n;i++){
        getmx(dp[i],query0(all,i,1,aa[i]));
        // printf("query0 = %d\n",query0(all,i,1,aa[i]));
        getmx(dp[i],query1(all,i,aa[i],m));
        // printf("query1 = %d\n",query1(all,i,aa[i],m));
        dp[i]++;
        upd(i,dp[i]);
        getmx(ans,dp[i]);
        // printf("dp[%d] = %d\n",i,dp[i]);
    }
    printf("%d\n",ans);
}
/*
if(abs(a[i]-a[j])/v<=(t[i]-t[j])) dp[i]=max(dp[j])+1

abs(a[i]-a[j])/v<=(t[i]-t[j])
a[i]-a[j]<=vt[i]-vt[j]

t[i]>t[j]

a[i]>=a[j]
a[i]-v*t[i]<=a[j]-v*t[j]

a[i]<a[j]
a[j]-a[i]<=vt[i]-vt[j]
a[j]+vt[j]<=a[i]+vt[i]

a[i]>=(a[j],j)
a[j]<=a[i] max(dp[j])
*/