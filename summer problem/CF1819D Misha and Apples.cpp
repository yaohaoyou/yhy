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
int n,m;
int dp[maxn];
vector<int> v[maxn];
unordered_map<int,int> mp;
inline void gmx(int &x,int y){(x<y)&&(x=y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2];
    inline void pu(int p){tr[p]=max(tr[ls],tr[rs]);}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;while(p>>=1)pu(p);}
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=0;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)gmx(res,query(rson,pl,pr));return res;}
}
using namespace SegmentTree;
void matt(int _tc){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        int k;scanf("%d",&k);
        v[i].clear();v[i].resize(k);
        for(int j=0;j<k;j++)   scanf("%d",&v[i][j]);
    }
    mp.clear();
    memset(tr,0,sizeof(int)*(n+5));
    int R=n+1,R0=n+1,p=n+1,sum=0;
    for(int i=n;i;i--){
        sum+=v[i].size();
        dp[i]=0;
        for(int j:v[i]){
            if(mp.find(j)!=mp.end()&&mp[j]<R)    R=mp[j],p=i;
            mp[j]=i;
        }
        if(v[i].empty()){
            if(R==n+1)  dp[i]=m;
            else gmx(dp[i],query(all,i+1,R+1));
            // for(int j=i+1;j<=R+1;j++)   gmx(dp[i],dp[j]);
            R0=i;
        }
        else{
            if(R==n+1){
                dp[i]=dp[i+1]+v[i].size();
                if(R0!=n+1) dp[i]=m;
            }
            else{
                if(p!=i)    dp[i]=dp[i+1];
                else    dp[i]=dp[R+1];
                if(R0!=n+1&&R0+1<=R+1) dp[i]=query(all,R0+1,R+1);
                    // for(int j=R0+1;j<=R+1;j++)  gmx(dp[i],dp[j]);
            }
        }
        if(R==n+1)  gmx(dp[i],sum);
        dp[i]=min(dp[i],m);
        upd(i,dp[i]);
        // printf("dp[%d] = %d %d\n",i,dp[i],R+1);
    }
    printf("%d\n",dp[1]);
}
int main(){int T;scanf("%d",&T);for(int i=1;i<=T;i++)matt(i);}