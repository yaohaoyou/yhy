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
const int maxn=3e5+10,inf=1e9;
int n,q,cnt;
int a[maxn],b[maxn];
unordered_map<int,int> id;
set<int> st[maxn<<1];
inline int GCD(int x,int y){if(!x||!y)return 0;if(!~x)x++;if(!~y)y++;return __gcd(x,y);}
namespace SegmentTree{
    #define ls p<<1
    #define rs p<<1|1
    #define lson ls,l,mid
    #define rson rs,mid+1,r
    #define all 1,1,n
    #define setmid int mid=(l+r)>>1
    #define setpos int p,int l,int r
    int tr[maxn<<2],mx[maxn<<2],mn[maxn<<2],lst[maxn<<2];
    inline void pu(int p){tr[p]=GCD(tr[ls],tr[rs]);mx[p]=max(mx[ls],mx[rs]);mn[p]=min(mn[ls],mn[rs]);lst[p]=max(lst[ls],lst[rs]);}
    inline void upd(int x){
        int p=1,l=1,r=n;while(l^r){setmid;(x<=mid)?(p=ls,r=mid):(p=rs,l=mid+1);}
        mx[p]=mn[p]=a[x];tr[p]=abs(a[x]-a[x-1]);lst[p]=b[x];
        while(p>>=1)pu(p);
    }
    int query(setpos,int pl,int pr){if(l>=pl&&r<=pr)return tr[p];setmid,res=-1;if(pl<=mid)res=query(lson,pl,pr);if(pr>mid)res=GCD(res,query(rson,pl,pr));return res;}
    int querymx(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mx[p];setmid,res=0;if(pl<=mid)res=querymx(lson,pl,pr);if(pr>mid)res=max(res,querymx(rson,pl,pr));return res;}
    int querymn(setpos,int pl,int pr){if(l>=pl&&r<=pr)return mn[p];setmid,res=inf;if(pl<=mid)res=querymn(lson,pl,pr);if(pr>mid)res=min(res,querymn(rson,pl,pr));return res;}
    int querylst(setpos,int pl,int pr){if(l>=pl&&r<=pr)return lst[p];setmid,res=0;if(pl<=mid)res=querylst(lson,pl,pr);if(pr>mid)res=max(res,querylst(rson,pl,pr));return res;}
}
using namespace SegmentTree;
inline void update(int x,int y){
    if(~a[x]){
        int c=id[a[x]];
        auto it=st[c].find(x);
        it=st[c].erase(it);
        if(it!=st[c].end()){
            int z=*it;
            b[z]=(it!=st[c].begin())?*prev(it):-1;
            upd(z);
        }
    }
    a[x]=y;
    {
        if(id.find(a[x])==id.end())id[a[x]]=++cnt;
        int c=id[a[x]];
        auto it=st[c].ep(x).fi;
        b[x]=(it!=st[c].begin())?*prev(it):-1;upd(x);
        it++;if(it!=st[c].end()){b[*it]=x;upd(*it);}
    }
    if(x+1<=n)upd(x+1);
}
int main(){
    scanf("%d%d",&n,&q);
    mems(tr,-1);mems(mn,0x3f);mems(a,-1);
    for(int i=1;i<=n;i++){int x;scanf("%d",&x);update(i,x);}
    int res=0;
    while(q--){
        int op,l,r,k;
        scanf("%d%d%d",&op,&l,&r);
        l^=res;r^=res;
        if(op==1)   update(l,r);
        else{
            scanf("%d",&k);k^=res;
            // debug("[%d,%d] : %d\n",l,r,k);
            // printf("%d\n",querylst(all,l,r));
            bool flag=(l==r)?true:((querymx(all,l,r)-querymn(all,l,r)==1ll*(r-l)*k)&&(k?query(all,l+1,r)==k:true)&&(k?querylst(all,l,r)<l:true));
            res+=flag;puts(flag?"Yes":"No");
        }
    }
}