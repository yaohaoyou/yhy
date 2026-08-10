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
int a[maxn];
struct Stack{
    int s[maxn],tp;
    inline void clear(){tp=0;}
    inline bool empty(){return !tp;}
    inline void ep(int x){s[++tp]=x;}
    inline void pop(){tp--;}
    inline int top(){return s[tp];}
    inline int size(){return tp;}
    int& operator[](int x){return s[x];}
}s[2];
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],cnt[maxn<<2],tag[maxn<<2];
    inline void pu(int p){tr[p]=min(tr[ls],tr[rs]);cnt[p]=tr[ls]<tr[rs]?cnt[ls]:(tr[ls]>tr[rs]?cnt[rs]:cnt[ls]+cnt[rs]);}
    inline void pt(int p,int s){tag[p]+=s;tr[p]+=s;}
    inline void pd(int p){if(tag[p]){pt(ls,tag[p]);pt(rs,tag[p]);tag[p]=0;}}
    void upd(setpos,int pl,int pr,int s){if(l>=pl&&r<=pr)return pt(p,s);pd(p);setmid;if(pl<=mid)upd(lson,pl,pr,s);if(pr>mid)upd(rson,pl,pr,s);pu(p);}
    inline void upd(int x,int s){int p=1,l=1,r=n;while(l^r){pd(p);setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}tr[p]=s;cnt[p]=1;while(p>>=1)pu(p);}
    int query0(setpos,int pl,int pr){if(tr[p])return 0;if(l>=pl&&r<=pr)return cnt[p];pd(p);setmid,res=0;if(pl<=mid)res=query0(lson,pl,pr);if(pr>mid)res+=query0(rson,pl,pr);return res;}
}
using namespace SegmentTree;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){int x,y;scanf("%d%d",&x,&y);a[x]=y;}
    ll ans=0;
    for(int i=1;i<=n;i++){
        while(!s[0].empty()&&a[s[0].top()]>=a[i]){
            upd(all,s[0][s[0].size()-1]+1,s[0].top(),a[s[0].top()]-a[i]);
            s[0].pop();
        }
        s[0].ep(i);
        while(!s[1].empty()&&a[s[1].top()]<=a[i]){
            upd(all,s[1][s[1].size()-1]+1,s[1].top(),a[i]-a[s[1].top()]);
            s[1].pop();
        }
        s[1].ep(i);
        upd(all,1,i,-1);
        upd(i,0);
        ans+=query0(all,1,i);
    }
    printf("%lld\n",ans);
}